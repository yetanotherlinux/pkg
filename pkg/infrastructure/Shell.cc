#include "Shell.h"

#include <unistd.h>
#include <wait.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Shell::Shell(const pkg::Settings &settings) :
            _settings(settings) {
    }

    void Shell::Run(const std::string &command) const {
        Run(command, "", false);
    }

    void Shell::Run(const std::string &command, const std::string &workingDirectory, bool impersonate) const {
        pid_t pid{fork()};
        if (pid < 0) {
            throw Exception("Fork failed");
        }
        if (pid == 0) {
            passwd *account{nullptr};
            if (impersonate) {
                account = getpwnam(std::string(_settings.ImpersonationAccount).c_str());
                if (!account) {
                    throw Exception("Impersonation failed: no such account");
                }
            }
            if (!workingDirectory.empty()) {
                if (chdir(workingDirectory.c_str())) {
                    throw Exception("Can't set working directory: " + workingDirectory);
                }
                if (account && chown(workingDirectory.c_str(), account->pw_uid, account->pw_gid)) {
                    throw Exception("Can't set working directory owner: " + workingDirectory);
                }
            }
            if (account) {
                Impersonate(account);
            }
            Execute(std::string(_settings.ShCommand), command);
            throw Exception("Unexpected call");
        }
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw Exception("'" + workingDirectory + "$ " + command + "' error");
        }
        if (!WIFEXITED(status)) {
            throw Exception("'" + workingDirectory + "$ " + command + "' terminated abnormally");
        }
        if (int exitCode = WEXITSTATUS(status)) {
            throw Exception("'" + workingDirectory + "$ " + command + "' returns '" + std::to_string(exitCode) + "'");
        }
    }

    void Shell::Execute(const std::string &sh, const std::string &command) {
        std::string shCommandArg{"-c"};
        const char *tokens[4]{
                sh.c_str(),
                shCommandArg.c_str(),
                command.c_str(),
                nullptr
        };
        if (execvp(sh.c_str(), const_cast<char **>(tokens))) {
            throw Exception("Invalid command: " + command);
        }
    }

    void Shell::Impersonate(const passwd *account) {
        if (setgid(account->pw_gid)) {
            throw Exception("Impersonation failed: can't set group id");
        }
        if (setuid(account->pw_uid)) {
            throw Exception("Impersonation failed: can't set user id");
        }
        if (!setuid(0)) {
            throw Exception("Impersonation failed: can set user id after impersonation");
        }
    }
}

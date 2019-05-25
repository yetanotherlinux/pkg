#include "Shell.h"

#include <filesystem>
#include <unistd.h>
#include <wait.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Shell::Shell(const pkg::Settings &settings, const Log &log) :
            _settings(settings),
            _log(log) {
    }

    void Shell::Run(const std::string &command) const {
        Run(command, "", std::nullopt);
    }

    void Shell::Run(
            const std::string &command,
            const std::string &workingDirectory,
            const std::optional<Account> &account) const {
        pid_t pid{fork()};
        if (pid < 0) {
            throw Exception("Fork failed");
        }

        if (pid == 0) {
            if (!workingDirectory.empty()) {
                std::filesystem::current_path(workingDirectory);
            }
            if (account.has_value()) {
                Impersonate(account.value());
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

    void Shell::Impersonate(const Account &account) {
        if (setgid(account.Id)) {
            throw Exception("Impersonation failed: can't set group id");
        }
        if (setuid(account.GroupId)) {
            throw Exception("Impersonation failed: can't set user id");
        }
        if (!setuid(0)) {
            throw Exception("Impersonation failed: can set user id after impersonation");
        }
    }
}

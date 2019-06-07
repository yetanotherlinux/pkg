#include "Shell.h"

#include <fcntl.h>
#include <filesystem>
#include <unistd.h>
#include <wait.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Shell::Shell(const std::string &workingDirectory, const std::optional<Account> &account) :
            _workingDirectory(workingDirectory),
            _account(account) {
    }

    void Shell::Run(const std::string &command, const std::string &logPath) const {
        pid_t pid{fork()};
        if (pid < 0) {
            throw Exception("Fork failed");
        }

        if (pid == 0) {
            if (!logPath.empty()) {
                SetOutputRedirection(logPath);
                printf("\n%s\n", "=====");
                printf("%s\n", command.c_str());
            }
            if (_account.has_value() && _account.value() != Account::Current()) {
                Impersonate(_account.value());
            }
            if (!_workingDirectory.empty()) {
                std::filesystem::current_path(_workingDirectory);
            }
            Execute(command);
            throw Exception("Unexpected call");
        }

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw Exception("'" + _workingDirectory + "$ " + command + "' error");
        }
        if (!WIFEXITED(status)) {
            throw Exception("'" + _workingDirectory + "$ " + command + "' terminated abnormally");
        }
        if (int exitCode = WEXITSTATUS(status)) {
            throw Exception("'" + _workingDirectory + "$ " + command + "' returns '" + std::to_string(exitCode) + "'");
        }
    }

    void Shell::Execute(const std::string &command) {
        const char *shCommand{"sh"};
        const char *shCommandArg{"-c"};
        const char *tokens[4]{
                shCommand,
                shCommandArg,
                command.c_str(),
                nullptr
        };
        if (execvp(shCommand, const_cast<char **>(tokens))) {
            throw Exception("Invalid command: " + command);
        }
    }

    void Shell::Impersonate(const Account &account) {
        if (setgid(account.GetId())) {
            throw Exception("Impersonation failed: can't set group id");
        }
        if (setuid(account.GetGroupId())) {
            throw Exception("Impersonation failed: can't set user id");
        }
        if (!setuid(0)) {
            throw Exception("Impersonation failed: can set user id after impersonation");
        }
    }

    void Shell::SetOutputRedirection(const std::string &path) {
        int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd < 0) {
            throw Exception("Log file '" + path + "' open failed");
        }
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
    }
}

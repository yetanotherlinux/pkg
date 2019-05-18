#include "Shell.h"

#include <cstring>
#include <filesystem>
#include <iomanip>
#include <unistd.h>
#include <wait.h>
#include <sys/ioctl.h>
#include <iostream>
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
        int pipesDescriptors[2];
        pipe(pipesDescriptors);

        pid_t pid{fork()};
        if (pid < 0) {
            throw Exception("Fork failed");
        }
        if (pid == 0) {
            dup2(pipesDescriptors[1], STDOUT_FILENO);
            dup2(pipesDescriptors[1], STDERR_FILENO);
            close(pipesDescriptors[0]);
            close(pipesDescriptors[1]);
            if (!workingDirectory.empty()) {
                std::filesystem::current_path(workingDirectory);
            }
            if (account.has_value()) {
                Impersonate(account.value());
            }
            Execute(std::string(_settings.ShCommand), command);
            throw Exception("Unexpected call");
        }
        PrintOutput(_log, pipesDescriptors);
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

    void Shell::PrintOutput(const Log &log, int pipesDescriptors[2]) {
        close(pipesDescriptors[1]);

        const char cr{'\r'};
        const char eol{'\n'};
        const char space{' '};
        const int bufSize{512};
        char buffer[bufSize + 1]{};
        size_t lineLength{};

        winsize ws{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
        size_t maxLineLength{ws.ws_col};

        while (ssize_t length{read(pipesDescriptors[0], buffer, bufSize)}) {
            if (length < 0) {
                throw std::exception();
            }
            buffer[length] = '\0';
            char *nl{std::strrchr(buffer, eol)};

            if (nl || (maxLineLength && lineLength + length >= maxLineLength)) {
                log.Out() << cr << std::setfill(space) << std::setw(lineLength) << "" << cr;
            }

            if (nl) {
                if (static_cast<size_t>(buffer + length - nl) > maxLineLength) {
                    nl = buffer + length - maxLineLength;
                } else {
                    ++nl;
                }
                lineLength = length - (nl - buffer);
                log.Out() << nl;
            } else {
                lineLength += length;
                if (!maxLineLength || lineLength < maxLineLength) {
                    log.Out() << buffer;
                } else {
                    lineLength = maxLineLength;
                    log.Out() << buffer + (length - lineLength);
                }
            }
            log.Out() << std::flush;
        }
        log.Out() << cr << std::flush;
        close(pipesDescriptors[0]);
    }
}

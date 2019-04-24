#include "Shell.h"

#include <unistd.h>
#include <wait.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Shell::Shell(const pkg::Settings &settings) :
            _shCommand(settings.ShCommand) {
    }

    void Shell::Run(const std::string &command) const {
        Run(command, "");
    }

    void Shell::Run(const std::string &command, const std::string &workingDirectory) const {
        pid_t pid{fork()};
        if (pid < 0) {
            throw Exception("Fork failed");
        }
        if (pid == 0) {
            Execute(_shCommand, command, workingDirectory);
            throw Exception("Unexpected call");
        }
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            throw Exception("'" + workingDirectory + " >" + command + "' error");
        }
        if (!WIFEXITED(status)) {
            throw Exception("'" + workingDirectory + " >" + command + "' terminated abnormally");
        }
        if (int exitCode = WEXITSTATUS(status)) {
            throw Exception("'" + workingDirectory + " >" + command + "' returns '" + std::to_string(exitCode) + "'");
        }
    }

    void Shell::Execute(const std::string &sh, const std::string &command, const std::string &workingDirectory) {
        std::string shCommandArg{"-c"};
        const char *tokens[4]{
                sh.c_str(),
                shCommandArg.c_str(),
                command.c_str(),
                nullptr
        };
        if (!workingDirectory.empty()) {
            if (chdir(workingDirectory.c_str())) {
                throw Exception("Can't set working directory: " + workingDirectory);
            }
        }
        if (execvp(sh.c_str(), const_cast<char **>(tokens))) {
            throw Exception("Invalid command: " + command);
        }
    }
}

#include "CommandAction.h"

namespace pkg::actions {

    CommandAction::CommandAction(
            const std::shared_ptr<Storage> &storage,
            const Substitution &substitution,
            bool checkVersion) :
            Action(storage, checkVersion),
            _substitution(substitution) {
    }

    void CommandAction::RunCommand(const Shell &shell, const std::string &command) const {
        shell.Run(command);
    }

    void CommandAction::RunCommand(
            const Shell &shell, const std::string &command, const std::string &logPath) const {
        shell.Run(_substitution.Process(command), logPath);
    }

    void CommandAction::RunCommands(
            const Shell &shell, const std::vector<std::string> &commands, const std::string &logPath) const {
        for (const std::string &command : commands) {
            RunCommand(shell, command, logPath);
        }
    }
}

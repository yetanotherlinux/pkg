#include "CommandAction.h"

namespace pkg::actions {

    CommandAction::CommandAction(
            const std::shared_ptr<Storage> &storage,
            const Substitution &substitution,
            const Shell &shell,
            bool checkVersion) :
            Action(storage, checkVersion),
            _substitution(substitution),
            _shell(shell) {
    }

    void CommandAction::RunCommand(const std::string &command) const {
        RunCommand(command, "", "");
    }

    void CommandAction::RunCommand(
            const std::string &command,
            const std::string &path,
            const std::string &logPath,
            const std::optional<Account> &account) const {
        _shell.Run(command, path, logPath, account);
    }

    void CommandAction::RunCommands(
            const std::vector<std::string> &commands,
            const std::string &path,
            const std::string &logPath,
            const std::optional<Account> &account) const {
        for (const std::string &command : commands) {
            RunCommand(_substitution.Process(command), path, logPath, account);
        }
    }
}

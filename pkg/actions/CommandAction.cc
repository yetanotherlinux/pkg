#include "CommandAction.h"

namespace pkg::actions {

    CommandAction::CommandAction(const std::shared_ptr<Storage> &storage, bool checkVersion, const Shell &shell) :
            Action(storage, checkVersion),
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
            RunCommand(command, path, logPath, account);

        }
    }
}

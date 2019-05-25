#ifndef PKG_ACTIONS_COMMAND_ACTION_H
#define PKG_ACTIONS_COMMAND_ACTION_H

#include "pkg/actions/Action.h"

#include "pkg/infrastructure/Shell.h"

using pkg::infrastructure::Shell;

namespace pkg::actions {
    class CommandAction : public Action {

    private:
        const Shell _shell;

    public:
        CommandAction(const std::shared_ptr<Storage> &storage, bool checkVersion, const Shell &shell);

    protected:
        void RunCommand(const std::string &command) const;

        void RunCommand(
                const std::string &command,
                const std::string &path,
                const std::string &logPath,
                const std::optional<Account> &account = std::nullopt) const;

        void RunCommands(
                const std::vector<std::string> &commands,
                const std::string &path,
                const std::string &logPath,
                const std::optional<Account> &account = std::nullopt) const;
    };
}

#endif

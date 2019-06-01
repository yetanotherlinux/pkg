#ifndef PKG_ACTIONS_COMMAND_ACTION_H
#define PKG_ACTIONS_COMMAND_ACTION_H

#include "pkg/actions/Action.h"

#include "pkg/Substitution.h"
#include "pkg/infrastructure/Shell.h"

using pkg::infrastructure::Shell;

namespace pkg::actions {
    class CommandAction : public Action {

    private:
        const Substitution _substitution;

    public:
        CommandAction(
                const std::shared_ptr<Storage> &storage,
                const Substitution &substitution,
                bool checkVersion);

    protected:
        void RunCommand(
                const Shell &shell, const std::string &command) const;

        void RunCommand(
                const Shell &shell, const std::string &command, const std::string &logPath) const;

        void RunCommands(
                const Shell &shell, const std::vector<std::string> &commands, const std::string &logPath) const;
    };
}

#endif

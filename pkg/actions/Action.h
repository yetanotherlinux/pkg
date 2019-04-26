#ifndef PKG_ACTIONS_ACTION_H
#define PKG_ACTIONS_ACTION_H

#include "pkg/actions/IAction.h"

#include "pkg/infrastructure/Shell.h"
#include "pkg/storage/Storage.h"

using pkg::infrastructure::Shell;
using pkg::storage::Storage;

namespace pkg::actions {
    class Action : public IAction {

    private:
        const std::shared_ptr<Storage> _storage;
        const bool _checkVersion;

    public:
        Action(const std::shared_ptr<Storage> &storage, bool checkVersion);

        bool ShouldBePerformed(const Package &package) const override;

    protected:
        void PushToStorage(const Package &package) const;

        void PopFromStorage(const Package &package) const;

        static void RunCommands(
                const Shell &shell, const std::vector<std::string> &commands, const std::string &path,
                bool impersonate = false);
    };
}

#endif

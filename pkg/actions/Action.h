#ifndef PKG_ACTIONS_ACTION_H
#define PKG_ACTIONS_ACTION_H

#include "pkg/actions/IAction.h"

#include "pkg/storage/Storage.h"

using pkg::storage::Storage;

namespace pkg::actions {
    class Action : public IAction {

    private:
        const std::shared_ptr<Storage> _storage;
        const bool _checkVersion;

    public:
        Action(const std::shared_ptr<Storage> &storage, bool checkVersion);

        bool ShouldBePerformed(const Package &package) const override;

        virtual void Perform(const PackageMetadata &package) const = 0;

        void Perform(const PackageMetadata &package, bool isForced) const override;

    protected:
        void PushToStorage(const Package &package) const;

        void PopFromStorage(const Package &package) const;
    };
}

#endif

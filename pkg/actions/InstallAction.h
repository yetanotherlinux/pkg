#ifndef PKG_ACTIONS_INSTALL_ACTION_H
#define PKG_ACTIONS_INSTALL_ACTION_H

#include "pkg/actions/CommandAction.h"

#include "pkg/actions/BuildAction.h"
#include "pkg/storage/PackageStorage.h"

using pkg::storage::PackageStorage;

namespace pkg::actions {
    class InstallAction : public CommandAction {

    private:
        const std::shared_ptr<BuildAction> _buildAction;
        const FileSystem _fileSystem;
        const Settings _settings;

    public:
        InstallAction(
                const std::shared_ptr<PackageStorage> &packageStorage,
                const std::shared_ptr<BuildAction> &buildAction,
                const FileSystem &fileSystem,
                const Shell &shell,
                const Settings &settings);

        std::string GetName() const override;

        void Perform(const PackageMetadata &package) const override;

    private:
        void ResetLdCache() const;
    };
}

#endif

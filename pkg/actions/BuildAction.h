#ifndef PKG_ACTIONS_BUILD_ACTION_H
#define PKG_ACTIONS_BUILD_ACTION_H

#include "pkg/actions/CommandAction.h"

#include "pkg/Log.h"
#include "pkg/actions/FetchAction.h"
#include "pkg/storage/BuildStorage.h"

using pkg::storage::BuildStorage;

namespace pkg::actions {
    class BuildAction : public CommandAction {

    private:
        const std::shared_ptr<FetchAction> _fetchAction;
        const Account _account;
        const FileSystem _fileSystem;
        const Log _log;
        const std::string _buildPath;

    public:
        BuildAction(
                const std::shared_ptr<BuildStorage> &buildStorage,
                const std::shared_ptr<FetchAction> &fetchAction,
                const Substitution &substitution,
                const Account &account,
                const FileSystem &fileSystem,
                const Shell &shell,
                const Settings &settings,
                const Log &log);

        std::string GetName() const override;

        void Perform(const PackageMetadata &package) const override;

        std::string GetPath(const PackageMetadata &package) const;

        std::string GetLogPath(const PackageMetadata &package, const std::string &logName) const;

    private:
        std::string GetRootPath(const PackageMetadata &package) const;
    };
}

#endif

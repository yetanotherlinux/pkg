#ifndef PKG_ACTIONS_FETCH_ACTION_H
#define PKG_ACTIONS_FETCH_ACTION_H

#include "pkg/actions/Action.h"

#include "pkg/Log.h"
#include "pkg/infrastructure/Shell.h"
#include "pkg/infrastructure/WebClient.h"
#include "pkg/storage/SourceStorage.h"

using pkg::infrastructure::Shell;
using pkg::infrastructure::WebClient;
using pkg::storage::SourceStorage;

namespace pkg::actions {
    class FetchAction : public Action {

    private:
        const FileSystem _fileSystem;
        const WebClient _webClient;
        const Shell _shell;
        const Log _log;
        const std::string _downloadPath;
        const std::string _sourcesPath;

    public:
        FetchAction(
                const std::shared_ptr<SourceStorage> &sourceStorage,
                const FileSystem &fileSystem,
                const WebClient &webClient,
                const Shell &shell,
                const Settings &settings,
                const Log &log);

        std::string GetName() const override;

        std::string GetPath(const Package &package) const;

        void Perform(const PackageMetadata &package) const override;

    private:
        std::string Download(const PackageMetadata &package) const;

        std::string Extract(const std::string &filePath, const std::string &extractPath) const;
    };
}

#endif

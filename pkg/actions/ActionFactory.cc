#include "ActionFactory.h"

#include "pkg/actions/StatusAction.h"

namespace pkg::actions {

    static const std::string_view StatusActionName{"status"};
    static const std::string_view FetchActionName{"fetch"};
    static const std::string_view InstallActionName{"install"};
    static const std::string_view UpdateActionName{"update"};

    ActionFactory::ActionFactory(
            std::shared_ptr<SourceStorage> sourceStorage,
            std::shared_ptr<BinaryStorage> binaryStorage,
            std::shared_ptr<PackageStorage> packageStorage,
            const FileSystem &fileSystem,
            const WebClient &webClient,
            const Shell &shell,
            const Settings &settings,
            const Log &log) :
            _sourceStorage(std::move(sourceStorage)),
            _binaryStorage(std::move(binaryStorage)),
            _packageStorage(std::move(packageStorage)),
            _fileSystem(fileSystem),
            _webClient(webClient),
            _shell(shell),
            _settings(settings),
            _log(log) {
    }

    std::vector<std::string_view> ActionFactory::GetActions() const {
        return {
                StatusActionName,
                FetchActionName,
                InstallActionName,
                UpdateActionName
        };
    }

    std::shared_ptr<IAction> ActionFactory::CreateAction(const std::string &name) const {
        auto fetchAction{std::make_shared<FetchAction>(
                _sourceStorage, _fileSystem, _webClient, _shell, _settings, _log)};
        if (name == FetchActionName) {
            return fetchAction;
        }

        auto buildAction{std::make_shared<BuildAction>(
                _binaryStorage, fetchAction, _fileSystem, _shell, _settings, _log)};

        auto installAction{std::make_shared<InstallAction>(_packageStorage, buildAction, _shell)};
        if (name == InstallActionName) {
            return installAction;
        }

        auto updateAction{std::make_shared<UpdateAction>(_packageStorage, buildAction, installAction)};
        if (name == UpdateActionName) {
            return updateAction;
        }

        if (name == StatusActionName) {
            return std::make_shared<StatusAction>(fetchAction, buildAction, installAction, updateAction, _log);
        }
        return nullptr;
    }
}

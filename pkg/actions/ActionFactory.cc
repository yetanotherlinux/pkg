#include "ActionFactory.h"


namespace pkg::actions {

    ActionFactory::ActionFactory(
            const std::shared_ptr<SourceStorage> &sourceStorage,
            const std::shared_ptr<BinaryStorage> &binaryStorage,
            const std::shared_ptr<PackageStorage> &packageStorage,
            const FileSystem &fileSystem,
            const WebClient &webClient,
            const Shell &shell,
            const Settings &settings,
            const Log &log) :
            _fetchAction(std::make_shared<FetchAction>(sourceStorage, fileSystem, webClient, settings, log)),
            _buildAction(std::make_shared<BuildAction>(binaryStorage, _fetchAction, fileSystem, shell, settings, log)),
            _installAction(std::make_shared<InstallAction>(packageStorage, _buildAction, fileSystem, shell, settings)),
            _updateAction(std::make_shared<UpdateAction>(packageStorage, _buildAction, _installAction)),
            _statusAction(std::make_shared<StatusAction>(
                    _fetchAction, _buildAction, _installAction, _updateAction, log)) {
    }

    std::vector<std::string> ActionFactory::GetActions() const {
        return {
                _statusAction->GetName(),
                _fetchAction->GetName(),
                _installAction->GetName(),
                _updateAction->GetName()
        };
    }

    std::shared_ptr<IAction> ActionFactory::CreateAction(const std::string &name) const {
        if (name == _fetchAction->GetName()) {
            return _fetchAction;
        }
        if (name == "pre" + _buildAction->GetName()) {
            return _buildAction;
        }
        if (name == _installAction->GetName()) {
            return _installAction;
        }
        if (name == _updateAction->GetName()) {
            return _updateAction;
        }
        if (name == _statusAction->GetName()) {
            return _statusAction;
        }
        return nullptr;
    }
}

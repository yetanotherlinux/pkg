#include "Action.h"

namespace pkg::actions {

    Action::Action(const std::shared_ptr<Storage> &storage, bool checkVersion) :
            _storage(storage),
            _checkVersion(checkVersion) {
    }

    bool Action::ShouldBePerformed(const Package &package) const {
        std::optional<Package> storagePackage{_storage->FindPackage(package.Name)};
        return !storagePackage.has_value() || (_checkVersion && storagePackage->Version != package.Version);
    }

    void Action::Perform(const PackageMetadata &package, bool isForced) const {
        if (isForced) {
            if (_storage->FindPackage(package.Name).has_value()) {
                _storage->Pop(package);
            }
        }

        Perform(package);
    }

    void Action::PushToStorage(const Package &package) const {
        _storage->Push(package);
    }

    void Action::PopFromStorage(const Package &package) const {
        _storage->Pop(package);
    }
}

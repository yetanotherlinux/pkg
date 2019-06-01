#include "PackageStorage.h"

namespace pkg::storage {

    PackageStorage::PackageStorage(const Settings &settings, const FileSystem &fileSystem) :
            Storage(settings.GetPackagesFilePath(), fileSystem) {
    }
}

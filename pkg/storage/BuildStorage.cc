#include "BuildStorage.h"

namespace pkg::storage {

    BuildStorage::BuildStorage(const Settings &settings, const FileSystem &fileSystem) :
            Storage(settings, settings.BuildsFileName, fileSystem) {
    }
}

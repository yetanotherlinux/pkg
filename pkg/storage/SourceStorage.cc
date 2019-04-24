#include "SourceStorage.h"

namespace pkg::storage {

    SourceStorage::SourceStorage(const Settings &settings, const FileSystem &fileSystem) :
            Storage(settings, settings.SourcesFileName, fileSystem) {
    }
}

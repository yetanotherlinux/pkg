#include "BinaryStorage.h"

namespace pkg::storage {

    BinaryStorage::BinaryStorage(const Settings &settings, const FileSystem &fileSystem) :
            Storage(settings, settings.BinariesFileName, fileSystem) {
    }
}

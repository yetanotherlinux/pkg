#ifndef PKG_STORAGE_BINARY_STORAGE_H
#define PKG_STORAGE_BINARY_STORAGE_H

#include "pkg/storage/Storage.h"

namespace pkg::storage {
    class BinaryStorage : public Storage {

    public:
        BinaryStorage(const Settings &settings, const FileSystem &fileSystem);
    };
}

#endif

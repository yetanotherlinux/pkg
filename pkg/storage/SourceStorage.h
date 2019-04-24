#ifndef PKG_STORAGE_SOURCE_STORAGE_H
#define PKG_STORAGE_SOURCE_STORAGE_H

#include "pkg/storage/Storage.h"

namespace pkg::storage {
    class SourceStorage : public Storage {

    public:
        SourceStorage(const Settings &settings, const FileSystem &fileSystem);
    };
}

#endif

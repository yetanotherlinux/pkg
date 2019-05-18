#ifndef PKG_STORAGE_BUILD_STORAGE_H
#define PKG_STORAGE_BUILD_STORAGE_H

#include "pkg/storage/Storage.h"

namespace pkg::storage {
    class BuildStorage : public Storage {

    public:
        BuildStorage(const Settings &settings, const FileSystem &fileSystem);
    };
}

#endif

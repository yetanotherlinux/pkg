#ifndef PKG_STORAGE_PACKAGE_STORAGE_H
#define PKG_STORAGE_PACKAGE_STORAGE_H

#include "pkg/storage/Storage.h"

namespace pkg::storage {
    class PackageStorage : public Storage {

    public:
        PackageStorage(const Settings &settings, const FileSystem &fileSystem);
    };
}

#endif

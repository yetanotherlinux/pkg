#ifndef PKG_PACKAGE_H
#define PKG_PACKAGE_H

#include <string>

namespace pkg {
    struct Package {

        std::string Name;
        std::string Version;

        Package(std::string name, std::string version);
    };
}

#endif

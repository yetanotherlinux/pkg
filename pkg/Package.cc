#include "Package.h"

namespace pkg {

    Package::Package(std::string name, std::string version) :
            Name(std::move(name)),
            Version(std::move(version)) {
    }
}

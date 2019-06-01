#ifndef PKG_INFRASTRUCTURE_KERNEL_H
#define PKG_INFRASTRUCTURE_KERNEL_H

#include <string>

namespace pkg::infrastructure {
    class Kernel {

    public:
        std::string GetArch() const;

    };
}

#endif

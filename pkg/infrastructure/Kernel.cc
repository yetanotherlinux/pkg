#include "Kernel.h"

#include <memory>
#include <sys/utsname.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    std::string Kernel::GetArch() const {
        auto info{std::make_unique<utsname>()};
        if (uname(info.get())) {
            throw Exception("Can't get kernel info");
        }
        return info->machine;
    }
}

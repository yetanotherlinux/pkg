#include "Log.h"

#include <iostream>

namespace pkg {

    std::ostream &Log::Out() const {
        return std::cout;
    }

    std::ostream &Log::Error() const {
        return std::cerr;
    }
}

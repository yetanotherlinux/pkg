#include "Exception.h"

namespace pkg {

    Exception::Exception(std::string message) :
            _message(std::move(message)) {

    }

    const char *Exception::what() const noexcept {
        return _message.c_str();
    }
}

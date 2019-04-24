#ifndef PKG_EXCEPTION_H
#define PKG_EXCEPTION_H

#include <string>

namespace pkg {
    class Exception : public std::exception {

    private:
        const std::string _message;

    public:
        explicit Exception(std::string message);

        const char *what() const noexcept override;
    };
}

#endif

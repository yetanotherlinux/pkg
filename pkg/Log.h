#ifndef PKG_LOG_H
#define PKG_LOG_H

#include <ostream>

namespace pkg {
    class Log {

    public:
        std::ostream &Out() const;

        std::ostream &Error() const;
    };
}

#endif

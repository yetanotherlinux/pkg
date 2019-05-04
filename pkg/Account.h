#ifndef PKG_ACCOUNT_H
#define PKG_ACCOUNT_H

#include <cstdint>

namespace pkg {
    struct Account {

        uint32_t Id;
        uint32_t GroupId;

        Account(uint32_t id, uint32_t groupId);
    };
}

#endif

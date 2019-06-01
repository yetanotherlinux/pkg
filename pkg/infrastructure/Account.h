#ifndef PKG_INFRASTRUCTURE_ACCOUNT_H
#define PKG_INFRASTRUCTURE_ACCOUNT_H

#include <pwd.h>
#include <string>

namespace pkg::infrastructure {
    class Account {

    private:
        const uint32_t _id;
        const uint32_t _groupId;

        Account(passwd *account);

    public:
        Account(const std::string &accountName);

        bool operator==(const Account &o) const;

        bool operator!=(const Account &o) const;

        uint32_t GetId() const;

        uint32_t GetGroupId() const;

        static Account Current();

    };
}

#endif

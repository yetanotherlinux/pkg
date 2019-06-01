#include "Account.h"

#include <unistd.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Account::Account(passwd *account) :
            _id(account->pw_uid),
            _groupId(account->pw_gid) {
    }

    Account::Account(const std::string &accountName) :
            Account([&accountName]() {
                passwd *account = getpwnam(accountName.c_str());
                return account ? account : throw Exception("Impersonation failed: no such account");
            }()) {
    }

    bool Account::operator==(const Account &o) const {
        return _id == o._id;
    }

    bool Account::operator!=(const Account &o) const {
        return !operator==(o);
    }

    uint32_t Account::GetId() const {
        return _id;
    }

    uint32_t Account::GetGroupId() const {
        return _groupId;
    }

    Account Account::Current() {
        uid_t uid{geteuid()};
        return getpwuid(uid);
    }
}

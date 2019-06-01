#ifndef PKG_INFRASTRUCTURE_SHELL_H
#define PKG_INFRASTRUCTURE_SHELL_H

#include <optional>
#include "pkg/Account.h"

namespace pkg::infrastructure {
    class Shell {

    private:
        const std::string _workingDirectory;
        const std::optional<Account> _account;

    public:
        Shell(const std::string &workingDirectory = "", const std::optional<Account> &account = std::nullopt);

        void Run(const std::string &command, const std::string &logPath = "") const;

    private:
        static void Impersonate(const Account &account);

        static void SetOutputRedirection(const std::string &path);

        static void Execute(const std::string &command);
    };
}

#endif

#ifndef PKG_INFRASTRUCTURE_SHELL_H
#define PKG_INFRASTRUCTURE_SHELL_H

#include <optional>
#include "pkg/Account.h"
#include "pkg/Log.h"
#include "pkg/Settings.h"

namespace pkg::infrastructure {
    class Shell {

    private:
        const Settings _settings;
        const Log _log;

    public:
        Shell(const Settings &settings, const Log &log);

        void Run(const std::string &command) const;

        void Run(
                const std::string &command,
                const std::string &workingDirectory,
                const std::optional<Account> &account) const;

    private:
        static void Impersonate(const Account &account);

        static void Execute(const std::string &sh, const std::string &command);

        static void PrintOutput(const Log &log, int pipesDescriptors[2]);
    };
}

#endif

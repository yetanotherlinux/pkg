#ifndef PKG_INFRASTRUCTURE_SHELL_H
#define PKG_INFRASTRUCTURE_SHELL_H

#include "pkg/Settings.h"

namespace pkg::infrastructure {
    class Shell {

    private:
        const std::string _shCommand;

    public:
        Shell(const Settings &settings);

        void Run(const std::string &command) const;

        void Run(const std::string &command, const std::string &workingDirectory) const;

    private:
        static void Execute(const std::string &sh, const std::string &command, const std::string &workingDirectory);
    };
}

#endif

#ifndef PKG_ARGS_H
#define PKG_ARGS_H

#include <string>
#include <vector>
#include "Settings.h"

namespace pkg {
    class Args {

    private:
        std::string _action;
        std::vector<std::string> _packages;
        bool _hasForceFlag;

    public:
        Args(int argc, char **argv, const Settings &settings);

        bool HasForceFlag() const;

        std::string GetAction() const;

        std::vector<std::string> GetPackages() const;
    };
}

#endif

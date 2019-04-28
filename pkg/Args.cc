#include "Args.h"

#include "pkg/Exception.h"

namespace pkg {

    Args::Args(int argc, char **argv, const Settings &settings) :
            _action(),
            _packages(),
            _hasForceFlag() {
        int index{1};

        const std::string flagPrefix{"--"};
        for (std::string s{argv[index]};
             s.size() >= flagPrefix.size() && s.substr(0, flagPrefix.size()) == flagPrefix;
             s = argv[++index]) {
            if (s == "--force") {
                _hasForceFlag = true;
            } else {
                throw Exception("Unknown flag '" + s + "'");
            }
        }

        _action = argc == index ? settings.DefaultAction : argv[index];
        for (++index; index < argc; ++index) {
            _packages.emplace_back(argv[index]);
        }
    }

    bool Args::HasForceFlag() const {
        return _hasForceFlag;
    }

    std::string Args::GetAction() const {
        return _action;
    }

    std::vector<std::string> Args::GetPackages() const {
        return _packages;
    }
}

#include "Args.h"

namespace pkg {

    static const int ActionIndex{1};

    Args::Args(int argc, char **argv, const Settings &settings) :
            _action(argc == ActionIndex ? settings.DefaultAction : argv[ActionIndex]),
            _packages() {
        for (int i{ActionIndex + 1}; i < argc; ++i) {
            _packages.emplace_back(argv[i]);
        }
    }

    std::string Args::GetAction() const {
        return _action;
    }

    std::vector<std::string> Args::GetPackages() const {
        return _packages;
    }
}

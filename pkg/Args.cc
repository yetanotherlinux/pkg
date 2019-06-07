#include "Args.h"

#include "pkg/Exception.h"

namespace pkg {

    Args::Args(int argc, char **argv, std::string defaultAction) :
            _defaultAction(std::move(defaultAction)),
            _action(),
            _packages() {
        const std::string flagPrefix{"--"};
        int index{};

        while (argc > ++index) {
            std::string s{argv[index]};
            if (s.size() >= flagPrefix.size() && s.substr(0, flagPrefix.size()) == flagPrefix) {
                if (s == "--") {
                } else {
                    throw Exception("Unknown flag '" + s + "'");
                }
            } else {
                break;
            }
        }

        _action = argc == index ? _defaultAction : argv[index];
        for (++index; index < argc; ++index) {
            _packages.emplace_back(argv[index]);
        }
    }

    std::string Args::GetAction() const {
        return _action;
    }

    std::vector<std::string> Args::GetPackages() const {
        return _packages;
    }
}

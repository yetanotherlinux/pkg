#ifndef PKG_ARGS_H
#define PKG_ARGS_H

#include <string>
#include <vector>

namespace pkg {
    class Args {

    private:
        const std::string _defaultAction;
        std::string _action;
        std::vector<std::string> _packages;

    public:
        Args(int argc, char **argv, std::string defaultAction);

        std::string GetAction() const;

        std::vector<std::string> GetPackages() const;
    };
}

#endif

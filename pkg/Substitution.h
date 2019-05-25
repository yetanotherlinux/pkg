#ifndef PKG_SUBSTITUTION_H
#define PKG_SUBSTITUTION_H

#include <map>

namespace pkg {
    class Substitution {

    private:
        const std::map<std::string, std::string> _dictionary;

    public:
        Substitution(std::map<std::string, std::string> dictionary);

        std::string Process(std::string string) const;
    };
}

#endif

#include "Substitution.h"

namespace pkg {

    Substitution::Substitution(std::map<std::string, std::string> dictionary) :
            _dictionary(std::move(dictionary)) {
    }

    std::string Substitution::Process(std::string string) const {
        for (const auto &[key, value] : _dictionary) {
            std::string placeholder{"${" + key + "}"};
            std::string::size_type p{};
            while ((p = string.find(placeholder)) != std::string::npos) {
                string = string.replace(p, placeholder.size(), value);
            }
        }
        return string;
    }
}

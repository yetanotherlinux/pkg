#ifndef PKG_INFRASTRUCTURE_ARCHIVE_H
#define PKG_INFRASTRUCTURE_ARCHIVE_H

#include <string>

namespace pkg::infrastructure {
    class Archive {

    private:
        const std::string _path;

    public:
        Archive(const std::string &path);

        std::string Extract(const std::string &path) const;
    };
}

#endif

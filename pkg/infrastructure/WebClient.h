#ifndef PKG_INFRASTRUCTURE_WEB_CLIENT_H
#define PKG_INFRASTRUCTURE_WEB_CLIENT_H

#include <string_view>

namespace pkg::infrastructure {
    class WebClient {

    public:
        WebClient();

        void Load(const std::string &url, std::ostream *stream) const;

    private:
        static size_t WriteToStream(void *ptr, size_t size, size_t nmemb, void *stream);
    };
}

#endif

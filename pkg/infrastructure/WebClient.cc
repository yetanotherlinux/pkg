#include "WebClient.h"

#include <memory>
#include <sstream>
#include <curl/curl.h>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    WebClient::WebClient() {
        static const CURLcode init{curl_global_init(CURL_GLOBAL_DEFAULT)};
        if (init != CURLcode::CURLE_OK) {
            throw Exception("cUrl global init failed");
        }
    }

    void WebClient::Load(const std::string &url, std::ostream *stream) const {
        std::unique_ptr<CURL, void (*)(CURL *)> curl{curl_easy_init(), curl_easy_cleanup};
        if (curl == nullptr) {
            throw Exception("cUrl init failed");
        }

        curl_easy_setopt(curl.get(), CURLoption::CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLoption::CURLOPT_WRITEDATA, stream);
        curl_easy_setopt(curl.get(), CURLoption::CURLOPT_WRITEFUNCTION, WriteToStream);
        curl_easy_setopt(curl.get(), CURLoption::CURLOPT_FOLLOWLOCATION, true);
        if (curl_easy_perform(curl.get()) != CURLcode::CURLE_OK) {
            throw Exception(std::string(url) + " loading failed");
        }
    }

    size_t WebClient::WriteToStream(void *ptr, size_t size, size_t nmemb, void *stream) {
        size_t length{size * nmemb / sizeof(char)};
        static_cast<std::ostream *>(stream)->write(reinterpret_cast<char *>(ptr), static_cast<std::streamsize>(length));
        return length;
    }
}

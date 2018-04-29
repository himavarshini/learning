/**
 * @copyright Dev Naga <devendra.aaru@gmail.com>
 *
 * MIT Licensed
 * download of the REST API data from github using CURL API
 */
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <fstream>

// ofstream is part of std
// ios is a sub class of std and out is part of ios
static std::ofstream fout;
static std::ifstream fin;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    fout << (char *)ptr;
    return size * nmemb;
}

static int curlGetContent(char *end_point_url, char *json_file)
{
    CURLcode code;
    CURL *curl;
    static int req;

    fout.open(json_file, std::ios::out);
    if (!fout.is_open()) {
        std::cout <<"Failed to open "<<json_file<<std::endl;
        return -1;
    }

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, end_point_url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "DevNaga");

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);

        req ++;

        char* url;
        long response_code;
        double elapsed;
        char *content = NULL;

        code = curl_easy_perform(curl);
        if (code != CURLE_OK) {
            std::cout <<"Failed to easy perform"<<std::endl;
            return -1;
        }

        std::cout << "Request: ["<<req<<"] {"<<std::endl;
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (code == CURLE_OK) {
            std::cout <<"\t response code "<<response_code<<std::endl;
        }
        code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        if (code == CURLE_OK) {
            std::cout <<"\t elapsed time "<<elapsed<<" seconds"<<std::endl;
        }
        code = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        if (code == CURLE_OK) {
            std::cout <<"\t effective uri "<<url<<std::endl;
        }
        std::cout << "}"<<std::endl;

        curl_easy_cleanup(curl);
        curl = NULL;
    }

    fout.close();
}

int main(int argc, char** argv)
{
    curlGetContent("https://api.github.com/users/devnaga/repos", "repos.json");
    curlGetContent("https://api.github.com/users/devnaga/followers", "followers.json");
    curlGetContent("https://api.github.com/users/devnaga/starred", "starred.json");
    curlGetContent("https://api.github.com/users/devnaga/following", "following.json");
    curlGetContent("https://api.github.com/users/devnaga/gists", "gists.json");
    curlGetContent("https://api.github.com/users/devnaga/orgs", "orgs.json");

    return 0;
}

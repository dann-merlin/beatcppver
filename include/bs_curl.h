#pragma once
#include <string>
#include <curl/curl.h>
#include <vector>

struct BsResponse {
	std::string returnCode;
	std::string responseText;
};

struct BsRequestOptions  {
	std::vector<std::string> headers = {"Accept: application/json", "Content-Type: application/json", "charset: utf-8"};
	std::string api_url = "https://beatsaver.com/api";
	std::string user_agent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36";
	std::string request_type = "GET";
	std::string data = "";
};

class BsCurl {
	private:
		static curl_slist *generateHeaders(std::vector<std::string> header_list);
		static std::string generateUrl(std::string query);
	public:
		static std::string percentEscapeString(std::string s);
		static BsResponse sendRequest(std::string query, BsRequestOptions options = BsRequestOptions{});
};

#pragma once
#include <string>
#include <curl/curl.h>

struct BsResponse {
	std::string returnCode;
	std::string responseText;
};

class BsCurl {
	private:
		static curl_slist *generateHeaders();
		static std::string generateUrl(std::string query);
	public:
		static std::string percentEscapeString(std::string s);
		static BsResponse sendRequest(std::string query);
};

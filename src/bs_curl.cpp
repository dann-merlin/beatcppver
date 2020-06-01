#include "bs_curl.h"
#include <curl/curl.h>
#include <iterator>
#include <string>
#include <iostream>

static const std::string API_URL = "https://beatsaver.com/api";
static const char *USER_AGENT = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36";

static int write_into(char* data, size_t size, size_t nmemb, std::string *buffer_in) {
	if(buffer_in != NULL) {
		buffer_in->append(data, size * nmemb);

		return size * nmemb;
	}

	return 0;
}	

struct curl_slist *BsCurl::generateHeaders() {
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charset: utf-8");
	return headers;
}

std::string BsCurl::generateUrl(std::string query) {
	return API_URL + query;
}

std::string BsCurl::percentEscapeString(std::string s) {
	CURL *handle = curl_easy_init();
	char* c_s = curl_easy_escape(handle, s.c_str(), s.length());
	std::string escaped(c_s);
	curl_free(c_s);
	curl_easy_cleanup(handle);
	return escaped;
}

BsResponse BsCurl::sendRequest(std::string query) {
	CURL *handle = curl_easy_init();
	if(!handle) {
		return BsResponse{"418", "curl_easy_init failed. Was not so easy after all, it seems..."};
	}

	curl_slist *headers = generateHeaders();
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

	std::cout << generateUrl(query) << std::endl;

	std::string url_string = generateUrl(query);
	const char* url = url_string.c_str();
	curl_easy_setopt(handle, CURLOPT_URL, url);

	curl_easy_setopt(handle, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(handle, CURLOPT_USERAGENT, USER_AGENT);

	std::string output;
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_into);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &output);

	CURLcode res = curl_easy_perform(handle);

	bool success = false;
	if(CURLE_OK == res) {
		char *ct;
		res = curl_easy_getinfo(handle, CURLINFO_CONTENT_TYPE, &ct);
		if((CURLE_OK == res) && ct)
			success = true;
	}
	if(success) {
		std::string downloaded = output;

		curl_slist_free_all(headers);
		curl_easy_cleanup(handle);
		return BsResponse{"200", downloaded};
	}
	return BsResponse{curl_easy_strerror(res), "Something went wrong collecting your response. Why wouldn't you just listen for once?!"};
}

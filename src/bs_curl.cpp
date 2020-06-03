#include "bs_curl.h"
#include <curl/curl.h>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>

static int write_into(char* data, size_t size, size_t nmemb, std::string *buffer_in) {
	if(buffer_in != NULL) {
		buffer_in->append(data, size * nmemb);

		return size * nmemb;
	}

	return 0;
}	

curl_slist *BsCurl::generateHeaders(std::vector<std::string> header_list) {
	struct curl_slist *headers = NULL;
	for(auto str : header_list) {
		headers = curl_slist_append(headers, str.c_str());
	}
	return headers;
}

std::string BsCurl::percentEscapeString(std::string s) {
	CURL *handle = curl_easy_init();
	char* c_s = curl_easy_escape(handle, s.c_str(), s.length());
	std::string escaped(c_s);
	curl_free(c_s);
	curl_easy_cleanup(handle);
	return escaped;
}

BsResponse BsCurl::sendRequest(std::string query, BsRequestOptions options) {
	CURL *handle = curl_easy_init();
	if(!handle) {
		return BsResponse{"418", "curl_easy_init failed. Was not so easy after all, it seems..."};
	}

	curl_slist *headers = generateHeaders(options.headers);
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

	std::string url_string = (options.api_url + query);

	const char* url = url_string.c_str();
	curl_easy_setopt(handle, CURLOPT_URL, url);
	const char* data = options.data.c_str();

	if(options.request_type == "GET") {
		curl_easy_setopt(handle, CURLOPT_HTTPGET, 1);
	} else if(options.request_type == "POST") {
		curl_easy_setopt(handle, CURLOPT_POST, 1);
		curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, options.data.size());
		curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data);
	}

	curl_easy_setopt(handle, CURLOPT_USERAGENT, options.user_agent.c_str());

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

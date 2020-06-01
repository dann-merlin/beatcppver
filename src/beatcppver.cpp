#include "beatcppver.h"
#include <iostream>
#include <curl/curl.h>

bool BeatCver::init_done = false;

void BeatCver::setup_check(char *caller) {
	if(!init_done) {
		std::cerr << caller << ": You haven't called BeatCver::init() yet. Believe me, I'm doing you a favor exiting this program. Greeting from BeatCver!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int BeatCver::init() {
	if(init_done) return -1;

	CURLcode init_return_code;
   	init_return_code = curl_global_init(CURL_GLOBAL_ALL);
	if(init_return_code) {
		std::cerr << "curl_global_init failed. Believe me, I'm doing you a favor exiting this program. Greeting from BeatCver!" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}

BeatCver::~BeatCver() {
}

BsSearchResult *BeatCver::searchText(char *query, int page) {
	BsSearchResult *result = new BsSearchResult(query, page, BsSearchType::text);
	return result;
}

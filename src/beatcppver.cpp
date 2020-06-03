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

BsSearchResult *BeatCver::searchText(const char *query, int page) {
	BsSearchResult *result = new BsSearchResult(query, page, BsSearchType::text);
	return result;
}

std::vector<BsSong> BeatCver::searchText(std::string query, int max_sites) {
	int page = 0;
	BsSearchResult *result = nullptr;
	std::vector<BsSong> song_list;
	do {
		delete result;
		result = new BsSearchResult(query.c_str(), page++, BsSearchType::text);
		song_list.insert(song_list.end(), result->results.begin(), result->results.end());
	} while(page <= max_sites && result->nextPage);
	delete result;
	return song_list;
}

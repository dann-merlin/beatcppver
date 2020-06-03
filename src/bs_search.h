#pragma once
#include "bs_curl.h"
#include "bs_song.h"
#include <vector>

static const int all_pages = -1;

enum BsSearchType {
	text,
	advanced
};


class BsSearchResult {
	private:
		int page, lastPage, totalEntries;

		void process_response(BsResponse response);
	public:
		std::vector<BsSong> results;
		bool nextPage, prevPage;

		BsSearchResult(const char* query, int page, BsSearchType type);
		BsSearchResult(const char* query, BsSearchType type);
};

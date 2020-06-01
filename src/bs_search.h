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
		std::vector<BsSong> results;
		int page, lastPage, totalEntries;
		bool nextPage, prevPage;

		void process_response(BsResponse response);
	public:
		BsSearchResult(char* query, int page, BsSearchType type);
};

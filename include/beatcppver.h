#pragma once
#include "bs_search.h"

class BeatCver {
	private:
		static bool init_done;
		static void setup_check(char *caller);
		BeatCver() {};
		~BeatCver();
	public:
		static BeatCver& getInstance() {
			static BeatCver instance;
			return instance;
		}
		BeatCver(BeatCver const&) = delete;
		void operator=(BeatCver const&) = delete;

		int init();
		BsSearchResult *searchText(const char* query, int page);
		std::vector<BsSong> searchText(std::string query, int max_sites = 10);
};

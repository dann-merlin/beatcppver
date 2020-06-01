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
		BsSearchResult *searchText(char* query, int page = 0);
};

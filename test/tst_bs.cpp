#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "beatcppver.h"
#include <string>

TEST_CASE("BeatCver") {
	auto &bs = BeatCver::getInstance();
	bs.init();
	bs.searchText(&(std::string("Avril Lavigne")[0]));
}

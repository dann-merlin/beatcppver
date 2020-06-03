#include "bs_search.h"
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static const std::string search_url = "/search";
static const std::string text_url = "/text";
static const std::string advanced_url = "/advanced";

void BsSearchResult::process_response(BsResponse response) {
	std::string content = response.responseText;
	json j = json::parse(content);
	auto json_results = j["docs"];
	for(auto json_entry : json_results) {
		BsSong song;

		// read stats
		auto stats = json_entry["stats"];
		song.stats.downloads = stats["downloads"];
		song.stats.plays = stats["plays"];
		song.stats.downVotes = stats["downVotes"];
		song.stats.upVotes = stats["upVotes"];
		song.stats.heat = stats["heat"];
		song.stats.rating = stats["rating"];

		// read metadata
		auto metadata = json_entry["metadata"];
		song.metadata.duration = metadata["duration"];
		song.metadata.levelAuthorName = metadata["levelAuthorName"];
		song.metadata.songAuthorName = metadata["songAuthorName"];
		song.metadata.songName = metadata["songName"];
		song.metadata.songSubName = metadata["songSubName"];
		song.metadata.bpm = metadata["bpm"];
		auto characteristics_list = metadata["characteristics"];
		for( auto characteristic : characteristics_list ) {
			BsSongCharacteristics bs_char;
			bs_char.name = characteristic["name"];

			auto json_difficulties = characteristic["difficulties"];
			for(json::iterator it = json_difficulties.begin(); it != json_difficulties.end(); it++) {
				bs_char.difficulties[it.key()];
				auto& diff_entry = bs_char.difficulties[it.key()];
				if(it.value().is_null()) {
					diff_entry.isNull = true;
				} else {
					auto difficulty = it.value();
					diff_entry.isNull = false;
					diff_entry.duration = difficulty["duration"];
					diff_entry.length = difficulty["length"];
					diff_entry.bombs = difficulty["bombs"];
					diff_entry.notes = difficulty["notes"];
					diff_entry.obstacles = difficulty["obstacles"];
					diff_entry.njs = difficulty["njs"];
					diff_entry.njsOffset = difficulty["njsOffset"];
				}
			}
			song.metadata.characteristics.push_back(bs_char);
		}
		auto difficulties = metadata["difficulties"];
		for(auto& it : difficulties.items()) {
			song.metadata.difficulties[it.key()] = it.value();
		}
		
		// read the rest
		song.description = json_entry["description"];
		song.deletedAt = (json_entry["deletedAt"].is_null()) ? "null" : json_entry["deletedAt"];
		song._id = json_entry["_id"];
		song.key = json_entry["key"];
		song.name = json_entry["name"];
		song.uploader_id = json_entry["uploader"]["_id"];
		song.uploaderUsername = json_entry["uploader"]["username"];
		song.hash = json_entry["hash"];
		song.uploaded = json_entry["uploaded"];
		song.directDownload = json_entry["directDownload"];
		song.downloadURL = json_entry["downloadURL"];
		song.coverURL = json_entry["coverURL"];
		results.push_back(song);
	}
	nextPage = j["nextPage"].is_null() ? false : true;
	prevPage = j["prevPage"].is_null() ? false : true;
	if(j["lastPage"].is_null()) {
		lastPage = 0;
	} else {
		lastPage = j["lastPage"];
	}
	totalEntries = j["totalDocs"];
}

BsSearchResult::BsSearchResult(const char* query, int page, BsSearchType type) {
	std::string typestring;
	switch (type) {
		case advanced:
			typestring = advanced_url;
			break;
		case text:
		default:
			typestring = text_url;
	}
	// TODO Option page == -1

	std::string querystring = search_url + typestring + "/" + std::to_string(page) + "?q=" + BsCurl::percentEscapeString(query);
	/* BsCurl::sendRequest(querystring); */
	auto response = BsCurl::sendRequest(querystring);
	if(response.returnCode != "200" ) {
		nextPage = false;
		return;
	}
	process_response(response);
}

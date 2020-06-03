#pragma once

#include <cstring>
#include<map>
#include <string>
#include<vector>

struct BsSongDifficulty {
	bool isNull;
	double duration;
	int length, njs, njsOffset, bombs, notes, obstacles;
};

struct BsSongCharacteristics {
	std::string name;
	std::map<std::string, BsSongDifficulty> difficulties;
};

struct BsSongMetadata {
	std::map<std::string, bool> difficulties;
	std::vector<BsSongCharacteristics> characteristics;
	unsigned long duration;
	std::string levelAuthorName, songAuthorName, songName, songSubName;
	int bpm;
};

struct BsSongStats {
	unsigned long downloads, plays, downVotes, upVotes;
	double heat, rating;
};

struct BsSong {
	BsSongMetadata metadata;
	BsSongStats stats;
	std::string description, deletedAt, _id, key, name;
	std::string uploader_id, uploaderUsername;
	std::string hash, uploaded, directDownload, downloadURL, coverURL;
};

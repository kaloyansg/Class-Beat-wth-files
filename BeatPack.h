#pragma once
#include "Beat.h"

class BeatPack
{
public:
	BeatPack();
	BeatPack(const Beat*, size_t);
	BeatPack(const BeatPack&);
	BeatPack& operator=(const BeatPack&);
	~BeatPack();

	void addBeat(const Beat&);

	void saveAsText(const char*);
	void getFromText(const char*);
	void saveAsBinary(const char*);
	void getFromBinary(const char*);

private:
	Beat* beats;
	size_t number;
	size_t capacity;

	void resize();
};


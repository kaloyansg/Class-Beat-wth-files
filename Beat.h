#pragma once
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

enum class Genre
{
	Drill,
	Trap,
	Country,
	BoomBap,
	Other
};

class Beat
{
public:
	Beat();
	Beat(const char*, size_t, double, const char*);
	Beat(const Beat&);
	Beat& operator=(const Beat&);
	~Beat();

	void saveAsText(std::ofstream&) const;
	void getFromText(std::ifstream&);

	void saveAsBinary(std::ofstream&) const;
	void getFromBinary(std::ifstream&);

private:
	char* name;
	size_t duration; //< 240
	double price;
	Genre genre;
};


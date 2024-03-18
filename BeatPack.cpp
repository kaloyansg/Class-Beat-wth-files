#include "BeatPack.h"
#include <fstream>

BeatPack::BeatPack()
{
	beats = new Beat[1];
	number = 0;
	capacity = 1;
}

BeatPack::BeatPack(const Beat* beats, size_t number)
{
	this->beats = new Beat[number];
	for (size_t i = 0; i < number; ++i)
	{
		this->beats[i] = beats[i];
	}
	this->number = number;
	this->capacity = number;
}

BeatPack::BeatPack(const BeatPack& other)
{
	beats = new Beat[other.capacity];
	for (size_t i = 0; i < other.number; ++i)
	{
		beats[i] = other.beats[i];	
	}
	number = other.number;
	capacity = other.capacity;
}

BeatPack& BeatPack::operator=(const BeatPack& other)
{
	if (this == &other)
		return *this;

	Beat* tempBeats = new Beat[other.capacity];
	for (size_t i = 0; i < other.number; ++i)
	{
		tempBeats[i] = other.beats[i];
	}

	delete[] beats;
	beats = tempBeats;
	number = other.number;
	capacity = other.capacity;

	return *this;
}

BeatPack::~BeatPack()
{
	delete[] beats;
}

void BeatPack::addBeat(const Beat& beat)
{
	resize();
	beats[number] = beat;
	++number;
}

void BeatPack::saveAsText(const char* fileName)
{
	std::ofstream file(fileName);
	if (!file)
		throw "File not loaded";

	for (size_t i = 0; i < number; ++i)
	{
		beats[i].saveAsText(file);
		file << '\n';
	}
	file.close();
}

void BeatPack::getFromText(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file)
		throw "File not loaded";

	Beat temp;

	try
	{
		while (!file.eof())
		{
			temp.getFromText(file);
			this->addBeat(temp);
		}
	}
	catch (...) {}
}

void BeatPack::saveAsBinary(const char* fileName)
{
	std::ofstream file(fileName, std::ios::binary);
	if (!file)
		throw "File not loaded";

	for (size_t i = 0; i < number; ++i)
	{
		beats[i].saveAsBinary(file);
	}
	file.close();
}

void BeatPack::getFromBinary(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file)
		throw "File not loaded";

	Beat temp;
	try
	{
		while (!file.eof())
		{
			temp.getFromBinary(file);
			this->addBeat(temp);
		}
	}
	catch (...) {}
	file.close();
}

void BeatPack::resize()
{
	if (number < capacity)
		return;

	Beat* temp = new Beat[capacity * 2];
	for (size_t i = 0; i < number; ++i)
	{
		temp[i] = beats[i];
	}
	delete[] beats;
	beats = temp;
	capacity *= 2;
}

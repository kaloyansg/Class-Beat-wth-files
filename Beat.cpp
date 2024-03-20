#include "Beat.h"

Beat::Beat()
{
	name = new char[strlen("Beat") + 1];
	strcpy(name, "Beat");
	duration = 0;
	price = 0;
	genre = Genre::Other;
}

Beat::Beat(const char* name, size_t duration, double price, const char* genre)
{
	if (!name || strlen(name) == 0)
	{
		this->name = new char[strlen("Beat") + 1];
		strcpy(this->name, "Beat");
	}


	if (duration > 240)
		throw "Invalid duration";
	if (price < 0)
		price *= -1;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->duration = duration;
	this->price = price;

	if (strcmp(genre, "Drill") == 0)
		this->genre = Genre::Drill;
	else if (strcmp(genre, "Trap") == 0)
		this->genre = Genre::Trap;
	else if (strcmp(genre, "Country") == 0)
		this->genre = Genre::Country;
	else if (strcmp(genre, "BoomBap") == 0)
		this->genre = Genre::BoomBap;
	else
		this->genre = Genre::Other;
}

Beat::Beat(const Beat& other) : duration(other.duration), price(other.price)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	genre = other.genre;
}

Beat& Beat::operator=(const Beat& other)
{
	if (this == &other)
		return *this;

	char* tempName = new char[strlen(other.name) + 1];
	strcpy(tempName, other.name);
	
	delete[] name;
	name = tempName;

	duration = other.duration;
	price = other.price;
	genre = other.genre;
	return *this;
}

Beat::~Beat()
{
	delete[] name;
}

void Beat::saveAsText(std::ofstream& file) const
{
	file << name << ", " << duration << ", " << price << ", ";
	switch (genre)
	{
	case Genre::Drill: file << "Drill";
		break;
	case Genre::Trap: file << "Trap";
		break;
	case Genre::Country: file << "Country";
		break;
	case Genre::BoomBap: file << "BoomBap";
		break;
	case Genre::Other: file << "Other";
		break;
	}
}

void Beat::getFromText(std::ifstream& file)
{
	char tempName[129];
	file.getline(tempName, 128, ',');
	file.ignore();

	if (!file)
		throw "Invalid beat info";

	delete[] name;
	name = new char[strlen(tempName)+1];
	strcpy(name, tempName);

	file >> duration;
	file.ignore(); // for the ,
	file.ignore(); // for the space
	file >> price;
	file.ignore(); // for the ,
	file.ignore(); // for the space

	char genreText[129];
	file.getline(genreText, 128);
	if (strcmp(genreText, "Drill") == 0)
		genre = Genre::Drill;
	else if (strcmp(genreText, "Trap") == 0)
		genre = Genre::Trap;
	else if (strcmp(genreText, "Country") == 0)
		genre = Genre::Country;
	else if (strcmp(genreText, "BoomBap") == 0)
		genre = Genre::BoomBap;
	else
		genre = Genre::Other;

	if (!file)
		throw "Invalid beat info";
}

void Beat::saveAsBinary(std::ofstream& file) const
{
	size_t nameSize = strlen(name) + 1;
	file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	file.write(name, nameSize);
	file.write(reinterpret_cast<const char*>(this), sizeof(Beat));
}

void Beat::getFromBinary(std::ifstream& file)
{
	size_t nameSize;
	file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
	if (!file)
		throw "File not valid";
	char* tempName = new char[nameSize];
	file.read(tempName, nameSize);
	if (!file)
		throw "File not valid";

	file.read(reinterpret_cast<char*>(this), sizeof(Beat));
	if (!file)
		throw "File not valid";
	this->name = tempName;
}

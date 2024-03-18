#include <iostream>
#include <fstream>
#include "Beat.h"
#include "BeatPack.h"

int main()
{
	Beat a;
	Beat b("Brilla", 45, 35, "Drill");
	Beat c("Crap", 50, 55, "Trap");

	BeatPack pack;
	pack.addBeat(a);
	pack.addBeat(b);
	pack.addBeat(c);

	Beat arr[2];
	arr[0] = c;
	arr[1] = b;
	BeatPack pack2(arr, 2);

	pack.saveAsText("beatPack1.txt");
	pack.getFromText("beatPack1.txt");

	pack2.saveAsBinary("beatPack2.dat");
	pack2.getFromBinary("beatPack2.dat");
}

int main2()
{
    std::cout << "Hello World!\n";
    Beat a;
    Beat b("Brilla", 45, 35, "Drill");
	try
	{
		Beat c("C", 400, 400, "Drill");
	}
	catch (const char* err)
	{
		std::cerr << err;
	}
	Beat c("Crap", 50, 55, "Trap");


	Beat beats[3];
	beats[1] = b;
	beats[2] = c;

	std::ofstream file("beats.dat", std::ios::binary); //std::ofstream file("beats.txt");
	if (!file)
		return -1;
	for (size_t i = 0; i < 3; ++i)
	{
		beats[i].saveAsText(file);
		file << '\n';
	}
	file.close();


	Beat beatsCopy[3];
	std::ifstream file2("beats.dat", std::ios::binary); //std::ifstream file2("beats.txt");
	if (!file2)
		std::cerr << "File not found";
	else for (size_t i = 0; i < 3; ++i)
	{
		beatsCopy[i].getFromText(file2);
	}
	file2.close();
}

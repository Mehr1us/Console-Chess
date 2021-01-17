#include <stdlib.h>
#include <vector>
#include <string>

struct Tile;

class Log
{
public:
	std::vector<std::string>log;
	void print();
	void logMove(Tile s, Tile t, bool WhiteMove);
	bool hasLog = false;
	std::string logName;
};

extern Log L;
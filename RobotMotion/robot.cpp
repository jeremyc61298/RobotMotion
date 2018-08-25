#include <fstream>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

struct GridPoint
{
	char directionToMove;
	int instructionCount;
	bool visited;
};

int main()
{
	ifstream fin("robot.in");
	if (!fin.is_open)
	{
		return -1;
	}

	ofstream fout("robot.out");
	int rows, cols, x, y;

	fin >> rows >> cols >> x >> y;

	while (rows != 0 && cols != 0 && x != 0 && y != 0)
	{

	}

}

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

struct GridPoint
{
	char directionToMove;
	int instructionCount;
	bool visited = false;
};

struct RobotGrid
{
	vector<vector<GridPoint>> map;
	int rows, cols, x, y;
};

void initializeGrid(RobotGrid &grid, ifstream &fin)
{
	// Resize grid
	grid.map.resize(grid.rows);
	for (int i = 0; i < grid.map.size(); i++)
	{
		grid.map[i].resize(grid.cols);
	}
	
	// Fill Grid
	for (int i = 0; i < grid.rows; i++)
	{
		string line;
		getline(fin, line);
		for (int j = 0; j < grid.cols; j++)
		{
			grid.map[i][j].directionToMove = line[j];
		}
	}

}

int main()
{
	ifstream fin("robot.in");
	if (!fin.is_open())
	{
		return -1;
	}

	ofstream fout("robot.out");
	
	RobotGrid grid;

	fin >> grid.rows >> grid.cols >> grid.x >> grid.y;
	fin.ignore();

	while (grid.rows != 0 && grid.cols != 0 && grid.x != 0 && grid.y != 0)
	{
		initializeGrid(grid, fin);

		// Read in the next grid information
		fin >> grid.rows >> grid.cols >> grid.x >> grid.y;
		fin.ignore();
	}

}

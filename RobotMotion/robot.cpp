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

struct Point
{
	int x = 0;
	int y = 0;
};

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
	int numOfInstructions = 0;
	int loopSize = 0;
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

void traverseGrid(RobotGrid &grid)
{
	Point robot;
	bool finished = false;
	
	// Initialize the start point of the robot
	robot.x = grid.x;
	robot.y = grid.y;

	while (!finished)
	{
		if (robot.x < 0 || robot.x > grid.rows || robot.y < 0 || robot.y > grid.cols)
		{
			finished = true;
		}
		else if (grid.map[robot.x][robot.y].visited)
		{
			grid.loopSize = grid.numOfInstructions - grid.map[robot.x][robot.y].instructionCount;
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
		traverseGrid(grid);
		// Read in the next grid information
		fin >> grid.rows >> grid.cols >> grid.x >> grid.y;
		fin.ignore();
	}

}

// Robot Motion - robot.cpp
// Jeremy Campbell

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
	int y = 0;
	int x = 0;
};

struct GridPoint
{
	char directionToMove;
	int instructionCount;
	bool visited;
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
			grid.map[i][j].instructionCount = 0;
			grid.map[i][j].visited = false;
		}
	}

	// Erase remaining data from previous grids
	grid.loopSize = 0;
	grid.numOfInstructions = 0;
}

bool moveRobot(Point &robot, char directionToMove)
{
	bool result = true;
	switch (directionToMove)
	{
	case 'N':
		--robot.y;
		break;
	case 'E':
		++robot.x;
		break;
	case 'S':
		++robot.y;
		break;
	case 'W':
		--robot.x;
		break;
	default:
		cout << "Invalid direction. ";
		result = false;
	}
	return result;
}

void traverseGrid(RobotGrid &grid)
{
	Point robot;
	bool finished = false;
	
	// Initialize the start point of the robot and make first move
	robot.x = grid.x;
	robot.y = grid.y;
	grid.map[robot.y][robot.x].visited = true;
	if (!moveRobot(robot, grid.map[robot.y][robot.x].directionToMove))
	{
		finished = true;
		grid.loopSize = -1;
		cout << "Grid information: " << grid.rows << grid.cols << grid.y << grid.x << endl;
	}

	// Continue to traverse the grid
	while (!finished)
	{
		++grid.numOfInstructions;
		if (robot.y < 0 || robot.y > grid.rows - 1 || robot.x < 0 || robot.x > grid.cols - 1)
		{
			finished = true;
		}
		else if (grid.map[robot.y][robot.x].visited)
		{
			grid.loopSize = grid.numOfInstructions - grid.map[robot.y][robot.x].instructionCount;
			finished = true;
		}
		else
		{
			// Breadcrumb the spot, then attempt to move. If moving fails, write an error message
			// and mark the grid as failed with a -1.
			grid.map[robot.y][robot.x].visited = true;
			grid.map[robot.y][robot.x].instructionCount = grid.numOfInstructions;

			if (!moveRobot(robot, grid.map[robot.y][robot.x].directionToMove))
			{
				finished = true; 
				grid.loopSize = -1;
				cout << "Grid information: " << grid.rows << grid.cols << grid.y << grid.x << endl;
			}
		}
	}
}

void displayResults(RobotGrid &grid, ofstream &fout)
{
	if (grid.loopSize == 0)
	{
		fout << grid.numOfInstructions << " instruction";
		if (grid.numOfInstructions != 1)
		{
			fout << "s";
		}
		fout << " before exit";
	}
	else if (grid.loopSize == -1)
	{
		fout << "Error moving the robot.";
	}
	else 
	{
		fout << grid.numOfInstructions - grid.loopSize << " instruction";
		if (grid.numOfInstructions - grid.loopSize != 1)
		{
			fout << "s";
		}
		fout << " before a loop of " << grid.loopSize << " instruction";
		if (grid.loopSize != 1)
		{
			fout << "s";
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

	fin >> grid.rows >> grid.cols >> grid.y >> grid.x;
	fin.ignore();

	while (grid.rows != 0 && grid.cols != 0 && grid.x != 0 && grid.y != 0)
	{
		// Format to a zero base array
		--grid.y;
		--grid.x;
		initializeGrid(grid, fin);
		traverseGrid(grid);
		displayResults(grid, fout);
		// Read in the next grid information
		fin >> grid.rows >> grid.cols >> grid.y >> grid.x;
		if (grid.rows != 0 && grid.cols != 0 && grid.x != 0 && grid.y != 0)
		{
			fout << endl;
		}
		fin.ignore();
	}
}

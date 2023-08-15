#include <iostream>
#include <fstream>
#include <sstream>
#include "Maze.h"


int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	//get dat INPUT
	int height;
	int width;
	int layers;
	in >> height >> width >> layers;
	Maze myMaze = Maze(height, width, layers);
	std::string line;
	in.ignore();
	in.ignore();
	for (int i = 0; i < layers; ++i) {
		for (int j = 0; j < height; ++j) {
			getline(in, line);
			std::istringstream iss(line);
			for (int k = 0; k < width; ++k) {
				int value;
				iss >> value;
				myMaze.setValue(j, k, i, value);
			}
		}
		in.ignore(); //for the space between layers
	}

	//send dat OUTPUT
	out << "Solve Maze:" << std::endl;
	out << myMaze;
	if (!myMaze.find_maze_path()) { //one little function...just one...probably doesn't do anything...
		out << "No Solution Exists!" << std::endl;
	}
	else {
		out << "Solution:" << std::endl;
		out << myMaze;
	}

	in.close();
	out.close();

	return 0;
}

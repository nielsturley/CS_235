#include "Maze.h"
#include <string>
#include <iomanip>
#include <sstream>

/**WELCOME TO THE MAGICAL RECURSIVE FUNCTION
 * I DON'T KNOW HOW IT WORKS
 * SO I SURE HOPE YOU DO
 * :) */
bool Maze::rec_find_maze_path(int h, int w, int l) {
	if (out_of_bounds_check(h, w, l) || maze[h][w][l] == BLOCKED || maze[h][w][l] == VISITED) return false; //these are the bad stuff
	if (maze[h][w][l] == EXIT) return true; //this is what begins the recursive call-back
	maze[h][w][l] = VISITED;

	//now all the checks begin.
	if (rec_find_maze_path(CHECK_LEFT)) {
		maze[h][w][l] = LEFT;
		return true;
	}
	if (rec_find_maze_path(CHECK_RIGHT)) {
		maze[h][w][l] = RIGHT;
		return true;
	}
	if (rec_find_maze_path(CHECK_UP)) {
		maze[h][w][l] = UP;
		return true;
	}
	if (rec_find_maze_path(CHECK_DOWN)) {
		maze[h][w][l] = DOWN;
		return true;
	}
	if (rec_find_maze_path(CHECK_OUT)) {
		maze[h][w][l] = OUT;
		return true;
	}
	if (rec_find_maze_path(CHECK_IN)) {
		maze[h][w][l] = IN;
		return true;
	}
	return false; //if none of the checks work, you lost. :(
}

/**this is mostly for the output
 * it reads the value (stored as the enum, but also is represented by the int)
 * and translates it into the symbol*/
char Maze::interpretValue(int value) const {
	switch(value) {
		case 0:
			return '_';
		case 1:
			return 'X';
		case 2:
			return '*';
		case 3:
			return 'E';
		case 4:
			return 'L';
		case 5:
			return 'R';
		case 6:
			return 'U';
		case 7:
			return 'D';
		case 8:
			return 'O';
		case 9:
			return 'I';
		default:
			return '\0';
	}
}

//learning to code is like learning to play an instrument
//so many strings
//:)
std::string Maze::toString() const {
	std::stringstream out;
	for (int i = 0; i < layer; ++i) {
		out << "Layer " << std::to_string(i + 1) << std::endl;
		for (int j = 0; j < height; ++j) {
			for (int k = 0; k < width; ++k) {
				out << " " << interpretValue(maze[j][k][i]);
			}
			out << std::endl;
		}
	}
	out << std::endl;
	return out.str();
}
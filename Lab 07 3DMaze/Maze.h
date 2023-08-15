#ifndef LAB_07_3DMAZE_MAZE_H
#define LAB_07_3DMAZE_MAZE_H

#include "MazeInterface.h"

//all the definition stuff
enum CellValue_t { OPEN, BLOCKED, VISITED, EXIT, LEFT, RIGHT, UP, DOWN, OUT, IN };
#define CHECK_LEFT h,w-1,l
#define CHECK_RIGHT h,w+1,l
#define CHECK_UP h-1,w,l
#define CHECK_DOWN h+1,w,l
#define CHECK_OUT h,w,l-1
#define CHECK_IN h,w,l+1

class Maze : public MazeInterface {
private:
	int*** maze; //I want to see what the longest feasible stretch of pointers is
	int height;
	int width;
	int layer;
public:
	Maze(int height, int width, int layer) {
		this->height = height;
		this->width = width;
		this->layer = layer;
		makeMaze(); //he said something about this in lecture, but I'm pretty sure I'm not doing this right
	}

	/** anyway, all it does is create the 3D array*/
	void makeMaze() {
		maze = new int**[height];
		for (int i = 0; i < height; ++i) {
			maze[i] = new int*[width];
			for (int j = 0; j < width; ++j) {
				maze[i][j] = new int[layer];
			}
		}
	}

	~Maze() {
		/**just DELETE already*/
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				delete [] maze[i][j];
			}
			delete [] maze[i];
		}
		delete [] maze;
	}

	void setValue(int height, int width, int layer, int value) {
		if (value == 0) {
			maze[height][width][layer] = OPEN;
		}
		if (value == 1) {
			maze[height][width][layer] = BLOCKED;
		}
	}

	bool find_maze_path() {
		maze[height-1][width-1][layer-1] = EXIT; //put the exit definition here so it wouldn't get mixed up in the initial output
		return rec_find_maze_path(0, 0, 0); //SO IT BEGINS
	}

	bool rec_find_maze_path(int h, int w, int l);

	bool out_of_bounds_check(int h, int w, int l) {
		if (h < 0 || w < 0 || l < 0 || h >= height || w >= width || l >= layer) {
			return true;
		}
		else {
			return false;
		}
	}

	friend std::ostream& operator<< (std::ostream& os, const Maze& maze) {
		os << maze.toString();
		return os;
	}

	std::string toString() const;

	char interpretValue(int value) const;



};



#endif //LAB_07_3DMAZE_MAZE_H

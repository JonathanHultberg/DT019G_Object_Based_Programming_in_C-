//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"

bool Maze::dfs_solver(int r, int c) {
	grid[r][c].visited = true;
	
	// Stopvilkor för rekursionen
	if (grid[r][c].is_end) {
		grid[r][c].is_on_path = true;
		return true;
	}

	for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
		int next_r = r;
		int next_c = c;
		move(next_r, next_c, dir);

		if (is_valid_move(next_r, next_c) && can_move(r, c, next_r, next_c, dir)) {
			if (dfs_solver(next_r, next_c)) {
				grid[r][c].is_on_path = true; //Bara markera väg om rätt väg hittas
				return true;
			}
		}
	}

	return false;
}

// Kontrollerar att den ej går genom en vägg
bool Maze::can_move(int r, int c, int next_r, int next_c, Direction dir) const {
	switch (dir) {
	case Direction::UP:
		return !grid[r][c].up && !grid[next_r][next_c].down;
	case Direction::DOWN:
		return !grid[r][c].down && !grid[next_r][next_c].up;
	case Direction::LEFT:
		return !grid[r][c].left && !grid[next_r][next_c].right;
	case Direction::RIGHT:
		return !grid[r][c].right && !grid[next_r][next_c].left;
	default:
		return false;
	}
}


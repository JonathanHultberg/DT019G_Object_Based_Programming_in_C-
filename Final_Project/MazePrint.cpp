//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"

void Maze::print_maze() {
	for (int r = 0; r < rows; ++r) {
		// Rita toppväggar
		for (int c = 0; c < cols; ++c) {
			std::cout << "+";
			if (grid[r][c].up) {
				std::cout << "---";
			}
			else {
				if (grid[r][c].is_start && r == 0 && grid[r][c].wall_position == ExitWall::EXIT_UP) {
					std::cout << " S ";
				}
				else if (grid[r][c].is_end && r == 0 && grid[r][c].wall_position == ExitWall::EXIT_UP) {
					std::cout << " E ";
				}
				else {
					std::cout << "   ";
				}
			}
		}
		std::cout << "+\n";

		// Rita vänstervägg + utrymme + högerkant
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c].left) {
				std::cout << "|";
			}
			else {
				if (grid[r][c].is_start && c == 0 &&
					(grid[r][c].wall_position == ExitWall::EXIT_LEFT || grid[r][c].wall_position == ExitWall::EXIT_RIGHT)) {
					std::cout << "S";
				}
				else if (grid[r][c].is_end && c == 0 &&
					(grid[r][c].wall_position == ExitWall::EXIT_LEFT || grid[r][c].wall_position == ExitWall::EXIT_RIGHT)) {
					std::cout << "E";
				}
				else {
					std::cout << " ";
				}
			}
			if (grid[r][c].is_on_path) {
				std::cout << " * ";
			}
			else {
				std::cout << "   ";
			}
		}

		// Sista högerkant
		if (grid[r][cols - 1].right) {
			std::cout << "|\n";
		}
		else {
			if (grid[r][cols - 1].is_start && grid[r][cols - 1].wall_position == ExitWall::EXIT_RIGHT) {
				std::cout << "S\n";
			}
			else if (grid[r][cols - 1].is_end && grid[r][cols - 1].wall_position == ExitWall::EXIT_RIGHT) {
				std::cout << "E\n";
			}
			else {
				std::cout << " \n";
			}
		}
	}

	// Rita nedersta horisontella väggen
	for (int c = 0; c < cols; ++c) {
		std::cout << "+";
		if (grid[rows - 1][c].down) {
			std::cout << "---";
		}
		else {
			if (grid[rows - 1][c].is_start && grid[rows - 1][c].wall_position == ExitWall::EXIT_DOWN) {
				std::cout << " S ";
			}
			else if (grid[rows - 1][c].is_end && grid[rows - 1][c].wall_position == ExitWall::EXIT_DOWN) {
				std::cout << " E ";
			}
			else {
				std::cout << "   ";
			}
		}
	}
	std::cout << "+\n";
}
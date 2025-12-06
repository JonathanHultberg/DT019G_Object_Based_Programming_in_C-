//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"


void Maze::choose_start_end() {
	std::pair<int, int> start;
	std::pair<int, int> end;

	std::uniform_int_distribution<int> wall_dist(0, 3);

	Wall start_wall = static_cast<Wall>(wall_dist(gen));
	start = choose_position(start_wall);

	Wall end_wall;

	// Ser till att start och slut hamnar på olika väggar
	do {
		end_wall = static_cast<Wall>(wall_dist(gen));
		end = choose_position(end_wall);
	} while (start_wall == end_wall || start == end);

	grid[start.first][start.second].is_start = true;
	grid[end.first][end.second].is_end = true;

	mark_exit_wall(start, start_wall);
	mark_exit_wall(end, end_wall);
}

// Randomiserar kordinater utefter väggen
std::pair<int, int> Maze::choose_position(Wall wall_dir) {
	std::uniform_int_distribution<int> row_dist(0, rows - 1);
	std::uniform_int_distribution<int> col_dist(0, cols - 1);

	int r;
	int c;

	switch (wall_dir) {
	case Wall::UP_WALL:
		r = 0;
		c = col_dist(gen);
		break;
	case Wall::DOWN_WALL:
		r = rows - 1;
		c = col_dist(gen);
		break;
	case Wall::LEFT_WALL:
		r = row_dist(gen);
		c = 0;
		break;
	case Wall::RIGHT_WALL:
		r = row_dist(gen);
		c = cols - 1;
		break;
	}
	return std::make_pair(r, c);
}

// Markerar väggen som utgång så inte hör får dubbla S eller E
void Maze::mark_exit_wall(std::pair<int, int> pos, Wall dir) {
	switch (dir) {
	case Wall::UP_WALL:
		grid[pos.first][pos.second].wall_position = ExitWall::EXIT_UP;
		grid[pos.first][pos.second].up = false;
		break;
	case Wall::DOWN_WALL:
		grid[pos.first][pos.second].wall_position = ExitWall::EXIT_DOWN;
		grid[pos.first][pos.second].down = false;
		break;
	case Wall::LEFT_WALL:
		grid[pos.first][pos.second].wall_position = ExitWall::EXIT_LEFT;
		grid[pos.first][pos.second].left = false;
		break;
	case Wall::RIGHT_WALL:
		grid[pos.first][pos.second].wall_position = ExitWall::EXIT_RIGHT;
		grid[pos.first][pos.second].right = false;
		break;
	}
}

// Tar bort väggen för S och E, behöver tas bort för att print logik ska fungera
void Maze::set_exit_wall(int r, int c) {
	if (r == 0 && c == 0) {
		std::vector<ExitWall> walls = { ExitWall::EXIT_UP, ExitWall::EXIT_LEFT };
		std::shuffle(walls.begin(), walls.end(), gen);
		grid[r][c].wall_position = walls[0];

		if (grid[r][c].wall_position == ExitWall::EXIT_UP) {
			grid[r][c].up = false;
		}
		else {
			grid[r][c].left = false;
		}
		return;
	}
	else if (r == 0 && c == cols - 1) {
		std::vector<ExitWall> walls = { ExitWall::EXIT_UP, ExitWall::EXIT_RIGHT };
		std::shuffle(walls.begin(), walls.end(), gen);
		grid[r][c].wall_position = walls[0];
		if (grid[r][c].wall_position == ExitWall::EXIT_UP) {
			grid[r][c].up = false;
		}
		else {
			grid[r][c].right = false;
		}
		return;
	}
	else if (r == rows - 1 && c == 0) {
		std::vector<ExitWall> walls = { ExitWall::EXIT_DOWN, ExitWall::EXIT_LEFT };
		std::shuffle(walls.begin(), walls.end(), gen);
		grid[r][c].wall_position = walls[0];
		if (grid[r][c].wall_position == ExitWall::EXIT_DOWN) {
			grid[r][c].down = false;
		}
		else {
			grid[r][c].left = false;
		}
		return;
	}
	else if (r == rows - 1 && c == cols - 1) {
		std::vector<ExitWall> walls = { ExitWall::EXIT_DOWN, ExitWall::EXIT_RIGHT };
		std::shuffle(walls.begin(), walls.end(), gen);
		grid[r][c].wall_position = walls[0];
		if (grid[r][c].wall_position == ExitWall::EXIT_DOWN) {
			grid[r][c].down = false;
		}
		else {
			grid[r][c].right = false;
		}
		return;
	}

	// Kantspecifik hantering (ej hörn)
	if (r == 0) {
		grid[r][c].wall_position = ExitWall::EXIT_UP;
		grid[r][c].up = false;
	}
	else if (r == rows - 1) {
		grid[r][c].wall_position = ExitWall::EXIT_DOWN;
		grid[r][c].down = false;
	}
	else if (c == 0) {
		grid[r][c].wall_position = ExitWall::EXIT_LEFT;
		grid[r][c].left = false;
	}
	else if (c == cols - 1) {
		grid[r][c].wall_position = ExitWall::EXIT_RIGHT;
		grid[r][c].right = false;
	}
	else {
		std::cerr << "Fel: Positionen (" << r << "," << c << ") ligger inte på yttervägg!\n";
	}
}
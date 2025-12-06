//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"

void Maze::dfs_generation(int r, int c) {
	grid[r][c].visited = true;

	std::vector<Direction> directions = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
	std::shuffle(directions.begin(), directions.end(), gen); // Randomisera riktningarna

	for (Direction dir : directions) {
		int next_r = r;
		int next_c = c;
		move(next_r, next_c, dir);
		if (is_valid_move(next_r, next_c)) {
			remove_wall(grid[r][c], grid[next_r][next_c], dir);
			dfs_generation(next_r, next_c);
		}
	}
}

void Maze::prims_generation(int r, int c) {
	std::vector<Direction> directions = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
	std::vector<frontier_entry> frontier;

	grid[r][c].visited = true;

	//Lägger till första grannarna för att kunna kickstarta algoritmen
	add_neighbor_to_frontier(r, c, frontier);

	while (!frontier.empty()) {
		std::shuffle(frontier.begin(), frontier.end(), gen); //Randomisera vilken granne som väljs
		frontier_entry next_node = frontier.back();
		frontier.pop_back();

		remove_wall(grid[next_node.from_r][next_node.from_c],
			grid[next_node.r][next_node.c], next_node.from_dir);

		grid[next_node.r][next_node.c].visited = true;
		grid[next_node.r][next_node.c].is_in_frontier = false;

		add_neighbor_to_frontier(next_node.r, next_node.c, frontier);
	}
}

// Hjälpfunktion till Prims för att följa DRY och inte upprepa 2 identiska kodblock
void Maze::add_neighbor_to_frontier(int r, int c, std::vector<frontier_entry>& frontier) {
	std::vector<Direction> directions = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
	for (Direction dir : directions) {
		int next_r = r;
		int next_c = c;
		move(next_r, next_c, dir);
		if (is_valid_move(next_r, next_c) && !grid[next_r][next_c].is_in_frontier) {
			grid[next_r][next_c].is_in_frontier = true;
			frontier.push_back(frontier_entry(next_r, next_c, r, c, dir));
		}
	}
}

// För att ta bort väggar för att skapa en väg mellan två noder
void Maze::remove_wall(node& current, node& next, Direction dir) {
	switch (dir) {
	case Direction::UP:
		current.up = false;
		next.down = false;
		break;
	case Direction::DOWN:
		current.down = false;
		next.up = false;
		break;
	case Direction::LEFT:
		current.left = false;
		next.right = false;
		break;
	case Direction::RIGHT:
		current.right = false;
		next.left = false;
		break;
	}
}

// För att ge nya kordinater för nästa förflyttning baserat på randomiserad riktning
void Maze::move(int& r, int& c, Direction dir) {
	switch (dir) {
	case Direction::UP:
		--r;
		break;
	case Direction::DOWN:
		++r;
		break;
	case Direction::LEFT:
		--c;
		break;
	case Direction::RIGHT:
		++c;
		break;
	}
}

// Kontroll så att algoritmen inte går utanför gränserna eller besöker en nod som redan är besökt
bool Maze::is_valid_move(int r, int c) const {
	if (r < 0 || r >= rows || c < 0 || c >= cols) {
		return false;
	}
	else {
		return !grid[r][c].visited;
	}
}

// Nollställer maze instansen så att man kan generera ny labyrint i samma objekt
void Maze::reset_maze() {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			grid[r][c].visited = false;
			grid[r][c].is_in_frontier = false;
			grid[r][c].is_start = false;
			grid[r][c].is_end = false;
			grid[r][c].wall_position = ExitWall::EXIT_NONE;
			grid[r][c].is_on_path = false;
			grid[r][c].up = true;
			grid[r][c].down = true;
			grid[r][c].left = true;
			grid[r][c].right = true;
		}
	}
}
//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"
//För att kunna skapa maze utan att ange storlek, för stdin
Maze::Maze() : rows(0), cols(0), generation_method(GenerationMethod::NONE) {
	// Genererar seed för randomisering baserat på datorns klocka
	std::random_device seed;
	gen = std::mt19937(seed());
}

Maze::Maze(int r, int c) : rows(r), cols(c), generation_method(GenerationMethod::NONE) {
	// Genererar seed för randomisering baserat på datorns klocka
	std::random_device seed;
	gen = std::mt19937 (seed());
	
	grid.reserve(rows);
	for (int r = 0; r < rows; ++r) {
		std::vector<node> row;
		row.reserve(cols);
		for (int c = 0; c < cols; ++c) {
			row.emplace_back(r, c);
		}
		grid.push_back(std::move(row));
	}
}
// Retunerar bool för att kunna användas som vilkor, så att en ogiltig labyrint inte försöker skrivas ut
bool Maze::load_from_stdin() {
	std::vector<std::string> lines;
	std::string line;
	int line_num = 0;

	//För att kunna beräkna kolumer och rader
	while (std::getline(std::cin, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}


	if (!is_valid_input(lines)) {
		return false;
	}

	//Beräknar noder, eftersom en node omsluts av 8 väggpositioner
	rows = static_cast<int> (lines.size() - 1) / 2;
	cols = static_cast<int> (lines[0].size() - 1) / 2;

	bool found_start = false;
	bool found_end = false;

	grid.resize(rows, std::vector<node>(cols)); //Skapar en 2D-vektor av noder

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			grid[r][c] = node(r, c);

			// Beräknar kordinater för att kunna skanna runt om noden i den ursprungliga inmatningen
			int text_r = r * 2 + 1;
			int text_c = c * 2 + 1;

			//Kollar om node är S/E
			if (lines[text_r][text_c] == 'S') {
				found_start = true;
				grid[r][c].is_start = true;
				set_exit_wall(r, c);

			}
			else if (lines[text_r][text_c] == 'E') {
				found_end = true;
				grid[r][c].is_end = true;
				set_exit_wall(r, c);
			}

			// Kollar om de finns väggar runt noden
			if (std::isspace(lines[text_r - 1][text_c])) {
				grid[r][c].up = false;
			}
			if (std::isspace(lines[text_r + 1][text_c])) {
				grid[r][c].down = false;
			}
			if (std::isspace(lines[text_r][text_c - 1])) {
				grid[r][c].left = false;
			}
			if (std::isspace(lines[text_r][text_c + 1])) {
				grid[r][c].right = false;
			}

		}
	}

	//Säkerställer att en start och en slut node finns
	if (!found_start) {
		std::cerr << "Startpunkt (S) saknas i inmatningen!" << std::endl;
		return false;
	}
	if (!found_end) {
		std::cerr << "Slutpunkt (E) saknas i inmatningen!" << std::endl;
		return false;
	}

	return true;
}

// Kontrollerar att inmatningen är en giltig labyrint
bool Maze::is_valid_input(const std::vector<std::string>& lines) const {
	if (lines.empty()) {
		std::cerr << "Felaktig inmatning: tom inmatning!" << std::endl;
		return false;
	}
	if (lines.size() < 3) {
		std::cerr << "Felaktig inmatning: för få rader!" << std::endl;
		return false;
	}

	for (std::string s : lines) {
		if (s.size() < 3) {
			std::cout << "Felaktig inmatning: för kort rad!" << std::endl;
			return false;
		}
		if (s.size() != lines[0].size()) {
			std::cout << "Felaktig inmatning: raderna har olika längd!" << std::endl;
			return false;
		}
	}

	return true;
}

// Wrapper för DFS generation, som randomiserar start och nollställer noder
void Maze::generate_maze_dfs() {
	reset_maze();

	std::uniform_int_distribution<int> row_dist(0, rows - 1);
	std::uniform_int_distribution<int> col_dist(0, cols - 1);

	int r = row_dist(gen);
	int c = col_dist(gen);

	dfs_generation(r, c);

	choose_start_end();

	generation_method = GenerationMethod::DFS;	
}

//Wrapper för Prims's generation, som randomiserar start och nollställer noder
void Maze::generate_maze_prims() {
	reset_maze();

	std::uniform_int_distribution<int> row_dist(0, rows - 1);
	std::uniform_int_distribution<int> col_dist(0, cols - 1);

	int r = row_dist(gen);
	int c = col_dist(gen);

	prims_generation(r, c);

	choose_start_end();

	generation_method = GenerationMethod::PRIMS;
}

// Wrapper för DFS-lösning, som nollställer medlemar i noder som väsentliga och letar efter startpunkten
bool Maze::solve_maze_dfs() {
	// Återställ visited och path-markeringar
	for (std::vector<node>& row : grid) {
		for (node& n : row) {
			n.visited = false;
			n.is_on_path = false;
		}
	}

	// Leta upp startpunkten och påbörja DFS
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c].is_start) {
				return dfs_solver(r, c);
			}
		}
	}

	// Om ingen start hittades — borde inte hända, men säkrare att hantera
	std::cerr << "Ingen startpunkt hittades i labyrinten.\n";
	return false;
}


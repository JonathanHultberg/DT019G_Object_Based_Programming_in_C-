//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Maze.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
	// För att kunna använda stdin för inläsning och lösning av labyrint.
	if (argc == 2 && std::string(argv[1]) == "--solve") {
		Maze maze;
		if (maze.load_from_stdin()) {
			if (maze.solve_maze_dfs()) {
				maze.print_maze();
			}
			else {
				std::cerr << "Ingen lösning hittades." << std::endl;
			}
		}
		else {
			std::cerr << "Misslyckades med att läsa labyrinten från standard input." << std::endl;
		}

		return 0;
	}

	// Meny för programmet
	Menu menu;
	menu.main_menu();
	
	return 0;
}
//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#include "Menu.h"
void Menu::main_menu() {
	bool running = true;
	int alt = 0;
	empty_term(); // "Rensar terminalen"
	do {
		// För att skriva ut labyrint ovanför menyn, men ändast om de finns något att skriva ut
		if (!mazes.empty() && (active_index >=0 && active_index < mazes.size())) {
			std::cout << "Current maze: " << active_index + 1 << " | Generation: " << generation << "\n\n";
			mazes[active_index].print_maze();
		}

		std::cout << "\n\nChoose option: "
			<< "\n1. Generate maze with DFS"
			<< "\n2. Generate maze with Prim's algorithm"
			<< "\n3. Solve maze with DFS"
			<< "\n4. Switch maze"
			<< "\n5. Generate new maze with DFS (overwrite current)"
			<< "\n6. Generate new maze with Prim's algorithm (overwrite current)"
			<< "\n7. Delete the currently active maze"
			<< "\n8. Exit"
			<< "\n> ";

		std::cin >> alt;
		
		// Kontrollera om inmatningen är giltig
		if (std::cin.fail())
		{
			empty_term();
			std::cin.clear();
			std::cin.ignore();
			std::cerr << "Invalid input! Please enter a number between 1 and 4.\n";
		}

		switch (alt)
		{
		case 1:
			generation_in_use = "DFS";
			if (creat_maze()) {
				mazes[active_index].generate_maze_dfs();
				generation = "DFS";
			}
			empty_term();
			break;
		case 2:
			generation_in_use = "PRIM";
			if (creat_maze()) {
				mazes[active_index].generate_maze_prims();
				generation = "Prim's algorithm";
			}
			empty_term();	
			break;
		case 3:
			empty_term();
			if (active_index >= 0 && active_index < mazes.size()) {
				if (mazes[active_index].solve_maze_dfs()) {
				}
				else {
					std::cerr << "No solution found.\n";
				}
			}
			else {
				std::cerr << "No maze available to solve.\n";
			}
			break;
		case 4:
			empty_term();
			switch_maze();
			empty_term();
			break;
		case 5:
			if (active_index >= 0 && active_index < mazes.size()) {
				mazes[active_index].generate_maze_dfs();
				generation = "DFS";
				empty_term();
			}
			else {
				empty_term();
				std::cerr << "No maze available to overwrite.\n";
			}
			break;
		case 6:
			if (active_index >= 0 && active_index < mazes.size()) {
				mazes[active_index].generate_maze_prims();
				generation = "Prim's algorithm";
				empty_term();	
			}
			else {
				empty_term();
				std::cerr << "No maze available to overwrite.\n";
			}
			break;
		case 7:
			empty_term();
			if (active_index >= 0 && active_index < mazes.size()) {
				mazes.erase(mazes.begin() + active_index);

				if (mazes.empty()) {
					active_index = -1;
				}
				else if (active_index >= mazes.size()) {
					active_index = static_cast<int> (mazes.size()) - 1;
				}

			}
			else {
				std::cerr << "Cannot delete – no maze is currently loaded.\n";
			}
			break;
		case 8:
			running = false;
			break;
		default:
			std::cout << "Please enter a number between 1 and 4.\n";
			break;
		}

	} while (running);
}

bool Menu::creat_maze() {
	int rows = 0;
	int cols = 0;
	empty_term();

	do {
		if (generation_in_use == "DFS") {
			std::cout << "Generating maze with DFS...\n"
				<< "\nRestriction: The maze cannot exceed 40 rows or 40 columns.\n";
		}
		else if (generation_in_use == "PRIM") {
			std::cout << "Generating maze with Prim's algorithm...\n"
				<< "Restriction: The maze cannot exceed 40 rows or 40 columns.\n";
		}
		

		std::cout << "Enter number of rows: ";
		std::cin >> rows;
		
		// Går inte vidare till nästa inmatning om inmatningen är ogiltig, för att slippa att de ser stökigt ut
		if (!std::cin.fail()) {
			std::cout << "Enter number of columns: ";
			std::cin >> cols;
		}
		
		// Kontrollera om inmatningen är giltig
		if (std::cin.fail() || rows <= 0 || cols <= 0) {
			empty_term();
			std::cerr << "Invalid input! Please enter positiv integers greater than zero for rows and columns.\n";
			std::cin.clear();
			std::cin.ignore();
			rows = cols = 0; 

		}
		
		// Meddelande till användare om de skulle mata in felaktiga heltal
		if ((rows <= 0 || cols <= 0) && !std::cin.fail()) {
			empty_term();
			std::cout << "Please enter positive integers greater than zero for rows and columns.\n";
		}

		if (rows > 40 || cols > 40) {
			empty_term();
			std::cout << "The maze cannot exceed 40 rows or 40 columns.\n";
			rows = cols = 0; // Återställ värdena för att undvika att skapa en labyrint med ogiltiga dimensioner
		}

	} while (rows <= 0 || cols <= 0);

	mazes.emplace_back(rows, cols);
	active_index = static_cast<int>(mazes.size()) - 1; // För att visa den senate skapade labyrinten i menysystem

	if (rows == 1 && cols == 1) {
		return false;
	}
	else {
		return true;
	}
}

void Menu::switch_maze() {
	if (mazes.empty()) {
		std::cout << "No mazes available to switch. Press enter to continue...\n";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	else if (mazes.size() == 1) {
		std::cout << "Only one maze available. No need to switch. Press enter to continue...\n";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	else {
		int choice = 0;
		do {
			std::cout << "Available mazes:\n";
			for (size_t i = 0; i < mazes.size(); ++i) {
				std::cout << i + 1 << ". Maze " << i + 1 << "\n";
			}
			std::cout << "Enter the number of the maze you want to switch to: ";
			std::cin >> choice;

			// Kontrollera om inmatningen är giltig
			if (std::cin.fail() || choice < 1 || choice > static_cast<int>(mazes.size())) {
				std::cin.clear();
				std::cin.ignore();
				empty_term();
				std::cerr << "Invalid input! Please enter a number between 1 and " << mazes.size() << ".\n";
			}

			// Kontrollera om användaren har matat in ett ogiltigt tal
			if (!std::cin.fail() && (choice < 1 || choice > static_cast<int>(mazes.size()))) {
				empty_term();
				std::cerr << "Please enter a number between 1 and " << mazes.size() << ".\n";
			}

		} while (std::cin.fail() || choice < 1 || choice > static_cast<int>(mazes.size()));
		
		active_index = choice - 1; // För att matcha med index i vektorn
		
		// Sätter generation till den aktiva labyrinten
		if (mazes[active_index].get_generation_metod() == GenerationMethod::DFS) {
			generation = "DFS";
		}
		else if (mazes[active_index].get_generation_metod() == GenerationMethod::PRIMS) {
			generation = "Prim's algorithm";
		}
		else {
			generation = "Unknown";
		}
	}
}

// Rensar terminalen, istället för system.clear() som är osäkert
void Menu::empty_term()
{
	for (int i = 0; i < 100; i++)
	{
		std::cout << "\n" << std::endl;
	}

}
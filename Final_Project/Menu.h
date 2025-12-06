//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#pragma once
#include "Maze.h"
#include <vector>


class Menu
{
private:
	std::vector<Maze> mazes;
	int active_index;
	std::string generation;
	std::string generation_in_use;

	// === Hjälpfunktioner ===
	bool creat_maze();
	void switch_maze();
	void empty_term();
public:
	Menu() : active_index(-1) {};
	void main_menu();
};


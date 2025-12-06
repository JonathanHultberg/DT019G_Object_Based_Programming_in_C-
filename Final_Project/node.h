//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#pragma once
#include "Enum.h"


struct node {
	int row;
	int col;
	bool visited;

	//Väggar - true = vägg, false = ingen vägg
	bool up;
	bool down;
	bool left;
	bool right;

	// För att hålla koll om de är S/E och vilken vägg som ska ersättas
	bool is_start;
	bool is_end;
	ExitWall wall_position;

	bool is_on_path; // För att hålla koll på rätt väg vid lösning

	bool is_in_frontier; // För Prim's algoritm, för att hålla koll på om noden redan finns i frontier

	
	node(int r, int c) : row(r), col(c), visited(false), up(true), down(true),
		left(true), right(true), is_start(false), is_end(false),
		wall_position(ExitWall::EXIT_NONE), is_on_path(false), is_in_frontier(false) {
	};

	//För att kunna skapa en tom node, för stdin
	node() : row(0), col(0), visited(false), up(true), down(true),
		left(true), right(true), is_start(false), is_end(false),
		wall_position(ExitWall::EXIT_NONE), is_on_path(false), is_in_frontier(false) {
	};
};

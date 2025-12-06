//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#pragma once
#include "Enum.h"

// För Prim's algoritm, för att hålla koll på vilken node grannarna hör till. För att öppna rätt vägg
struct frontier_entry {
	int r;
	int c;
	
	int from_r;
	int from_c;

	Direction from_dir;


	frontier_entry(int r, int c, int from_r, int from_c, Direction dir) : r(r), c(c), from_r(from_r), 
		from_c(from_c), from_dir(dir) {};
};;

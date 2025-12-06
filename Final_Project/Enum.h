//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#pragma once

//Direction: Andvänds till förlyttning mellan noder
enum class Direction { UP, DOWN, LEFT, RIGHT };

//Wall: Används för att välja vägg till S och E
enum class Wall { UP_WALL, DOWN_WALL, LEFT_WALL, RIGHT_WALL };

//ExitWall: Används för att markera vilken vägg som ska ersättas med S eller E
enum class ExitWall { EXIT_NONE, EXIT_UP, EXIT_DOWN, EXIT_LEFT, EXIT_RIGHT };

//GenerationMethod: Används för att berätta vilken metod som ska användas för att generera labyrinten
enum class GenerationMethod { DFS, PRIMS, NONE };
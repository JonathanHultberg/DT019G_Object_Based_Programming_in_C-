//Jonathan Hultberg (johu1701)
//2025-05-15
//DT019G Objektbaserad c++
//Projekt: Labyrint
//Betyg: A

#pragma once
#include "node.h"
#include "frontier_entry.h"
#include "Enum.h"
#include <vector>
#include <random>
#include <iostream>
#include <utility>
#include <string>
#include <cctype>
#include <algorithm>


class Maze {
private:
	// Maze-dimensioner och struktur
	int rows;
	int cols;
	std::mt19937 gen;
	std::vector<std::vector<node>> grid;
	GenerationMethod generation_method;

	// === Generering ===
	void dfs_generation(int row, int col);
	void prims_generation(int row, int col);
	void remove_wall(node& a, node& b, Direction dir);
	void move(int& r, int& c, Direction dir);
	bool is_valid_move(int r, int c) const;
	void add_neighbor_to_frontier(int r, int c, std::vector<frontier_entry>& frontier);

	// === Lösning ===
	bool dfs_solver(int r, int c);
	bool can_move(int r, int c, int next_r, int next_c, Direction dir) const;

	// === Start/slut-val ===
	void choose_start_end();
	std::pair<int, int> choose_position(Wall wall_dir);
	void mark_exit_wall(std::pair<int, int> pos, Wall dir);
	void set_exit_wall(int r, int c);

	// === Verktyg ===
	bool is_valid_input(const std::vector<std::string>& lines) const;
	void reset_maze();

public:
	// === Konstruktorer ===
	Maze();
	Maze(int r, int c);

	// === Offentliga gränssnitt ===
	void generate_maze_dfs();
	void generate_maze_prims();
	bool solve_maze_dfs();
	void print_maze();
	bool load_from_stdin();
	
	GenerationMethod get_generation_metod() { return generation_method;};
};

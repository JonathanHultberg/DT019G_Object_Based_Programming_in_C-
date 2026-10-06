# Maze Generator & Solver (C++)

A terminal application that **generates random mazes** and **finds a path through them**. It was built as the final project in *DT019G Object-Based Programming in C++* at Mid Sweden University and received grade **A**.

```
+---+ E +---+---+---+---+---+---+---+---+
| *   * |   |   |   |       |   |       |
+   +---+   +   +   +   +---+   +   +---+
| *     |           |   |   |           |
+   +---+   +---+---+   +   +   +---+---+
S * |                                   |
+   +   +---+---+---+---+---+---+---+---+
|                                       |
+   +---+---+---+---+---+---+   +---+---+
|       |   |   |   |       |           |
+   +---+   +   +   +   +---+---+---+   +
|                                   |   |
+---+---+---+---+---+---+---+---+---+---+
```
*A 6×10 maze generated with Prim's algorithm and solved with DFS. `S` is the start, `E` is the exit and `*` marks the path.*

## Features

- **Two generation algorithms**
  - **Recursive DFS (recursive backtracker):** produces long, winding corridors.
  - **Randomized Prim's algorithm:** grows the maze from a frontier and produces many short branches.
- **Solving with depth-first search.** The solver marks the path from `S` to `E` with `*`.
- **Random start and exit**, always placed on two different outer walls.
- **Several mazes at once.** You can create, switch between, overwrite and delete mazes from the menu.
- **Solve mode from stdin.** Pipe a maze in text format to the program and it prints the solution.
- **Input validation** for menu choices, maze size (max 40×40) and maze files.

## Technologies

| | |
|---|---|
| **Language** | C++17 |
| **Standard library** | `<vector>`, `<random>` (`std::mt19937`), `<algorithm>` (`std::shuffle`), `<utility>`, `enum class` |
| **Concepts** | Object-based design, encapsulation, recursion, graph traversal (DFS), randomized spanning trees (Prim) |
| **External libraries** | None |

## Project structure

| File | Responsibility |
|---|---|
| `Main.cpp` | Entry point. Starts the menu or `--solve` mode |
| `Menu.h / .cpp` | Text menu that manages several mazes |
| `Maze.h / Maze.cpp` | The `Maze` class: constructors, reading from stdin, validation |
| `MazeGeneration.cpp` | DFS and Prim's generation |
| `MazeSolving.cpp` | DFS solver and wall checks |
| `MazeStartEnd.cpp` | Random placement of start and exit |
| `MazePrint.cpp` | ASCII rendering of the maze |
| `node.h` | A cell in the grid, with its walls and state |
| `frontier_entry.h` | Helper struct for Prim's frontier |
| `Enum.h` | `Direction`, `Wall`, `ExitWall`, `GenerationMethod` |

## Build and run

```bash
g++ -std=c++17 -O2 *.cpp -o maze
./maze
```

### Interactive menu

```
1. Generate maze with DFS
2. Generate maze with Prim's algorithm
3. Solve maze with DFS
4. Switch maze
5. Generate new maze with DFS (overwrite current)
6. Generate new maze with Prim's algorithm (overwrite current)
7. Delete the currently active maze
8. Exit
```

### Solve a maze from a file (`--solve`)

The input format uses one character per cell and wall. Any non-space character is a wall. `S` marks the start and `E` marks the exit.

```bash
printf '#########\n#S  #   #\n### # # #\n#     #E#\n#########\n' | ./maze --solve
```

Output:

```
+---+---+---+---+
S *   * | *   * |
+---+   +   +   +
|     *   * | * E
+---+---+---+---+
```

## Author

**Jonathan Hultberg**, Computer Engineering student at Mid Sweden University

# 8-Puzzle Solver — Best First Search (Misplaced Tiles Heuristic)

## Overview
This C++ program solves the **8-puzzle problem** using the **Best First Search** algorithm with the **Misplaced Tiles heuristic**.  
The program explores puzzle states by always expanding the one with the **fewest misplaced tiles** compared to the goal configuration.

The goal configuration is:

1 2 3
4 5 6
7 8 0

Here, `0` represents the blank tile.

---

## Features
- Accepts user-defined starting puzzle configuration.
- Uses **Misplaced Tiles heuristic** `h(n)` to guide search.
- Expands states in order of increasing heuristic value.
- Displays the **step-by-step transformation** from start state to goal state.
- Detects and stops if no solution is possible.

---

## How the Algorithm Works
1. **Heuristic Function**: Counts the number of tiles not in their correct position (excluding the blank).
2. **Priority Queue (Min-Heap)**: Stores puzzle states, ordered by `h(n)`.
3. **Move Generation**: Produces all possible next states by sliding the blank tile **up**, **down**, **left**, or **right**.
4. **Visited Set**: Prevents revisiting the same state.
5. **Termination**:
   - Success: Goal configuration reached.
   - Failure: All possible states explored without reaching the goal.

---

## Example Run

**Input**
Enter puzzle (0 for blank):
1 2 3
4 0 6
7 5 8


**Output**
--- Solution Found (Best First Search - Misplaced Tiles) ---
1 2 3
4 0 6
7 5 8
1 2 3
4 5 6
7 0 8
1 2 3
4 5 6
7 8 0


---

## Usage
1. Compile the program:
   ```bash
   g++ puzzle_bfs.cpp -o puzzle_bfs
Run the program:
./puzzle_bfs
Enter the puzzle configuration row by row, using 0 for the blank space.

# Use Case
This program is useful for:

Demonstrating Best First Search in action.

Comparing heuristic search performance with other strategies like A* or Uniform Cost Search.

Teaching and learning AI search algorithms.

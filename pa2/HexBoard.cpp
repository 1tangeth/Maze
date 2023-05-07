#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

/**
 * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard()
 * and setting cells to have the appropriate neighbours by calling configure_cells(). The default start_coord is (0, 0).
 * @note There is no maze yet! The board is just a beehive for now.
 * @param radius The radius of the board
 */

HexBoard::HexBoard(int radius)
{
    this->longest_path_dist = 0;
    this->start_coord = {0, 0};
    this->radius = radius;
    create_board();
    configure_cells();
}

/**
 * Creates all neccessary HexCells up to the (but not including) given radius and insert them into this->cells.
 */
void HexBoard::create_board()
{
    HexCell *start = new HexCell(0, 0);
    for (int q = -radius; q <= radius; q++)
    {
        for (int r = -radius; r <= radius; r++)
        {
            HexCell *cell = new HexCell(q, r);
            if (start->distance(cell) < radius)
            {
                this->cells[{q, r}] = cell;
            }
        }
    }
}

/**
 * Set all cells in this->cells to have the appropriate neighbours.
 */
void HexBoard::configure_cells()
{
    for (auto kv : cells)
    {
        pair<int, int> coord = kv.first;
        HexCell *cell = kv.second;
        vector<pair<int, int>> neighbour = get_neigh_coords(coord);
        for (unsigned i = 0; i < neighbour.size(); i++)
        {

            if (cells.find(neighbour[i]) != cells.end())
                cell->neighbours[cell->get_neighbour_side(cells[neighbour[i]])] = cells[neighbour[i]];
        }
    }
}

/**
  * Traverses the board via dfs to generate the maze, updating and keeping track of:
  * A. The length of the longest path to an edge in the maze

  * The algorithm goes as follows:
  * 1. Add the start_coord to the stack, and mark as visited
  * 2. While the stack is not empty do:

  *   a. Peek the top of the stack (call it curr_cell)
  *   c. Use chooseNeighbour to choose the neighbour to visit
  *   d. If the neighbour exists, for that neighbour (call it neigh_cell) do:

  *     i. Link curr_cell with neigh_cell
  *     ii. Set neigh_coord to be visited
  *     iii. Update the neigh_cell's path distance
  *     iv. If necessary, update length of longest path so far (longest_path_dist)
  *     v. Update the end coordinate only if its path distance to start is strictly greater
  *     vi. Push neigh_cell into the stack

  *   e. Otherwise (if chooseNeighbour returns nullptr), pop the stack.

  * @param start_coord The {q, r} coordinate of the start of the maze.
  * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
  *                    A small branch_prob means neighbours of the same radius (same dist from the centre) are preferred
  *                    A large branch_prob means neighbours of a different radius (diff dist from the centre) are preferred
  * REQUIRE: create_board() is already called
  */
void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob)
{
    map<pair<int, int>, bool> visited;
    Stack<pair<int, int>> stack;
    this->start_coord = start_coord;
    stack.push(start_coord);
    visited[{start_coord}] = true;
    int maximum = -1;

    while (!stack.isEmpty())
    {
        HexCell *curr_cell = cells[stack.peek()];
        HexCell *neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);

        if (neigh_cell != nullptr)
        {
            curr_cell->link(neigh_cell);
            visited[{neigh_cell->q, neigh_cell->r}] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;

            if (neigh_cell->path_dist_from_start > longest_path_dist)
            {
                longest_path_dist = neigh_cell->path_dist_from_start;
            }
            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > maximum)
            {
                maximum = neigh_cell->path_dist_from_start;
                this->end_coord = {neigh_cell->q, neigh_cell->r};
            }

            stack.push({neigh_cell->q, neigh_cell->r});
        }
        else
        {
            stack.pop();
        }
    }
}

/**
  * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

  * REQUIRE: generate_maze must be called already
  */
void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */

    Stack<pair<int, int>> stack;
    vector<pair<int, int>> visited;
    
    if (start_coord == end_coord) {
        solution.push_back(start_coord);
        return;
    }

    stack.push(start_coord);

    while(!stack.isEmpty()) {
        pair<int, int> currPair = stack.pop();
        solution.push_back(currPair);
        visited.push_back(currPair);

        auto lookup = cells.find(currPair);
        HexCell* currentCell = lookup->second;

        vector<pair<int, int>> neighbours = get_neigh_coords(currPair);
        int numberOfUnvisitedLink = 0;
        for (auto neighbour:neighbours) {
            auto lookup = cells.find(neighbour);
            HexCell* neigh_cell = lookup->second;
            if (neigh_cell != nullptr && currentCell->is_linked(neigh_cell) && neighbour==end_coord) {
                solution.push_back(neighbour);
                return;
            } else if (neigh_cell != nullptr && currentCell->is_linked(neigh_cell) && find(solution.begin(), solution.end(), neighbour) == solution.end()) {
                stack.push(neighbour);
                numberOfUnvisitedLink ++;
            }
        }

        if (numberOfUnvisitedLink == 0) {
            pair<int, int> stackTop = stack.peek();
            auto lookup = cells.find(stackTop);
            HexCell* stackTopCell = lookup->second;
            pair<int, int> curr = solution.back();
            auto lookup2 = cells.find(curr);
            HexCell* currCell = lookup2->second;
            while(currCell->get_neighbour_side(stackTopCell) == -1) {
                solution.pop_back();
                pair<int, int> curr = solution.back();
                auto lookup = cells.find(curr);
                currCell = lookup->second;
            }
        }
}
}

                    // cout << "(";
                    // cout << neigh_cell->q;
                    // cout << " , ";
                    // cout << neigh_cell->r;
                    // cout << ")" << endl;

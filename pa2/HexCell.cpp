#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    /**
     * @todo Your code here!
     */
    for (auto & neighbour:neighbours) {
        neighbour = nullptr;
    }
    for (auto & link:links) {
        link = nullptr;
    }
    path_dist_from_start = 0;
    q=Q;
    r=R;
}

void HexCell::link(HexCell* cell) {

    if (cell != nullptr) {
        if (q == cell->q) {
            if (r-1 == cell->r) {
                links[0] = cell;
                cell->links[3] = this;
            } else if (r+1 == cell->r) {
                links[3] = cell;
                cell->links[0] = this;
            }
        } if (q+1 == cell->q) {
            if (r == cell->r) {
                links[2] = cell;
                cell->links[5] = this;
            } else if (r-1 == cell->r){
                links[1] = cell;
                cell->links[4] = this;
            }
        } else if (q-1 == cell->q){
            if (r == cell->r) {
                links[5] = cell;
                cell->links[2] = this;
            } else if (r+1 == cell->r){
                links[4] = cell;
                cell->links[1] = this;
            }
        }
    }
}

int HexCell::get_neighbour_side(const HexCell* cell) const {

    int returnVal = -1;

    int cellR = cell->r;
    int cellQ = cell->q;
    if (q == cellQ) {
        if (r-1 == cellR) {
            returnVal = 0;
        } else if (r+1 == cellR) {
            returnVal = 3;
        }
    } else if (r == cellR) {
        if (q-1 == cellQ) {
            returnVal = 5;
        } else if (q+1 == cellQ) {
            returnVal = 2;
        }
    } else if (r+1 == cellR && q-1 == cellQ) {
        returnVal = 4;
    } else if (r-1 == cellR && q+1 == cellQ) {
        returnVal = 1;
    }
    return returnVal;
}

bool HexCell::is_linked(const HexCell* cell) const {


    for (auto const& link:links) {
        if (link == cell && cell != nullptr) {
            return true;
        }
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    int distance = -1;
    if (cell == nullptr) {
        return distance;
    } else {
        return (abs(q - cell->q) + abs(q + r - cell->q - cell->r)+ abs(r - cell->r)) / 2;
    }
}

bool HexCell::is_edge() const {

    for (auto const& neighbour:neighbours) {
        if (neighbour == nullptr) {
            return true;
        }
    }
    return false;
}
#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include <algorithm>

#include "move.hpp"

point decide( area_map input_map, int org_num, map< int, organism*> orgs, pair<vector<char>, vector<char>> ids );

#endif
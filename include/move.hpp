#ifndef MOVE_HPP
#define MOVE_HPP

#include <map>

#include "reproduce.hpp"

using namespace std;

void move_by( point pt, area_map& input_map, pair<vector<char>, vector<char>> ids, int org_num, map< int, organism*>& orgs );

#endif
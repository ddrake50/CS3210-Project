#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <fstream>

#include "pathfinding.hpp"

using namespace std;

int start( string map_file, string species_file );

map< int, organism*> load_positions( area_map input_map , map<char, shared_ptr<organism> > orgs );

pair<vector<char>, vector<char>> extract_ids(map<char, shared_ptr<organism> > const& orgs);

void start_simulation( area_map input_map, map< int, organism*>& locations, pair<vector<char>, vector<char>> ids, map<char, shared_ptr<organism> > orgs );

void run_simulation( area_map& input_map, map< int, organism*>& locations, pair<vector<char>, vector<char>> ids, map<char, shared_ptr<organism> > orgs );

#endif
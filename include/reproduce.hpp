#ifndef REPRODUCE_HPP
#define REPRODUCE_HPP

#include <set>
#include <map>

#include "species_registry.hpp"

using namespace std;

class area_map;

void reproduce( area_map& input_map, int org_num, map< int, organism*>& orgs, map<char, shared_ptr<organism> > species );

void make_offspring( char id, map< int, organism*>& orgs, point pt, map<char, shared_ptr<organism> > species );

#endif
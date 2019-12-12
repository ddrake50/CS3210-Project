#include "move.hpp"

using namespace std;

extern map<point,int> plant_regen;

void move_by( point pt, area_map& input_map, pair<vector<char>, vector<char>> ids, int org_num, map< int, organism*>& orgs ) 
{
  int energy = orgs[org_num]->energy_points();
  int max_energy = orgs[org_num]->max_energy();
  char id = orgs[org_num]->id();
  point pos = orgs[org_num]->position();
  vector<char> food = orgs[org_num]->food_chain();

  set<point> surrounding_pts = {point(-1,-1), point(-1,0), point(-1,1), point(0,-1),point(0,1), point(1,-1), point(1,0), point(1,1)};

  if ( orgs[org_num]->can_move() == true ) {
    if ( input_map.at( pt.y, pt.x ) != '#' && input_map.at( pt.y, pt.x ) != '~' ) {
      int switch_case;
      char comp_org;
      if ( input_map.at( pt.y, pt.x ) == ' ' ) { switch_case = 0; }
      for(auto it = ids.first.begin(); it != ids.first.end(); ++it) {
        if ( input_map.at( pt.y, pt.x ) == *it ) {
          switch_case = 1;
          comp_org = *it;
          break;
        }
      }
      for(auto it = ids.second.begin(); it != ids.second.end(); ++it) {
        if ( input_map.at( pt.y, pt.x ) == *it ) {
          switch_case = 2;
          comp_org = *it;
          break;
        }
      }
      switch(switch_case)
{
    case 0:
        if ( energy > 0 ) {
            orgs[org_num]->update_energy(-1);
            input_map.at(pos.y,pos.x) = ' ';
            orgs[org_num]->position() = pt;
            input_map.at(pt.y,pt.x) = id;
        } else { 
          input_map.at( pos.y, pos.x ) = ' ';
          orgs.erase(org_num);
        }
        break;
    case 1: 
        for( char ch : food ) {
          if ( ch == comp_org ) {
            for(auto it2 = orgs.begin(); it2 != orgs.end(); ++it2) {
              if ( it2->second->position() == pt ) {
                if ( max_energy - energy >= ( it2->second->energy_points() + 1 ) ) {
                  orgs[org_num]->update_energy(it2->second->energy_points()-1);
                  input_map.at(pos.y,pos.x) = ' ';
                  orgs[org_num]->position() = pt;
                  plant_regen[pos] = 1;
                  input_map.at(pt.y,pt.x) = id;
                  break;
                } else if ( energy < max_energy ) {
                    orgs[org_num]->update_energy(max_energy - energy);
                    input_map.at(pos.y,pos.x) = ' ';
                    orgs[org_num]->position() = pt;
                    plant_regen[pos] = 1;
                    input_map.at(pt.y,pt.x) = id;
                    break;
                } else {
                    auto not_open = 0;

                    for ( auto pt : surrounding_pts ) {
                      auto check_pt = pos+pt;
                      if ( check_pt.x < input_map.extent().y && check_pt.x >= 0 && check_pt.y < input_map.extent().x && check_pt.y > 0 ) {
                        if ( input_map.at( check_pt.y, check_pt.x ) != ' ' ) {
                          not_open++;
                        }
                      } else { not_open++; }
                    }
                    if ( not_open < 8 ) {
                      orgs[org_num]->update_energy(-1);

                      auto rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));

                      while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                        rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                      }
                      while ( input_map.at( rand_pt.y, rand_pt.x ) != ' ' ) {
                        rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                        if ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                          while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                            rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                          }
                        }
                      }
                      input_map.at(pos.y,pos.x) = ' ';
                      orgs[org_num]->position() = rand_pt;
                      input_map.at(rand_pt.y, rand_pt.x) = id;
                      break;
                    } else { break; }
                 }
              } 
            } break; 
          }
        }
        break;
    case 2:
        for( char ch : food ) {
          if ( ch == comp_org ) {
            if ( orgs[org_num]->kind() != "herbivore" ) {
              for(auto it2 = orgs.begin(); it2 != orgs.end(); ++it2) {
                if ( it2->second->position() == pt ) {
                  if ( max_energy - energy >= ( it2->second->energy_points() + 1 ) ) {
                    orgs[org_num]->update_energy(it2->second->energy_points()-1);
                    input_map.at(pos.y,pos.x) = ' ';
                    orgs[org_num]->position() = pt;
                    orgs.erase(it2->first);
                    input_map.at(pt.y,pt.x) = id;
                    break;
                  } else if ( energy < max_energy ) {
                      orgs[org_num]->update_energy(max_energy - energy);
                      input_map.at(pos.y,pos.x) = ' ';
                      orgs[org_num]->position() = pt;
                      orgs.erase(it2->first);
                      input_map.at(pt.y,pt.x) = id;
                      break;
                  } else {
                      auto not_open = 0;

                      for ( auto pt : surrounding_pts ) {
                        auto check_pt = pos+pt;
                        if ( check_pt.x < input_map.extent().y && check_pt.x >= 0 && check_pt.y < input_map.extent().x && check_pt.y > 0 ) {
                          if ( input_map.at( check_pt.y, check_pt.x ) != ' ' ) {
                            not_open++;
                          }
                        } else { not_open++; }
                      }
                      if ( not_open < 8 ) {
                        orgs[org_num]->update_energy(-1);

                        auto rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));

                        while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                          rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                        }
                        while ( input_map.at( rand_pt.y, rand_pt.x ) != ' ' ) {
                          rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                          if ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                            while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                              rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
                            }
                          }
                        }
                        input_map.at(pos.y,pos.x) = ' ';
                        orgs[org_num]->position() = rand_pt;
                        input_map.at(rand_pt.y, rand_pt.x) = id;
                        break;
                      } else { break; }
                  }
                }
              } break;
            } else { cout << "Herbivores can not eat meat. They are vegetarian." << endl; }
          }
        } 
        break;
    default:
        { cout << "ERROR" << endl; }
}
    } if ( orgs.find(org_num) != orgs.end() ) { 
        if ( orgs[org_num]->position() == pos ) {
          auto surr_animals = 0;

          auto rand_pt = (pos+point((rand()%3-1),(rand()%3-1)));

          while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
            rand_pt = (pos+point((rand()%3-1),(rand()%3-1)));
          }
          while ( input_map.at( rand_pt.y, rand_pt.x ) != ' ' && surr_animals < 8 ) {
            rand_pt = (pos+point((rand()%3-1),(rand()%3-1)));
            if ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
              while ( rand_pt.x >= input_map.extent().y || rand_pt.x < 0 || rand_pt.y >= input_map.extent().x || rand_pt.y < 0 ) {
                rand_pt = (pos+point((rand()%3)-1,(rand()%3)-1));
              }
            } if ( input_map.at( rand_pt.y, rand_pt.x ) == orgs[org_num]->id() ) {
              surr_animals++;
            }
          }
          if ( surr_animals != 8 ) {
            orgs[org_num]->update_energy(-1);

            input_map.at(pos.y,pos.x) = ' ';
            orgs[org_num]->position() = rand_pt;
            input_map.at(rand_pt.y, rand_pt.x) = id;
          } else {}
        }
      }
  }
}
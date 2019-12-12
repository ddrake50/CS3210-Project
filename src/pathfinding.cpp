#include "pathfinding.hpp"

using namespace std;

point decide( area_map input_map, int org_num, map< int, organism*> orgs, pair<vector<char>, vector<char>> ids ) 
{
    point org_loc = orgs[org_num]->position();
    vector<char> food = orgs[org_num]->food_chain();
    char id = orgs[org_num]->id();

    set<point> surrounding_pts = {point(-1,-1), point(-1,0), point(-1,1), point(0,-1),point(0,1), point(1,-1), point(1,0), point(1,1)};
    vector<pair<int,point>> heat_map;
    point move_pos;

    for ( auto pts : surrounding_pts ) {
        auto heat_num = 0;
        auto pt = org_loc+pts;
        if ( pt.x < input_map.extent().y && pt.x >= 0 && pt.y < input_map.extent().x && pt.y >= 0 ) {
            if ( input_map.at( pt.y, pt.x ) == '#' && input_map.at( pt.y, pt.x ) == '~' ) {
                heat_num -= 10;
            }
            for ( auto ch : food ) {
                if ( input_map.at( pt.y, pt.x ) == ch ) {
                    for ( auto plant_id : ids.first ) {
                        if ( ch == plant_id ) {
                            heat_num += 5;
                            break; 
                        }
                    }
                    for ( auto animal_id : ids.second ) {
                        if ( ch == animal_id ) {
                            heat_num += 12;
                            break;
                        }
                    }        
                }
            } 
            for ( auto o : orgs ) {
                if ( pt == o.second->position() ) {
                    if ( o.second->kind() != "plant" ) {
                        auto other_food = o.second->food_chain();
                        for ( auto other_ch : other_food ) {
                            if ( other_ch == id ) {
                                heat_num -= 10;
                                break;
                            } else { 
                                heat_num += 1;
                                break;
                            }
                        }
                    } break;
                }
            }
        for ( auto nxt_pts : surrounding_pts ) {
            auto nxt_pt = pt+nxt_pts;
            if ( nxt_pt.x < input_map.extent().y && nxt_pt.x >= 0 && nxt_pt.y < input_map.extent().x && nxt_pt.y >= 0 ) {
                if ( input_map.at( nxt_pt.y, nxt_pt.x ) == '#' && input_map.at( nxt_pt.y, nxt_pt.x ) == '~' ) {
                    heat_num -= 5;
                }
                for ( auto ch : food ) {
                    if ( input_map.at( nxt_pt.y, nxt_pt.x ) == ch ) {
                        for ( auto plant_id : ids.first ) {
                            if ( ch == plant_id) {
                                heat_num += 3;
                                break; 
                            }
                        }
                        for ( auto animal_id : ids.second ) {
                            if ( ch == animal_id ) {
                                heat_num += 10;
                                break;
                            }
                        } 
                    }
                } 
                for ( auto o : orgs ) {
                    if ( nxt_pt == o.second->position() ) {
                        if ( o.second->kind() != "plant" ) {
                            auto other_food = o.second->food_chain();
                            for ( auto other_ch : other_food ) {
                                if ( other_ch == id ) {
                                    heat_num -= 8;
                                    break;
                                } else { 
                                    heat_num += 1;
                                    break;
                                }
                            }
                        } break;
                    }
                }
            }
        }
        heat_map.push_back( make_pair( heat_num, pt ) );
        }
    }
    sort( heat_map.begin(), heat_map.end() );
    if ( heat_map[heat_map.size()-1].first == 1 ) {
        while ( move_pos.x >= input_map.extent().y || move_pos.x < 0 || move_pos.y >= input_map.extent().x || move_pos.y < 0 ) {
            move_pos = org_loc + point((rand()%3)-1,(rand()%3)-1);
        }
    } else { move_pos = heat_map[heat_map.size()-1].second; }

    return move_pos;
}
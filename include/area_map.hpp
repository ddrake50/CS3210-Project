#ifndef AREA_MAP_HPP
#define AREA_MAP_HPP

#include <vector>
#include <sstream>

#include "point.hpp"

using namespace std;

class area_map : vector<vector<unsigned char>>
{
    using base = vector;
    using self = area_map;
public:
    using value_type = unsigned char;

    area_map() {}
    area_map( point const& extent );

    point extent() const;

    value_type& at( int col, int row );
    value_type at( int col, int row ) const;

    value_type& at( point const& pos ) { return at( pos.x, pos.y ); }
    auto at( point const& pos ) const { return at( pos.x, pos.y ); }

    value_type& operator[]( point const& pos ) { return at( pos ); }
    auto operator[]( point const& pos ) const { return at( pos ); }

    friend area_map load_map( istream& );
    friend void save_map( ostream&, area_map const& );
    friend void save_map_to_file( string, area_map const& );
};

area_map load_map( istream& in );
void save_map( ostream& out, area_map const& map );
void save_map_to_file( string out, area_map const& map);

#endif

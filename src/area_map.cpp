#include <fstream>

#include "area_map.hpp"

using namespace std;

area_map::area_map( point const& extent )
    : base( extent.y, vector<value_type>( extent.x ) )
{}

point area_map::extent() const
{
    auto nrows = size();
    return nrows > 0
        ? point( front().size(), nrows )
        : point();
}

auto area_map::at( int col, int row ) -> value_type&
{
    return base::operator[]( row )[ col ];
}

auto area_map::at( int col, int row ) const -> value_type
{
    return const_cast<self&>( *this ).at( col, row );
}

area_map load_map( istream& in )
{
    area_map result;
    string buffer;
    while ( getline( in, buffer ) )
    {
        if ( result.size() && buffer.size() != result.front().size() )
            return area_map();

        vector<area_map::value_type> row;
        for ( auto c : buffer )
            row.push_back( c );
        result.push_back( move( row ) );
    }

    return result;
}

void save_map( ostream& out, area_map const& map )
{
    for ( auto const& row : map ) 
    {
        for ( auto c : row ) 
            out << c;
        out << "\n";
    }
}

void save_map_to_file( string out, area_map const& map)
{
  fstream newfile;
  string buffer;
  string saved_map;
  newfile.open( out, ios::out );
  if (newfile.is_open()){
    for ( auto const& row : map ) {
      for ( auto c : row )
        newfile << c;
      newfile << "\n";
    }
    newfile.close();
  }
}
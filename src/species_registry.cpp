#include "species_registry.hpp"

species_registry const species;

unique_ptr<organism> read( istream& in )
{
    string kind;
    if ( in >> kind )
    {
        if ( auto org = species.find( kind ) )
            return org->new_from_stream( in );
    }

    return nullptr;
}

unique_ptr<organism> read_from_string( string const& str )
{
    istringstream in( str );
    return read( in );
}

string write_to_string( organism const& org )
{
    ostringstream out;
    org.write( out );
    return out.str();
}
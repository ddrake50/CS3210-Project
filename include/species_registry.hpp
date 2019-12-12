#ifndef SPECIES_REGISTRY_HPP
#define SPECIES_REGISTRY_HPP

#include <vector>

#include "organism.hpp"
#include "plant.hpp"
#include "herbivore.hpp"
#include "carnivore.hpp"
#include "omnivore.hpp"

using namespace std;

struct species_registry
{
    species_registry()
    {
        this->species.push_back( make_unique<plant>( '\0', '\0', '\0' ) );
        this->species.push_back( make_unique<herbivore>( '\0', vector<char>('\0'), '\0' ) );
        this->species.push_back( make_unique<omnivore>( '\0', vector<char>('\0'), '\0' ) );
        this->species.push_back( make_unique<carnivore>( '\0', vector<char>('\0'), '\0' ) );
    }

    organism* find( string const& kind ) const
    {
        for ( auto& org : this->species )
            if ( org->kind() == kind )
                return org.get();

        return nullptr;
    }

private:
    vector<unique_ptr<organism>> species;
};

unique_ptr<organism> read( istream& in );
unique_ptr<organism> read_from_string( string const& str );
string write_to_string( organism const& org );

#endif
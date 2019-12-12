#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include <iostream>
#include <sstream>
#include <memory>
#include <cassert>
#include <fstream>
#include <map>

#include "area_map.hpp"

using namespace std;

struct organism {
    using org_id = char;

    organism( org_id id, int max_energy ) : 
    id_( id ), max_energy_( max_energy ), energy_( max_energy ) {}

    virtual ~organism() {} 

    virtual string kind() const = 0;
    virtual int growth_coefficient() const = 0;
    virtual bool can_move() const = 0;
    virtual vector<char> food_chain() const = 0;
    virtual int max_energy() const = 0;
    virtual int energy_points() = 0;
    virtual void update_energy(int i) {};

    org_id id() const { return id_; }
    virtual point& position() { return pos_; }

    virtual organism* clone() const = 0;

    virtual void write( ostream& out ) const;
    
    virtual unique_ptr<organism> new_from_stream( istream& in ) const
    {
        org_id id;
        if ( in >> id  )
            return this->create( id );

        return nullptr;
    }

    unique_ptr<organism> create( org_id id ) const
    {
        assert( false );
        return nullptr;
    }

    private:
      org_id id_;
      int max_energy_;
      int energy_;
      point pos_;
      
};

void save_species_list( string out , map< int, organism*> locations);

#endif

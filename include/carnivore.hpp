#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP

#include "animal.hpp"

using namespace std;

struct carnivore : animal {
    carnivore( org_id id, vector<char> food_chain, int max_energy ) : 
    animal( id, food_chain, max_energy ) {}

    string kind() const override { return "carnivore"; }
    virtual carnivore* clone() const override{ return new carnivore(*this); }

    unique_ptr<organism> create( org_id id, vector<char> food_chain, int max_energy ) const override
    {
        return make_unique<carnivore>( id, food_chain, max_energy );
    }

};

#endif

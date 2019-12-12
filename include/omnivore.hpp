#ifndef OMNIVORE_HPP
#define OMNIVORE_HPP

#include "animal.hpp"

using namespace std;

struct omnivore : animal {
    omnivore( org_id id, vector<char> food_chain, int max_energy ) : 
    animal( id, food_chain, max_energy ) {}

    string kind() const override { return "omnivore"; }
    virtual omnivore* clone() const override { return new omnivore(*this); }

    unique_ptr<organism> create( org_id id, vector<char> food_chain, int max_energy ) const override
    {
        return make_unique<omnivore>( id, food_chain, max_energy );
    }

};

#endif

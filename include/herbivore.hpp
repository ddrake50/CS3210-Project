#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP

#include "animal.hpp"

using namespace std;

struct herbivore : animal {
    herbivore( org_id id, vector<char> food_chain, int max_energy ) : 
    animal( id, food_chain, max_energy ) {}

    string kind() const override { return "herbivore"; }
    virtual herbivore* clone() const override { return new herbivore(*this); }

    unique_ptr<organism> create( org_id id, vector<char> food_chain, int max_energy ) const override
    {
        return make_unique<herbivore>( id, food_chain, max_energy );
    }
    
};

#endif

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "organism.hpp"

using namespace std;

struct animal : organism {
    animal( org_id id, vector<char> food_chain, int max_energy ) : 
    organism( id, max_energy ), food_chain_( food_chain ), max_energy_( max_energy ), energy_( max_energy ) {}

    string kind() const override { return "animal"; }
    bool can_move() const override { return true; }
    int max_energy() const override { return max_energy_; }
    int energy_points() override { return energy_; }
    vector<char> food_chain() const override { return food_chain_; }
    void update_energy(int i) override;
    point& position() override { return pos_; }
    int growth_coefficient() const { return 0; }

    virtual animal* clone() const override { return new animal(*this); }

    string food_chain_str() const;
    void write( ostream& out ) const override;

    unique_ptr<organism> new_from_stream( istream& in ) const override
    {
        org_id id;
        int max_energy;
        char ch;
        vector<char> food_chain;
        if ( in >> id ) { in >> ch; }
        if ( ch == '[' ) {
          in >> ch;
          while ( ch != ']' ) {
            if ( ch != ',' ) {
              food_chain.push_back(ch);
            }
            in >> ch;
          }
        }
        if ( in >> max_energy ) {
          return this->create( id, food_chain, max_energy );
        } else { return nullptr; }
    }

    virtual unique_ptr<organism> create( org_id id, vector<char> food_chain, int max_energy ) const
    {
        return make_unique<animal>( id, food_chain, max_energy );
    }

    private:
      int max_energy_;
      vector<char> food_chain_;
      int energy_;
      point pos_;
};

#endif
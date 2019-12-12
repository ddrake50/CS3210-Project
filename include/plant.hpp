#ifndef PLANT_HPP
#define PLANT_HPP

#include "organism.hpp"

using namespace std;

struct plant : organism {
    plant( org_id id, int growth_coefficient, int energy_points ) : 
    organism( id, energy_points ), growth_coefficient_( growth_coefficient ), energy_points_( energy_points ) {}

    string kind() const override { return "plant"; }
    bool can_move() const override { return false; }
    int max_energy() const override { return energy_points_; }
    int energy_points() override { return energy_points_; }
    point& position() override { return pos_; }
    int growth_coefficient() const override { return growth_coefficient_; }
    vector<char> food_chain() const { return vector<char>('\n'); }

    virtual plant* clone() const override { return new plant(*this); }

    void write( ostream& out ) const override;

    unique_ptr<organism> new_from_stream( istream& in ) const override
    {
        org_id id;
        int growth_coefficient;
        int energy_points;
        if ( in >> id >> growth_coefficient >> energy_points )
            return this->create( id, growth_coefficient, energy_points );

        return nullptr;
    }
    
    unique_ptr<organism> create( org_id id, int growth_coefficient, int energy_points ) const
    {
        return make_unique<plant>( id, growth_coefficient, energy_points );
    }

    private:
      int growth_coefficient_;
      int energy_points_;
      point pos_;
};

#endif

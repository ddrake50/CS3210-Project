#include "organism.hpp"
#include "animal.hpp"
#include "plant.hpp"

void organism::write( ostream& out ) const
{
  out << this->kind() << " " << this->id();
}

void animal::update_energy(int i)
{
    this->energy_ += i;
}

void animal::write( std::ostream& out ) const
{
  out << this->kind() << " " << this->id() << " " << this->food_chain_str() << " " << this->max_energy();
} 

string animal::food_chain_str() const { 
  string food_chain_str = "[";
  for(auto& ch: food_chain()) {
    if ( ch != *(food_chain().end()-1) ) {
      food_chain_str += ch;
      food_chain_str += ", ";
    } else { food_chain_str += ch; }
    }
  food_chain_str += "]";
  return food_chain_str;
}

    
void plant::write( std::ostream& out ) const
{
  out << this->kind() << " " << this->id() << " " << this->growth_coefficient() << " " << this->max_energy();
} 

void save_species_list( string out , map< int, organism*> locations) {
    fstream newfile;
    newfile.open( out, ios::out );
    if (newfile.is_open()) {
        for ( auto const& org : locations ) {
            newfile << org.first << ", " << org.second->id() << ", " << org.second->kind() << ", \n";
        }
    }
}
#include "simulation.hpp"

//testmap1.txt & testspecies1.txt tests larger map with various species
//testmap2.txt & testspecies2.txt tests invalid species lists and invalid map boundaries
//testmap3.txt & testspecies3.txt tests missing species w/in the list
//testmap4.txt & testspecies4.txt tests invalid map obstacles
//map.txt & testspecies5.txt tests if herbivores can eat omnivores
//simpletest_map/simpletest_species creates simple environement to test move mechanics

int main() {
  start( "testmap1.txt", "testspecies1.txt" );
  return 0;
}
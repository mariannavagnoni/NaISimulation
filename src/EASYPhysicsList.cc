#include "EASYPhysicsList.hh"

EASYPhysicsList::EASYPhysicsList() : G4VModularPhysicsList(){

	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4RadioactiveDecayPhysics());
	RegisterPhysics(new G4DecayPhysics());
}

EASYPhysicsList::~EASYPhysicsList(){}
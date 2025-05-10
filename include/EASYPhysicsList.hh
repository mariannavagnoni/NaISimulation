#ifndef EASYPHYSICSLIST_HH
#define EASYPHYSICSLIST_HH 

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class EASYPhysicsList : public G4VModularPhysicsList{
	public:
		EASYPhysicsList();
		~EASYPhysicsList();
};

#endif
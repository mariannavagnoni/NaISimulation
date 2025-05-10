#ifndef EASYPRIMARYGENERATOR_HH
#define EASYPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"

class EASYPrimaryGenerator : public G4VUserPrimaryGeneratorAction{
	public:
		EASYPrimaryGenerator();
		~EASYPrimaryGenerator();

		virtual void GeneratePrimaries(G4Event *);
	
	private:
		G4ParticleGun *fParticleGun; 
};

#endif
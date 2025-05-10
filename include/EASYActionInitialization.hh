#ifndef EASYACTIONINITIALIZATION_HH
#define EASYACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "EASYRunAction.hh"

#include "EASYPrimaryGenerator.hh"

class EASYActionInitialization : public G4VUserActionInitialization{
	public:
		EASYActionInitialization();
		~EASYActionInitialization();

		virtual void BuildForMaster() const;
		virtual void Build() const;
};

#endif
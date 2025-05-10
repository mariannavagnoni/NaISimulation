#include "EASYActionInitialization.hh"

EASYActionInitialization::EASYActionInitialization(){}

EASYActionInitialization::~EASYActionInitialization(){}

void EASYActionInitialization::BuildForMaster() const{

	EASYRunAction *runAction = new EASYRunAction();
	SetUserAction(runAction);
}

void EASYActionInitialization::Build() const{

	EASYPrimaryGenerator *generator = new EASYPrimaryGenerator();
	SetUserAction(generator);

	EASYRunAction *runAction = new EASYRunAction();
	SetUserAction(runAction);
}

#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "EASYPhysicsList.hh"
#include "EASYDetectorConstruction.hh"
#include "EASYActionInitialization.hh"

int main(int argc, char** argv){

	G4UIExecutive *ui = nullptr ; //  = new G4UIExecutive(argc, argv)

	#ifdef G4MULTITHREADED
		G4MTRunManager* runManager = new G4MTRunManager;
	#else
		G4RunManager* runManager = new G4RunManager;
	#endif

	// Physics list
	runManager->SetUserInitialization(new EASYPhysicsList());

	// Action initialization
	runManager->SetUserInitialization(new EASYActionInitialization());

	// Detector construction
	runManager->SetUserInitialization(new EASYDetectorConstruction());

	if(argc == 1){
		ui = new G4UIExecutive(argc, argv);
	}

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if(ui){
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		
	} else {
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}

	delete ui;
	delete visManager;
	delete runManager;
	
	return 0;
}
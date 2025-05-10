#include "EASYRunAction.hh"

EASYRunAction::EASYRunAction(){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

	// 1D Histogram
	analysisManager->CreateH1("Edep", "Energy deposit", 500, 0., 3000 * keV);

	// NTuple
	//analysisManager->CreateNtuple("Photons", "Photons");
	//analysisManager->CreateNtupleIColumn("iEvent"); // event number
	//analysisManager->CreateNtupleDColumn("fX"); // photon position x
	//analysisManager->CreateNtupleDColumn("fY");
	//analysisManager->CreateNtupleDColumn("fZ");
	//analysisManager->CreateNtupleDColumn("fGlobalTime"); // total time of event
	//analysisManager->CreateNtupleDColumn("fWlen"); // time of event in local coordinates
	//analysisManager->FinishNtuple(0); // finish the first ntuple
}

EASYRunAction::~EASYRunAction(){}

void EASYRunAction::BeginOfRunAction(const G4Run *run){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance(); // new instance of analysis manager

	G4int runID = run->GetRunID();

	std::stringstream strRunID; // to convert int to string
	strRunID << runID;

	//analysisManager->OpenFile("output" + strRunID.str() + ".root"); // you have a output file for each run
	analysisManager->OpenFile("../../SimNaI/output/pos20.root");

}

void EASYRunAction::EndOfRunAction(const G4Run* run){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance(); // new instance of analysis manager

	analysisManager->Write();
	analysisManager->CloseFile();

	G4int runID = run->GetRunID();
	G4cout << "Finished run " << runID << G4endl;
}

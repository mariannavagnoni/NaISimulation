#include "EASYSensitiveDetector.hh"

EASYSensitiveDetector::EASYSensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
	fTotalEnergyDeposited = 0.0;
}

EASYSensitiveDetector::~EASYSensitiveDetector(){}

void EASYSensitiveDetector::Initialize(G4HCofThisEvent *HCE){
	// Initialize the total energy deposited to zero at the beginning of each event
	fTotalEnergyDeposited = 0.0;
}

void EASYSensitiveDetector::EndOfEvent(G4HCofThisEvent *HCE){

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

	/*Gaussian smearing to simulate the detector resolution*/
	G4double resolution = 0.04; // 40% resolution
	G4double sigma_res = (resolution / 2.355) * fTotalEnergyDeposited; 

	// Smear energy with Gaussian
	G4double smearedEnergy = G4RandGauss::shoot(fTotalEnergyDeposited, sigma_res);

	// line without resolution
	//analysisManager->FillH1(0, fTotalEnergyDeposited); // one histo --> 0
	// line with resolution
	analysisManager->FillH1(0, smearedEnergy);

	// Print the total energy deposited in this event
	G4cout << "Deposited energy (true): " << fTotalEnergyDeposited << " | (smeared): " << smearedEnergy << G4endl;
	//G4cout << "Deposited energy: " << fTotalEnergyDeposited << G4endl; 
}

G4bool EASYSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *){
	// Get the energy deposited in this step
	G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

	G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //info of first interaction info

	G4double fGlobalTime = preStepPoint->GetGlobalTime();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();

	G4double fMomPhotonMeg = momPhoton.mag();

	G4double fWlen = (1.239841939 * eV / fMomPhotonMeg) * 1e3; // wavelength in nm

	// Store in NTuple
	//analysisManager->FillNtupleIColumn(0, 0, eventID); // column O of NTuple 0
	//analysisManager->FillNtupleDColumn(0, 1, posPhoton[0]); // column 1 of NTuple 0
	//analysisManager->FillNtupleDColumn(0, 2, posPhoton[1]); 
	//analysisManager->FillNtupleDColumn(0, 3, posPhoton[2]); 
	//analysisManager->FillNtupleDColumn(0, 4, fGlobalTime); // column 4 of NTuple 0
	//analysisManager->FillNtupleDColumn(0, 5, fWlen); // column 5 of NTuple 0
	//analysisManager->AddNtupleRow(0); // Add row to NTuple 
	
	G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();
	
	if (fEnergyDeposited > 0){
		fTotalEnergyDeposited += fEnergyDeposited;
	}
	
	return true;
}
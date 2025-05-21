#ifndef EASYSENSITIVEDETECTOR_HH
#define EASYSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

// to create a gaussian smearing to the energy deposit --> simulate the resolution of the detector
#include "Randomize.hh"

class EASYSensitiveDetector : public G4VSensitiveDetector{
	public:
		EASYSensitiveDetector(G4String);
		~EASYSensitiveDetector();

	private:
		G4double fTotalEnergyDeposited;

		virtual void Initialize(G4HCofThisEvent *) override;
		virtual void EndOfEvent(G4HCofThisEvent *) override;

		virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;
};

#endif
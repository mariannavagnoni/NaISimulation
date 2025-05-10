/*Everything happens at the begging and the end of a run*/
#ifndef EASYRUNACTION_HH
#define EASYRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class EASYRunAction : public G4UserRunAction
{
	public:
		EASYRunAction();
		~EASYRunAction();

		virtual void BeginOfRunAction(const G4Run *run);
		virtual void EndOfRunAction(const G4Run *run);
};

#endif
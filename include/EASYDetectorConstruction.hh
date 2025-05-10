#ifndef EASYDETECTORCONSTRUCTION_HH
#define EASYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "EASYSensitiveDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"

class EASYDetectorConstruction : public G4VUserDetectorConstruction{
	public:
		EASYDetectorConstruction();
		virtual ~EASYDetectorConstruction();

		virtual G4VPhysicalVolume *Construct();
	
	private:
		G4LogicalVolume *logicNaI;

		virtual void ConstructSDandField();
};

#endif
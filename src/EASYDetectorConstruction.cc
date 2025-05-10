#include "EASYDetectorConstruction.hh"

EASYDetectorConstruction::EASYDetectorConstruction(){}

EASYDetectorConstruction::~EASYDetectorConstruction(){}

G4VPhysicalVolume *EASYDetectorConstruction::Construct(){

	// A boolean variable to check if the geometry overlaps
	G4bool checkOverlaps = true;

	// Define a pointer to have invisible world volume
	G4VisAttributes* invis = new G4VisAttributes();
  invis->SetVisibility(false);

  const G4double vacuum_Z = 1.;
  const G4double vacuum_A = 1.01*g/mole;
  const G4double vacuum_density = 1.e-25*g/cm3; // universe_mean_density

	// nist is a pointer to keep the material inside G4Material and put it inside the world volume
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
	G4Material *detMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	G4Material *coverMat = nist->FindOrBuildMaterial("G4_Al");
	G4Material *vacuumMat = new G4Material("Galactic", vacuum_Z, vacuum_A, vacuum_density, kStateGas, 273*kelvin, 3.e-18*pascal);

	// Define fluorine as a material
	//G4Isotope *F18 = new G4Isotope("F18", 9, 18, 18.000938 * g/mole);
	//G4Element *elF18 = new G4Element("Fluorine-18", "F18", 1);
	//elF18->AddIsotope(F18, 100.0 * perCent);
	//G4Material *F18Mat = new G4Material("F18Mat", 1.51 * g/cm3, 1); // 1 is solid
	//F18Mat->AddElement(elF18, 100.0 * perCent); // 1 is the number of elements

	// Define cobalt as a material
	G4Isotope *Co60 = new G4Isotope("Co60", 27, 60, 59.933822 * g/mole);
	G4Element *elCo60 = new G4Element("Cobalt-60", "Co60", 1);
	elCo60->AddIsotope(Co60, 100.0 * perCent);
	G4Material *Co60Mat = new G4Material("Co60Mat", 8.9 * g/cm3, 1); // 1 is solid
	Co60Mat->AddElement(elCo60, 100.0 * perCent); // 1 is the number of elements

	// Define the world size
	G4double xWorld = 1.0 * m;
	G4double yWorld = 1.0 * m;
	G4double zWorld = 1.0 * m;

	// Define the shape of the world
	/*G4Box takes the half of the total length in x, y, z*/
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*xWorld, 0.5*yWorld, 0.5*zWorld);

	// Define the logical volume of the world
	/*Take the solid volume and apply the material to it*/
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	logicWorld->SetVisAttributes(invis);

	// Define the physical volume of the world
	/*0 = no rotation, G4ThreeVector() = position of the physical volume in world, 0 = no mother volume, 0 = no copy*/
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

	/* Fluorine source */
	G4double rSource = 3 * mm;
	G4double zSource = 3 * mm;

	G4Tubs *solidSource = new G4Tubs("solidSource", 0., 0.5*rSource, 0.5*zSource, 0., 360. * deg);
	G4LogicalVolume *logicSource = new G4LogicalVolume(solidSource, Co60Mat, "logicSource");
	G4VPhysicalVolume *physSource = new G4PVPlacement(0, G4ThreeVector(0., 0., -2.7*cm), logicSource, "physSource", logicWorld, false, 0, checkOverlaps);

	G4Colour myAzure(135./255., 206./255., 235./255., 1);
	G4VisAttributes *SourceVisAtt = new G4VisAttributes(myAzure);
	SourceVisAtt->SetForceSolid(true);
	logicSource->SetVisAttributes(SourceVisAtt);

	// Define a lead box with z = 5 cm, x = 19,8 cm and y = 8,8 cm
	G4double xLead = 19.8 * cm;
	G4double yLead = 8.8 * cm;
	G4double zLead = 5.0 * cm;

	G4Box *solidLead = new G4Box("solidLead", 0.5*xLead, 0.5*yLead, 0.5*zLead);
	//G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicLead");
	//G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicLead, "physLead", logicWorld, false, 0, checkOverlaps);

	G4double xHole = 8.0 * cm;
	G4double yHole = 0.1 * cm;
	G4double zHole = 5.0 * cm;

	G4Box *solidHole = new G4Box("solidHole", 0.5*xHole, 0.5*yHole, 0.5*zHole);
	//G4LogicalVolume *logicHole = new G4LogicalVolume(solidHole, worldMat, "logicHole");
	//G4VPhysicalVolume *physHole = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicHole, "physHole", logicLead, false, 0, checkOverlaps);

	G4SubtractionSolid* subtraction1 = new G4SubtractionSolid("Subtraction1", solidLead, solidHole);

	G4Colour myBlack(0., 0., 0., 0.5);
	//G4VisAttributes *holeVisAtt = new G4VisAttributes(myBlack);
	//holeVisAtt->SetForceSolid(true);
	//logicHole->SetVisAttributes(holeVisAtt);

	// create a cylinder
	G4double rCylinder = 4.5 * mm;
	G4double zCylinder = 5.0 * cm;

	G4Tubs *solidCylinder = new G4Tubs("solidCylinder", 0., 0.5*rCylinder, 0.5*zCylinder, 0., 360. * deg);
	//G4LogicalVolume *logicCylinder = new G4LogicalVolume(solidCylinder,  worldMat, "logicCylinder");
	//G4VPhysicalVolume *physCylinder = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicCylinder, "physCylinder", logicLead, false, 0, checkOverlaps);
	G4SubtractionSolid* subtraction2 = new G4SubtractionSolid("Subtraction2", subtraction1, solidCylinder);

	G4LogicalVolume *logicLead = new G4LogicalVolume(subtraction2, leadMat, "logicLead");
	G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicLead, "physLead", logicWorld, false, 0, checkOverlaps);

	G4Colour myGrey(192./255., 192./255., 192./255., 0.5);
	G4VisAttributes *leadVisAtt = new G4VisAttributes(myGrey);
	leadVisAtt->SetForceSolid(true);
	logicLead->SetVisAttributes(leadVisAtt);

	//G4VisAttributes *cylVisAtt = new G4VisAttributes(myBlack);
	//cylVisAtt->SetForceSolid(true);
	//logicCylinder->SetVisAttributes(cylVisAtt);

	/* NaI(Tl) complete detector */
	G4double wallThickness = 1.0 * mm;
	G4double xDetector = 109.0 * mm;
	G4double yDetector = 109.0 * mm;
	G4double zDetector = 254.0 * mm;

	G4double theta = 90 * degree;
	G4RotationMatrix *rot = new G4RotationMatrix();
	rot->rotateX(theta);

  //Aluminum Box
	G4Box *solidOut = new G4Box("solidOut", 0.5*xDetector, 0.5*yDetector, 0.5*zDetector);
	G4LogicalVolume *logicOut = new G4LogicalVolume(solidOut, coverMat, "logicOut");
	G4VPhysicalVolume *physOut  = new G4PVPlacement(rot, G4ThreeVector(0.0, -76.4*mm, 79.5*mm), logicOut, "physOut", logicWorld, false, 0, checkOverlaps);

	G4VisAttributes *OutVisAtt = new G4VisAttributes(myGrey);
	OutVisAtt->SetForceSolid(true);
	logicOut->SetVisAttributes(OutVisAtt);

  G4Box *solidIn = new G4Box("solidIn", 0.5*(xDetector) - wallThickness, 0.5*(yDetector) - wallThickness, 0.5*(zDetector) - wallThickness);
  G4LogicalVolume *logicIn = new G4LogicalVolume (solidIn, vacuumMat, "logicIn");
	G4PVPlacement *physIn = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.*mm), logicIn, "logicIn", logicOut, false,  0, checkOverlaps);

	//G4VisAttributes *InVisAtt = new G4VisAttributes(myAzure);
	//InVisAtt->SetForceSolid(true);
	//logicIn->SetVisAttributes(InVisAtt);
  logicIn->SetVisAttributes(invis); // vacuum inside is invisible

  // NaI(Tl) crystal
  G4double xNaI = 102.0 * mm;
	G4double yNaI = 102.0 * mm;
	G4double zNaI = 203.0 * mm;

	G4Box *solidNaI = new G4Box("solidNaI", 0.5*xNaI, 0.5*yNaI, 0.5*zNaI);
	logicNaI = new G4LogicalVolume(solidNaI, detMat, "logicNaI");
	G4PVPlacement *physNaI = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.*mm - 23.8*mm), logicNaI, "logicNaI", logicIn, false, 1, checkOverlaps);

  G4VisAttributes *NaIVisAtt = new G4VisAttributes(myAzure);
	NaIVisAtt->SetForceSolid(true);
	logicNaI->SetVisAttributes(NaIVisAtt);

	return physWorld;
}

void EASYDetectorConstruction::ConstructSDandField(){

	EASYSensitiveDetector *sensDet = new EASYSensitiveDetector("SensitiveDetector"); // Define the sensitive detector
	logicNaI->SetSensitiveDetector(sensDet);
	G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}

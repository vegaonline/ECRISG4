/ *************************************************************
//     ECR ion source Bremsstrahlung simulation
//    file: src/ECRIS_DetectorConstruction.cc
//    Abhijit Bhattacharyya : BARC : Mumbai : INDIA
// *************************************************************

#include "ECRIS_DetectorConstruction.hh"
#include "ECRIS_DetectorMessenger.hh"

ECRIS_DetectorConstruction ::ECRIS_DetectorConstruction() : G4VUserDetectorConstruction(),
    fPlasmaChamberAlLV(null), fPlasmaChamberTaLV(null), fPlasmaChamberTaPV(null), fPlasmaChamberTaPV(null), fMaterial(null)
  {
    DefineMaterials();
    fECRMess = new ECRIS_DetectorMessenger(this);
    fFixDimension();
  }

ECRIS_DetectorConstruction::~ECRIS_DetectorConstruction() {
  delete fECRMess;
}

ECRIS_DetectorConstruction::DefineMaterials() {
  G4double density, a, z;
  G4NistManager* man = G4G4NistManager::Instance();

  G4Material* argosGas = new G4Material("ArgonGas", z = 18, a = 39.948*g/mole, density = 1.782*mg/cm3, kStateGas, 273.15*kelvin, 1.0*atmosphere); // Argon Gas

  density = universe_mean_density; // from G4PhysicalConstants
  new G4Material("Galactic", z = 1.0, a = 1.008*g/mole, density, kStateGas, 2.73*kelvin, 3.0e-18*pascal);   // vacuum

  G4bool isotopes = false;
  G4Element* Al = man->FindOrBuildElement("Al", isotopes);
  G4Element* Ta = man->FindOrBuildElement("Ta", isotopes);
  G4Element* Cu = man->FindOrBuildElement("Cu", isotopes);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void ECRIS_DetectorConstruction::fFixDimension() {
  fRadialGap = 30.0e-3*mm; // 30 um gap
  fMaxRadChambers = 41*mm;
  fMaxHeightChambers = 450.0*mm;
  fAlChamberWallThk = 5.0*mm;
  fTaChamberWallThk = 0.3*mm;    // This can be varied to change xray
  fTaTubeOuterRad = fMaxRadChambers;
  fTaTubeInnerRad = fMaxRadChambers - fTaChamberWallThk;
  fAlTubeOuterRad = fTaTubeInnerRad - fRadialGap;
  fAlTubeInnerRad = fAlTubeOuterRad - fAlChamberWallThk;
  fTaTubeHalfHeight = 0.5 * fMaxHeightChambers;
  fAlTubeHalfHeight = fTaTubeHalfHeight - fTaChamberWallThk - fRadialGap;
}

G4VPhysicalVolume* ECRIS_DetectorConstruction::Construct() {

  fTubeAl = new G4Tubs("PlasmaTubeAl", fAlTubeInnerRad, fAlTubeOuterRad, fAlTubeHalfHeight, 0.0*deg, 360.0*deg);
  fTubeAlLid = new G4Tubs("PlasmaTubeAlLid", 0.0*mm, fAlTubeOuterRad, fAlChamberWallThk, 0.0*deg, 360.0*deg);
  fPlasmaTubeAl = new G4UnionSolid("TubeAlLid1", fTubeAl, fTubeAlLid, &unitRot, G4ThreeVector(0, 0, -fAlTubeHalfHeight));  // rot = 0.0
  fPlasmaChamberAlLV = G4LogicalVolume()

  fTubeTa = new G4Tubs("PlasmaTubeTa", fTaTubeInnerRad, fTaTubeOuterRad, fTaTubeHalfHeight, 0.0*deg, 360.0*deg);
  fTubeTaLid = new G4Tubs("PlasmaTubeTaLid", 0.0*mm, fTaTubeOuterRad, fTaChamberWallThk, 0.0*deg, 360.0*deg);
  fPlasmaTubeTa = new G4UnionSolid("TubeTaLid1", fTubeTa, fTubeTaLid, &unitRot, G4ThreeVector(0, 0, -fTaTubeHalfHeight));  // rot = 0.0
}

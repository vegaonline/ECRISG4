// *************************************************************
//     ECR ion source Bremsstrahlung simulation
//    file: include/ECRIS_DetectorConstruction.hh
//    Abhijit Bhattacharyya : BARC : Mumbai : INDIA
// *************************************************************

#ifndef ECRIS_DetectorConstruction_H
#define ECRIS_DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Cache.hh"
#include "globals.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4VPhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

class G4LogicalVolume;
class G4Material;
class ECRIS_DetectorMessenger;
//class ECRIS_GlobalMagFieldMessenger;


//....ooooOOOOoooo....
class ECRIS_DetectorConstruction : public G4VUserDetectorConstruction {
public:
  ECRIS_DetectorConstruction();
  ~ECRIS_DetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  void SetMaterial(const G4String&);

public:
  const G4VPhysicalVolume* GetWorld()     { return fWorldBoxPV;}
  G4Material* GetMaterial()                          { return fMaterial;}
  void           DefineMaterials();
  void fPrintParameters();

private:
  G4VPhysicalVolume* fConstructVolume();
  void fFixDimension();   // fix dimension of all chambers etc.


private:
  G4VPhysicalVolume*      fWorldBoxPV;
  G4Material*                     fMaterial;
  G4LogicalVolume*          fPlasmaChamberAlLV;
  G4VPhysicalVolume*      fPlasmaChamberAlPV;
  G4LogicalVolume*          fPlasmaChamberTaLV;
  G4VPhysicalVolume*      fPlasmaChamberTaPV;
  G4LogicalVolume*          fYokeLV;
  G4VPhysicalVolume*      fYokePV;
  G4Tubs*                           fTubeAl;
  G4Tubs*                           fTubeAlLid;
  G4UnionSolid*                fPlasmaTubeAl;
  G4Tubs*                           fTubeTa;
  G4Tubs*                           fTubeTaLid;
  G4UnionSolid*                fPlasmaTubeTa;

  G4double                         fMaxRadChambers;
  G4double                         fMaxHeightChambers;
  G4double                         fAlChamberWallThk;
  G4double                         fTaChamberWallThk;
  G4double                         fRadialGap;

  G4double                         fAlTubeInnerRad;
  G4double                         fAlTubeOuterRad;
  G4double                         fAlTubeHalfHeight;

  G4double                         fTaTubeInnerRad;
  G4double                         fTaTubeOuterRad;
  G4double                         fTaTubeHalfHeight;


  ECRIS_DetectorMessenger* fECRMess;

};
//....ooooOOOOoooo....

#endif

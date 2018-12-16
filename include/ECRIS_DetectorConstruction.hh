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

class G4LogicalVolume;
class G4Material;
//class ECRIS_DetectorMessenger;
//class ECRIS_GlobalMagFieldMessenger;


//....ooooOOOOoooo....
class ECRIS_DetectorConstruction : public G4VUserDetectorConstruction {
public:
  ECRIS_DetectorConstruction();
  ~ECRIS_DetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();
  void SetMaterial(const G4String&);

public:
  const G4VPhysicalVolume* GetWorld()     { return fWorldBoxPV;}
  G4Material* GetMaterial()                          { return fMaterial;}
  void fPrintParameters();

private:
  G4VPhysicalVolume*      fWorldBoxPV;
  G4Material*                     fMaterial;
  G4LogicalVolume*          fPlasmaChamberLV;
  G4G4VPhysicalVolume* fPlasmaChamberPV;
  G4LogicalVolume*          fYokeLV;
  G4G4VPhysicalVolume* fYokePV;

private:
  void fDefineMaterial();
  G4VPhysicalVolume* fConstructVolume();
};
//....ooooOOOOoooo....

#endif

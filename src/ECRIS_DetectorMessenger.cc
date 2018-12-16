*************************************************************
//     ECR ion source Bremsstrahlung simulation
//    file: src/ECRIS_DetectorMessenger.cc
//    Abhijit Bhattacharyya : BARC : Mumbai : INDIA
// *************************************************************

#include "ECRIS_DetectorMessenger.hh"

ECRIS_DetectorMessenger::ECRIS_DetectorMessenger(ECRIS_DetectorConstruction* ECRIS) : G4UImessenger(),
  fSetup(ECRIS), fECRSRCDir(0), fDetectorDir(0), fMatterCmd(0), fSizeCmd(0){
    fECRSRCDir = new G4G4UIdirectory("/ECRSRC/");
    fECRSRCDir->SetGuidance("ECRIS setup construction commands");
}

ECRIS_DetectorMessenger::~ECRIS_DetectorMessenger() {
  delete fECRSRCDir;
}

void ECRIS_DetectorMessenger::SetNewValue(G4G4UIcommand* command, G4String newValue) {
  if (command = fMatterCmd) fSetup->SetMaterial(newValue);
}

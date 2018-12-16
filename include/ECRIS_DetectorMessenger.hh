/ *************************************************************
//     ECR ion source Bremsstrahlung simulation
//    file: include/ECRIS_DetectorMessenger.hh
//    Abhijit Bhattacharyya : BARC : Mumbai : INDIA
// *************************************************************

#ifndef ECRIS_DetectorMessenger_H
#define ECRIS_DetectorMessenger_H 1

#include "G4UImessenger.hh"
#include "globals.hh"

class ECRIS_DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class ECRIS_DetectorMessenger : public G4UImessenger {
public:
  ECRIS_DetectorMessenger(ECRIS_DetectorConstruction* );
  ~ECRIS_DetectorMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

private:
  ECRIS_DetectorConstruction* fSetup;
  G4UIdirectory*  fECRSRCDir;
  G4UIdirectory* fDetectorDir;
  G4UIcmdWithAString* fMatterCmd;
  G4UIcmdWithADoubleAndUnit* fSizeCmd;
};

#endif

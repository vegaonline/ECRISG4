// *************************************************************
//     ECR ion source Bremsstrahlung simulation
//    file: ECRmain.cc
//    Abhijit Bhattacharyya : BARC : Mumbai : INDIA
//   ****** examples/extended/electromagnetic/TestEm1, TestEm7, TestEm10,   @@TestEm11 (MT)@@
// *************************************************************

#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "ECRIS_DetectorConstruction.hh"
#include "ECRIS_PhysicsList.hh"
#include "ECRIS_RunAction.hh"
#include "ECRIS_ActionInitialization.hh"


void PrintUsage() {
  G4cerr << G4endl;
  G4cerr << "Usage: ECRmain [-m macro] [-u UIsession] [-t nThreads] "  << G4endl;
  G4cerr << "\t \t Here -t option is available for multithreaded mode only."                                                << G4endl;
  G4cerr << system("ls -l Data/GeomData/*.gdml");
  G4cerr << G4endl;
}


int main (int argc, char** argv) {
  G4String macro;
  G4String session;
  if (argc < 2 || argc > 8) {
    PrintUsage();
    return -1;
  }

  // Choose the Random Engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED
  G4int nThreads = G4Threading::G4GetNumberOfCores();
#endif

  for (G4int i = 2; i < argc; i += 2) {
    G4String inArg = G4String(argv[i]);
    if (inArg == "-m") macro = argv[i + 1];
    if (inArg == "-u") session = argv[i + 1];
#ifdef G4MULTITHREADED
    if (inArg == "-t")   nThreads = (G4String(argv[i+1]) == "NMAX")  ? G4Threading::G4GetNumberOfCores()  : G4UIcommand::ConvertToInt(argv[i + 1]);
#endif
    if (inArg != "-m" && inArg != "-u" && inArg != "-t") {
      PrintUsage();
      return -1;
    }
  }

  // construction of default run manager
#ifdef G4MULTITHREADED
  auto fRunManager = new G4MTRunManager;
  if ( nThreads > 0 )    fRunManager->SetNumberOfThreads(nThreads);
  G4cout << "Code is started with " << fRunManager->GetNumberOfThreads() << " threads. " << G4endl;
#else
  auto fRunManager = new G4RunManager;
#endif

  // geometry construction
  auto fGeomConstruct = new ECRIS_DetectorConstruction();
  fRunManager->SetUserInitialization(fGeomConstruct);

  // physics list
  fRunManager->SetUserInitialization(new ECRIS_PhysicsList());

  // Action Initialization
  fRunManager->SetUserInitialization(new ECRIS_ActionInitialization());

  //initialize visualization
  G4VisManager* visManager = nullptr;

  //get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
    //interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    ui->SessionStart();
    delete ui;
  } else  {
    //batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  //job termination
  delete visManager;
  delete runManager;

  return 0;
}

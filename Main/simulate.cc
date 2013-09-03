//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "cuboDetectorConstruction.h"
#include "DetectorConstruction.h"
#include "SimpleGeneratorAction.h"
#include "RunAction.h"
#include "EventAction.h"
#include "SteppingAction.h"
#include "cuboSteppingAction.h"
#include "StackingAction.h"
#include "cuboStackingAction.h"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"


//#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
//#endif

//#ifdef G4UI_USE
#include "G4UIExecutive.hh"
//#endif

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


int main(int argc,char** argv)
{
  // Choose the Random engine
  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new CaloCube::cuboDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  //G4VUserPhysicsList* physicsList = new ExN06PhysicsList; //FTFP_BERT;
  
  // Optical Physics
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();

  opticalPhysics->SetWLSTimeProfile("delta");

  opticalPhysics->SetScintillationYieldFactor(1.);
  opticalPhysics->SetScintillationExcitationRatio(1.0);

  opticalPhysics->SetMaxNumPhotonsPerStep(1000000);
  opticalPhysics->SetMaxBetaChangePerStep(100000.0);

  opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);
  physicsList->RegisterPhysics( opticalPhysics );
  std::cout << "Optical Physics " << physicsList->GetPhysics("Optical") << std::endl;
  
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  // Primary generator action
  runManager->SetUserAction(new SimpleGeneratorAction());

  // Set user action classes
  //
  // Stepping action
  runManager->SetUserAction(new CaloCube::cuboSteppingAction());     

  // Event action
  runManager->SetUserAction(new CaloCube::EventAction());

  // Run action
  runManager->SetUserAction(new CaloCube::RunAction());

  G4UserStackingAction* stacking_action = new CaloCube::cuboStackingAction;
  runManager->SetUserAction(stacking_action);

     
  // Initialize G4 kernel
  //
  runManager->Initialize();
  
//#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
//#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session
//#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
//#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
//#else
//    UImanager->ApplyCommand("/control/execute init.mac"); 
//#endif
    ui->SessionStart();
    delete ui;
//#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
//#ifdef G4VIS_USE
  delete visManager;
//#endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

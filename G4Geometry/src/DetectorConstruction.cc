#include "DetectorConstruction.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include <sstream>
#include "AerogelFactory.h"
#include "CsICrystalFactory.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using namespace CaloCube;

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{ 

  G4NistManager* nist = G4NistManager::Instance();
  // Envelope parameters
  //
  G4double env_sizeXY = 5*m, env_sizeZ = 5*m;
  G4bool checkOverlaps = false;

  CsICrystalFactory csifactory;
  AerogelFactory aerogelfactory;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        world_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4double offset = 1.8*cm;
  for (int i=-20; i < 20; ++i){
    for (int j=-20; j < 20; ++j){			
      for (unsigned int k=0; k < 40; ++k){
        //std::cout << "i:" << i << " j:" << j << " k:" << k << std::endl;
   
        //     
        // Shape 1
        //
        std::stringstream ss;
        ss << i << " " << j << " " << k;


        G4LogicalVolume* logicShape1 = 0;
        //G4Material* shape1_mat = csitl; //nist->FindOrBuildMaterial("G4_A-150_TISSUE");
        if ((i+j+k)%2 == 0){
          //std::cout << ss.str() << " is Aerogel" << std::endl;
          //shape1_mat = Aerog;
          logicShape1 = aerogelfactory.build(ss.str());  
        } else {
          logicShape1 = csifactory.build(ss.str());
        }

        G4ThreeVector pos1 = G4ThreeVector(3.6*cm*i, 3.6*cm*j, 3.6*cm*k+offset);
              
        // Box shape
                     
        new G4PVPlacement(0,                       //no rotation
                          pos1,                    //at position
                          logicShape1,             //its logical volume
                          ss.str(),                //its name
                          logicEnv,                //its mother  volume
                          false,                   //no boolean operation
                          0,                       //copy number
                          checkOverlaps);          //overlaps checking


        // Set scoring volume to stepping action 
        // (where we will account energy deposit)
        //
        //B1SteppingAction* steppingAction = B1SteppingAction::Instance(); 
        //steppingAction->SetVolume(logicShape1);
      }    
    }      
  }


  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

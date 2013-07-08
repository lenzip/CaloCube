#include "StackingAction.h"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include <sstream>
#include "Exception.h"
#include "SteppingAction.h"

using namespace CaloCube;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction()
: nScint(0), nCher(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{ 
  /*
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()){ // particle is optical photon
    if(aTrack->GetParentID()>0){ // particle is secondary
      //G4LogicalVolume* volume = B1SteppingAction::Instance()->GetVolume();
      //    = aTrack->GetStep()->GetPreStepPoint()->GetTouchableHandle()
      //          ->GetVolume()->GetLogicalVolume();
      if(aTrack->GetCreatorProcess()->GetProcessName()=="Scintillation" ){//&&
          //volume->GetMaterial()->GetName()=="CsI(Tl)"){
          nScint++;
      } else if (aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov"){// &&
                 //volume->GetMaterial()->GetName()=="Aerogel"){
          nCher++;
      }
      return fKill;
    }
  }
  return fUrgent;
  */
  if(aTrack->GetParentID()>0){
    SteppingAction* sa = SteppingAction::Instance();
    if (!sa){
      throw CaloCube::Exception("StackingAction") << "Cannot retrieve the SteppingAction";
    }
    if (sa->GetVolume()->GetMaterial()->GetName()=="CsI(Tl)" || sa->GetVolume()->GetMaterial()->GetName()=="Aerogel"){
      std::string name = sa->GetVolume()->GetName();
      std::stringstream ss;
      ss << name;
      int is, js, ks;
      ss >> is >> js >> ks;
      Particle p(aTrack->GetDefinition()->GetParticleName(), 
                aTrack->GetCreatorProcess()->GetProcessName(), 
                aTrack->GetTotalEnergy(), 
                aTrack->GetMomentum(),
                is, js, ks);
      p.setTrack(aTrack);           
      _particles.push_back(p);
    }
  }
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()){
    return fKill;
  }

  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::NewStage()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::PrepareNewEvent()
{ 
  nScint = 0.; 
  nCher =0.; 
  _particles.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

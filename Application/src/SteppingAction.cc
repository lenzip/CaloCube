#include "SteppingAction.h"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4OpticalPhoton.hh"
#include "StackingAction.h"
#include "Exception.h"


using namespace CaloCube;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction* SteppingAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction* SteppingAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction()
: G4UserSteppingAction(),
  fVolume(0),
  //nScint(0),
  //nCher(0),
  //eScint(0.),
  //eCher(0.),
  firstInteractionOccurred(false),
  start(0),
  end(0),
  totalEnergy(0.)
{ 
  fgInstance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ 
  fgInstance = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // get volume of the current step
  //G4LogicalVolume* volume 
  fVolume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  //if (volume != fVolume ) return;
  G4Track* track = step->GetTrack();
  if (track->GetCreatorProcess()){  
      if(track->GetParentID()>0){
        // particle is secondary
        if (fVolume->GetMaterial()->GetName()=="CsI(Tl)" || fVolume->GetMaterial()->GetName()=="Aerogel"){
          if (!firstInteractionOccurred){
            firstInteractionOccurred = true;
            start = step->GetPreStepPoint();
          }
          end = step->GetPreStepPoint(); 
          totalEnergy += step->GetTotalEnergyDeposit();
          std::string name = fVolume->GetName();
          std::stringstream ss;
          ss << name;
          int is, js, ks;
          ss >> is >> js >> ks; 
          Position curPos(is, js, ks);
          // check if we have been here before:
          int index = _crystals.size() + 1;
          for (unsigned int i = 0; i < _crystals.size(); ++i){
            if (_crystals[i].getPosition() == curPos){
              index = i;
              break;
            }
          }
          if (index > _crystals.size()){
            _crystals.push_back(Crystal(is, js, ks, fVolume->GetMaterial()->GetName()));
            index = _crystals.size() -1;
          }
          // now check which particle this is:
          G4RunManager* rmanager = G4RunManager::GetRunManager();
          const StackingAction* sa = dynamic_cast<const StackingAction*>(rmanager->GetUserStackingAction());   
          if (!sa){
            throw CaloCube::Exception("SteppingAction") << "Cannot retrieve the Stacking Action";
          }
          const std::vector<Particle>& particlesSoFar = sa->getParticles();
          bool found = false; 
          int iTrack = particlesSoFar.size() +1;
          for (unsigned int i = 0; i < particlesSoFar.size(); ++i) {
            if (particlesSoFar[i].getTrack() == track){
              found = true;
              iTrack = i;
              break;
            }
          }
          if (!found)
            throw CaloCube::Exception("SteppingAction") << "Cannot retrieve track from StackingAction!!";
      
          //now check if this track originated here
          if (particlesSoFar[iTrack].getCrystalPosition() == curPos){
            _crystals[index].addParticleOriginatingHere(Ref<Particle>("tree", "particles", iTrack), step->GetTotalEnergyDeposit());
            if (track->GetDefinition()->GetParticleName() == "pi0")
              _crystals[index].addPi0OriginatingHere(Ref<Particle>("tree", "particles", iTrack), track->GetTotalEnergy());
            if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()){
              _crystals[index].addOpticalOriginatingHere(Ref<Particle>("tree", "particles", iTrack), track->GetTotalEnergy());
            }
          } else {
            _crystals[index].addParticlePassingHere(Ref<Particle>("tree", "particles", iTrack), step->GetTotalEnergyDeposit());
          }     

        }
      }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::Reset()
{
  //eCher = 0.;
  //eScint = 0.;
  //nCher = 0.;
  //nScint =0.;
  firstInteractionOccurred = false;
  start = 0;
  end = 0;
  totalEnergy = 0.;
  fVolume =0;
}


#ifndef CaloCubeSteppingAction_h
#define CaloCubeSteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include "G4StepPoint.hh"
#include "globals.hh"
#include "Crystal.h"

class G4LogicalVolume;

/// Stepping action class
/// 
/// It holds data member fEnergy for accumulating the energy deposit
/// in a selected volume step by step.
/// The selected volume is set from  the detector construction via the  
/// SetVolume() function. The accumulated energy deposit is reset for each 
/// new event via the Reset() function from the event action.

namespace CaloCube {

class SteppingAction : public G4UserSteppingAction
  {
    public:
      SteppingAction();
      virtual ~SteppingAction();

      // static access method
      static SteppingAction* Instance();

      // method from the base class
      virtual void UserSteppingAction(const G4Step*);

      // reset accumulated energy
      void Reset();

      // set methods
      void SetVolume(G4LogicalVolume* volume) { fVolume = volume; }
    
      // get methods
      G4LogicalVolume* GetVolume() const { return fVolume; }
      //const G4double& GetNScintPhotons() const { return nScint; }
      //const G4double& GetNCherenkovPhotons() const { return nCher; }
      //const G4int& GetEScint() const { return eScint; }
      //const G4int& GetECherenkov() const { return eCher; }
      const G4StepPoint* GetStartingPoint() const { return start; }
      const G4StepPoint* GetEndingPoint() const { return end; }
      const G4double& GetTotalEnergy() const {return totalEnergy; }

      const std::vector<Crystal>& getCrystals() const { return _crystals; }
      
    private:
      static SteppingAction* fgInstance;  
    
      G4LogicalVolume* fVolume;
      //G4double nScint;
      //G4double nCher;
      //G4double eScint;
      //G4double eCher;
      bool firstInteractionOccurred;
      G4StepPoint* start;
      G4StepPoint* end;
      G4double totalEnergy;
      std::vector<Crystal> _crystals;
  };

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

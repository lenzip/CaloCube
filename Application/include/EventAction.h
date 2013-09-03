#ifndef CaloCubeEventAction_h
#define CaloCubeEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "Particle.h"
#include "Crystal.h"
#include "Shower.h"
#include <vector>

class B1SteppingAction;
class TTree;
class TFile;

/// Event action class
///
/// It holds data member fEnergySum and fEnergy2Sum for accumulating 
/// the event energy deposit its square event by event.
/// These data are then used in the run action to compute the dose.
/// The accumulated energy and enrgy square sums are reset for each 
/// new run via the Reset() function from the run action.
namespace CaloCube {

  class EventAction : public G4UserEventAction
  {
    public:
      EventAction();
      virtual ~EventAction();
      
      // static access method
      static EventAction* Instance();

      virtual void BeginOfEventAction(const G4Event* event);
      virtual void EndOfEventAction(const G4Event* event);

      void Reset();

      // get methods
      G4double GetEnergySum() const { return fEnergySum; }
      G4double GetEnergy2Sum() const { return fEnergy2Sum; }
       
    private:
      static EventAction* fgInstance;  

      G4int     fPrintModulo;
      G4double  fEnergySum;
      G4double  fEnergy2Sum;
      TTree * fTree;
      TFile * fOutput;
      //tree variables
      double nCher;
      double nScint;
      double totalEnergy;
      double xstart, ystart, zstart;
      double xend, yend, zend;
      std::vector<Particle> _particles;
      std::vector<Crystal> _crystals;
      std::vector<int> _photonsCollected;
      Shower* _shower;

  };

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

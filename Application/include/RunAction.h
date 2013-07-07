#ifndef CaloCubeRunAction_h
#define CaloCubeRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

namespace CaloCube {
  class RunAction : public G4UserRunAction
  {
    public:
      RunAction();
      virtual ~RunAction();

      virtual void BeginOfRunAction(const G4Run*);
      virtual void   EndOfRunAction(const G4Run*);
  };

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


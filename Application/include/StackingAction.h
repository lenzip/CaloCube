#ifndef CaloCubeStackingAction_H
#define CaloCubeStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "Particle.h"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace CaloCube {
  class StackingAction : public G4UserStackingAction
  {
    public:
      StackingAction();
     ~StackingAction();

    public:
      G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
      void NewStage();
      void PrepareNewEvent();
      const G4double& GetNScintPhotons() const { return nScint; }
      const G4double& GetNCherenkovPhotons() const { return nCher; }
      const std::vector<Particle>& getParticles() const { return _particles; }

    private:
      G4double nScint;
      G4double nCher;
      G4double eScint;
      G4double eCher;
      std::vector<Particle> _particles;
  };

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


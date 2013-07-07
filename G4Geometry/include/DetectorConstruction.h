#ifndef CaloCubeDetectorConstruction_h
#define CaloCubeDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

namespace CaloCube {
  /// Detector construction class to define materials and geometry.
  class DetectorConstruction : public G4VUserDetectorConstruction
  {
    public:
      DetectorConstruction();
      virtual ~DetectorConstruction();

    public:
      virtual G4VPhysicalVolume* Construct();
  };

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


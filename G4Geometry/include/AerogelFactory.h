#ifndef CaloCubeAerogelFactory_h
#define CaloCubeAerogelFactory_h

#include "VolumeFactory.h"

class G4LogicalVolume;
class G4VSolid;
class G4Material;



namespace CaloCube {
  class AerogelFactory : public VolumeFactory {
    
    public:
    AerogelFactory();

  };

}

#endif

#ifndef CaloCubeCsICrystalFactory_h
#define CaloCubeCsICrystalFactory_h

#include "VolumeFactory.h"

class G4LogicalVolume;
class G4VSolid;
class G4Material;



namespace CaloCube {
  class CsICrystalFactory : public VolumeFactory {
    
    public:
    CsICrystalFactory();

  };

}

#endif

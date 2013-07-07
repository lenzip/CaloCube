#ifndef CaloCubeVolumeFactory_h
#define CaloCubeVolumeFactory_h

class G4LogicalVolume;
class G4VSolid;
class G4Material;
#include <string>


namespace CaloCube {
  class VolumeFactory {
    
    public:
    VolumeFactory();
    virtual G4LogicalVolume* build(std::string) const;

    protected:
    G4VSolid* _shape;
    G4Material* _material;

  };

}

#endif

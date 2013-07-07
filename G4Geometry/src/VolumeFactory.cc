#include "VolumeFactory.h"
#include "G4Material.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "DataFormats/include/Exception.h"
#include <iostream>
#include <typeinfo>

using namespace CaloCube;
using namespace std;

VolumeFactory::VolumeFactory():
  _shape(0),
  _material(0){}

G4LogicalVolume* VolumeFactory::build(std::string name) const {
  if ((!_shape) || (!_material)){
    throw Exception("VolumeFactory") << "Null shape or material.";
  }  
  return new G4LogicalVolume(_shape, _material, name);  
}
  


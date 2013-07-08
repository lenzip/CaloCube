#include "Shower.h"

namespace CaloCube {

  using namespace std;

  Shower::Shower():
  _event(0),
  _threshold(0.),
  _crystals(),
  _crystalsAbove(){}

  Shower::Shower(unsigned int ievent, double threshold, const std::vector<Crystal>& crystals):
  _event(ievent),
  _threshold(threshold),
  _crystals(),
  _crystalsAbove()
  {
    
    _nOptical = 0;
    for (unsigned int i = 0; i < crystals.size(); ++i){
      _totalEnergy += crystals[i].getTotalEnergy();
      Ref<Crystal> curRef("tree", "crystals", i); 
      _crystals.push_back(curRef);
      if (crystals[i].getTotalEnergy() > _threshold){
        _crystalsAbove.push_back(curRef);        
      }
      _nOptical += crystals[i].getAllOpticalOriginatingHere().size(); 

    }
    _nCrystals = _crystalsAbove.size();

  }

}

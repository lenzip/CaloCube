#include "Shower.h"

namespace CaloCube {

  using namespace std;

  Shower::Shower(unsigned int ievent, double threshold, const std::vector<Crystal>& crystals):
  _event(ievent),
  _threshold(threshold){

  }

}

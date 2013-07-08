#include "Crystal.h"


namespace CaloCube {
  using namespace std;
  Crystal::Crystal(int x, int y, int z, string material):
    _pos(x, y, z),
    _material(material){
    
  }
  
  void Crystal::addParticlePassingHere(const Ref<Particle>& ref, double energyDeposit){
    _allParticlesPassingHere.push_back(std::make_pair(ref, energyDeposit));
    _totalEnergy += energyDeposit;
  }

  void Crystal::addParticleOriginatingHere(const Ref<Particle>& ref, double energyDeposit){
    _allParticlesOriginatingHere.push_back(std::make_pair(ref, energyDeposit));
    _totalEnergy += energyDeposit;
  }

  void Crystal::addPi0OriginatingHere(const Ref<Particle>& ref, double energyDeposit){
    _allPiOOriginatingHere.push_back(std::make_pair(ref, energyDeposit));
  }
  
  void Crystal::addOpticalOriginatingHere(const Ref<Particle>& ref, double energyDeposit){
    _allOpticalOriginatingHere.push_back(std::make_pair(ref, energyDeposit));
  }
}

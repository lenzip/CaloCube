#ifndef CaloCubeCrystal_h
#define CaloCubeCrystal_h

#include <string>
#include "Ref.h"
#include "Particle.h"
#include "Position.h"
#include <vector>
#include <map>

namespace CaloCube {

  class Crystal {
  public:
    Crystal():_pos(0,0,0), _material("") {}	
    Crystal(int x, int y, int z, std::string material);

    // getters
    // position
    const Position& getPosition() const { return _pos; }
    // material
    std::string getMaterial() const { return _material; }
    // total energy deposit
    double getTotalEnergy() const { return _totalEnergy; }
    // get the particles originating here and the associated energy deposit
    const std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > getAllParticlesBornHere() const { return _allParticlesOriginatingHere; }
    // get all particles passing here, but not originating here, with their energy deposit
    const std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > getAllParticlesPassingHere() const { return _allParticlesPassingHere; }
    // get all Pi0 originating here with their energy deposit
    const std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > getAllPi0PassingHere() const { return _allPiOOriginatingHere; }

    // const get total optical photons
    const std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > getAllOpticalOriginatingHere() const { return _allOpticalOriginatingHere;  } 


    //setters
    void addParticlePassingHere(const CaloCube::Ref<CaloCube::Particle>& ref, double energyDeposit);
    void addParticleOriginatingHere(const CaloCube::Ref<CaloCube::Particle>& ref, double energyDeposit);
    void addPi0OriginatingHere(const CaloCube::Ref<CaloCube::Particle>& ref, double energyDeposit);
    void addOpticalOriginatingHere(const CaloCube::Ref<CaloCube::Particle>& ref, double energyDeposit);




  private:
    //coordinates in units of number of crystals
    Position _pos;
    // the material
    std::string _material;

    double _totalEnergy;

    std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > _allParticlesOriginatingHere;
    std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > _allParticlesPassingHere;
    std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > _allPiOOriginatingHere;
    std::vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> > _allOpticalOriginatingHere;



  };

}

#endif

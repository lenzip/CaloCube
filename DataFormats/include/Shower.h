#ifndef CaloCubeShower_h
#define CaloCubeShower_h

#include <vector>
#include "Ref.h"
#include "Crystal.h"

namespace CaloCube {

  class Shower {

    public:

    // Constructor
    Shower();
    Shower(unsigned int iEvent, double threshold, const std::vector<CaloCube::Crystal>& crystals);

    // return the event number
    unsigned int getEventNumber() const { return _event; }
    // return the number of crystals above threshold
    double getNCrystalsAboveThreshold() const { return _nCrystals; }
    // return total energy deposit
    double getTotalEnergy() const { return _totalEnergy; }
    // access the crystals container
    const std::vector<CaloCube::Ref<CaloCube::Crystal> >& getAllCrystals() const { return _crystals; }
    // access the crystals above threshold
    const std::vector<CaloCube::Ref<CaloCube::Crystal> >& getCrystalsAboveThreshold() const { return _crystalsAbove; }
    // get the total number of scintillation photons
    double getNScintillation() const { return _nScint; } 
    // get the total number of Cherenlov photons
    double getNCherenkov() const { return _nCherenkov; }



    private:
    unsigned int _event;
    // threshold for cached values
    double _threshold;
    // total energy deposit
    double _totalEnergy;
    // number of crystals with energy above threshold
    double _nCrystals;
    // the vector of crystals
    std::vector<CaloCube::Ref<CaloCube::Crystal> > _crystals;
    // the vector of crystals above threshold
    std::vector<CaloCube::Ref<CaloCube::Crystal> > _crystalsAbove;
    // number of scitillation photons in total
    double _nScint;
    // number of Cherenkov photons in total
    double _nCherenkov;

  };

}

#endif

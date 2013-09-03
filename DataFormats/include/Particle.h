#ifndef CaloCubeParticle_h
#define CaloCubeParticle_h

#include "G4ThreeVector.hh"
#include <string>
#include "Position.h"


class G4Track;

namespace CaloCube {

  class Particle {
    public:
  
    Particle(){};
    Particle(std::string name, std::string creatorProcess, double energy, G4ThreeVector momentum, G4ThreeVector pos, int x, int y, int z);

    //getters 
    std::string getName() const { return _name; }
    std::string getCreatorProcess() const { return _creatorProcess; }
    double getTotalEnergy() const { return _totalEnergy; }
    G4ThreeVector getMomentum() const { return _momentum; }
    const G4Track* getTrack() const { return _track; }	//! transient
    const G4ThreeVector& getPositionOfOrigin() const { return _pos; }
    const Position& getCrystalPosition() const { return _crystalPos; } 


    //setters
    void setTrack(const G4Track* track) { _track = track; } ; //! transient

    private:
    std::string _name;
    std::string _creatorProcess;
    double _totalEnergy;
    G4ThreeVector _momentum;
    G4ThreeVector _pos;
    Position _crystalPos;
    

    // for internal use
    const G4Track* _track;  //! transient value
    bool _collected;

    //not thate a comment starting with "//!" tells rootcint not to store that data member on file

  };

}

#endif

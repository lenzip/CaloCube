#include "Particle.h"

namespace CaloCube {

  Particle::Particle(std::string name, std::string creatorProcess, double energy, G4ThreeVector momentum, G4ThreeVector pos, int x, int y, int z):
  _name(name),
  _creatorProcess(creatorProcess),
  _totalEnergy(energy),
  _momentum(momentum),
  _pos(pos),
  _crystalPos(x,y,z),
  _track(0)
  {}
}

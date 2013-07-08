#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
#pragma link C++ namespace CaloCube;
#pragma link C++ defined_in namespace CaloCube;
#pragma link C++ class CaloCube::Particle+;
#pragma link C++ class vector<CaloCube::Particle>+;
#include "Ref.h"
#include "Crystal.h"
#include "Shower.h"
#pragma link C++ class CaloCube::Ref<CaloCube::Particle>+;
#pragma link C++ class vector<CaloCube::Ref<CaloCube::Particle> >+;
#pragma link C++ class std::pair<CaloCube::Ref<CaloCube::Particle>, double>+;
#pragma link C++ class vector<std::pair<CaloCube::Ref<CaloCube::Particle>, double> >+;
#pragma link C++ class CaloCube::Crystal+;
#pragma link C++ class std::vector<CaloCube::Crystal>+;
#pragma link C++ class CaloCube::Shower+;
#include "CLHEP/Vector/ThreeVector.h"
#pragma link C++ namespace CLHEP;
#pragma link C++ class CLHEP::Hep3Vector+;
#pragma link C++ class CaloCube::Position+;
#endif

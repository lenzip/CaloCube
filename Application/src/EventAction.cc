
#include "EventAction.h"
#include "StackingAction.h"
#include "cuboStackingAction.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"

#include "RunAction.h"
#include "SteppingAction.h"
#include "cuboSteppingAction.h"
  // use of stepping action to get and reset accumulated energy  

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "TInterpreter.h"
#include "TROOT.h"

using namespace CaloCube;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction* EventAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction* EventAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(),
  fPrintModulo(100),
  fEnergySum(0.),
  fEnergy2Sum(0.),
  _shower(0)
{
  gROOT->ProcessLine("#include <vector>");


  fOutput = new TFile("tree.root", "RECREATE"); 
  fTree = new TTree("tree", "tree");  
  fTree->Branch("nCher", &nCher);
  fTree->Branch("nScint", &nScint);
  //fTree->Branch("xstart", &xstart);
  //fTree->Branch("ystart", &ystart);
  //fTree->Branch("zstart", &zstart);
  //fTree->Branch("xend", &xend);
  //fTree->Branch("yend", &yend);
  //fTree->Branch("zend", &zend);
  fTree->Branch("totalEnergy", &totalEnergy);
  fTree->Branch("particles", &_particles);
  fTree->Branch("photonsCollected", &_photonsCollected);
  fTree->Branch("primaryTheta", &_primaryTheta);
  fTree->Branch("primaryPhi", &_primaryPhi);
  //fTree->Branch("shower", &_shower);
  fgInstance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ 
  fgInstance = 0;
  fOutput->Write();
  delete fTree;
  delete fOutput;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{  
  G4int eventNb = event->GetEventID();
  if (eventNb%fPrintModulo == 0) { 
    G4cout << "\n---> Begin of event: " << eventNb << G4endl;
  }
 
  // Reset accounted energy in stepping action
  cuboSteppingAction::Instance()->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
  G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
  _primaryTheta = primaryParticle->GetMomentum().theta();
  _primaryPhi = primaryParticle->GetMomentum().phi();

  G4RunManager* rmanager = G4RunManager::GetRunManager();
  const cuboStackingAction* sa = dynamic_cast<const cuboStackingAction*>(rmanager->GetUserStackingAction());
  // accumulate statistics
  G4double energy = 0;
  if (sa){
    nScint = sa->GetNScintPhotons(); //GetEnergy();
    nCher  = sa->GetNCherenkovPhotons();
    _particles = sa->getParticles();
  }  
  //const G4StepPoint* begin = SteppingAction::Instance()->GetStartingPoint();
  //if (begin){
  //  xstart = begin->GetPosition().x()/cm;
  //  ystart = begin->GetPosition().y()/cm;
  //  zstart = begin->GetPosition().z()/cm;
  //}  
  //const G4StepPoint* end   = SteppingAction::Instance()->GetEndingPoint();
  //if (end){
  //  xend = end->GetPosition().x()/cm;
  //  yend = end->GetPosition().y()/cm;
  //  zend = end->GetPosition().z()/cm;
  //}  
  totalEnergy = cuboSteppingAction::Instance()->GetTotalEnergy()/GeV;
  _photonsCollected = cuboSteppingAction::Instance()->getPhotonsCollected();  
  //_crystals = SteppingAction::Instance()->getCrystals();
  //Shower theshower(0, 0.15, _crystals);
  //_shower = &theshower;
  fTree->Fill();
  fEnergySum  += energy;
  fEnergy2Sum += energy*energy;
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::Reset()
{
  //reset cumulative quantities
  //
  fEnergySum = 0.;
  fEnergy2Sum = 0.;
  totalEnergy = -1.;
  nScint=-1.;
  nCher=-1.;
  xstart = -10000.;
  ystart = -10000.;
  zstart = -10000.;
  xend = -10000.;
  yend = -10000.;
  zend = -10000.;
  _particles.clear();
  _crystals.clear();	
  _shower = 0;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

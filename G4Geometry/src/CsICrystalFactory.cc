#include "CsICrystalFactory.h"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"

namespace CaloCube {
  CsICrystalFactory::CsICrystalFactory(){

    G4NistManager* nist = G4NistManager::Instance();

    const G4int nEntries = 12;
    G4int ncomponents, natoms;
    G4double a, z, density;
    G4String name, symbol;

    G4double PhotonEnergy[nEntries] =
    { 1.65*eV, 1.77*eV, 1.91*eV, 2.07*eV, 2.25*eV, 2.48*eV, 2.76*eV, 3.10*eV,
      3.54*eV, 3.87*eV, 4.13*eV, 4.28*eV};
    //{  750*nm,  700*nm,  650*nm,  600*nm,  550*nm,  500*nm,  450*nm,  400*nm,
    //   350*nm,  320*nm,  300*nm,  290*nm}

    //
    // CsI
    //            
    G4double RefractiveIndex_CsI[nEntries] =
      {   1.769,   1.773,   1.778,   1.785,   1.794,   1.806,   1.824,   1.850,
          1.894,   1.937,   1.979,   2.006 };

    G4double Absorption_CsI[nEntries] =
      {   250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm,
          250.*cm, 250.*cm, 250.*cm, 250.*cm};


    G4double ScintilFast[nEntries] =
      {   0.00,    0.18,    0.39,      0.70,    1.0,    0.75,    0.28,     0.12,
          0.00,    0.00,    0.00,    0.00 };       
    a = 132.9*g/mole;
    G4Element* elCs = new G4Element(name="Cesium"  ,symbol="Cs" , z= 55., a);
    a = 126.9*g/mole;
    G4Element* elI  = new G4Element(name="Iodio"  ,symbol="I" , z= 53., a);

    G4Material* csi = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    G4Material* tl = nist->FindOrBuildMaterial("G4_Tl");
    density = csi->GetDensity();
    _material = new G4Material(name="CsI(Tl)", density, ncomponents=2);
    _material->AddElement(elCs, natoms=1);
    _material->AddElement(elI, natoms=1);
    G4MaterialPropertiesTable* mycsitl= new G4MaterialPropertiesTable();
    //mycsitl->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,nEntries)->SetSpline(true);
    //mycsitl->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex_CsI,nEntries)->SetSpline(true);
    //mycsitl->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption_CsI,     nEntries)->SetSpline(true);
    //mycsitl->AddConstProperty("SCINTILLATIONYIELD",54000./MeV);
    //mycsitl->AddConstProperty("RESOLUTIONSCALE",1.0);       
    //mycsitl->AddConstProperty("FASTTIMECONSTANT", 1000.*ns);
    //mycsitl->AddConstProperty("YIELDRATIO",1.0);


    _material->SetMaterialPropertiesTable(mycsitl);      

    G4double shape1_dx = 3.6*cm, shape1_dy = 3.6*cm, shape1_dz = 3.6*cm;
    _shape =  new G4Box("Shape1",                     //its name
               0.5*shape1_dx, 0.5*shape1_dy, 0.5*shape1_dz);     //its size
  }
}

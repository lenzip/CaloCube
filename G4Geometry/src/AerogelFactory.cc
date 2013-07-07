#include "AerogelFactory.h"

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

namespace CaloCube {
  AerogelFactory::AerogelFactory(){
    

    G4UnitDefinition::BuildUnitsTable();
    G4String name, symbol;             // a=mass of a mole;
    G4double a, z, density;            // z=mean number of protons;  
                                     // n=nb of nucleons in an isotope;
    G4int ncomponents, natoms;
    G4double fractionmass;

    const G4int nEntries = 12;

      G4double PhotonEnergy[nEntries] =
    { 1.65*eV, 1.77*eV, 1.91*eV, 2.07*eV, 2.25*eV, 2.48*eV, 2.76*eV, 3.10*eV,
      3.54*eV, 3.87*eV, 4.13*eV, 4.28*eV};
    //{  750*nm,  700*nm,  650*nm,  600*nm,  550*nm,  500*nm,  450*nm,  400*nm,
    //   350*nm,  320*nm,  300*nm,  290*nm}

    G4double RefractiveIndex_Aerogel[nEntries] =
      {   1.02,    1.02,    1.02,    1.02,      1.02,    1.02,   1.02,    1.02,
          1.02,    1.02,    1.02,    1.02,  };

    G4double Absorption_Aerogel[nEntries] =
      {   250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm, 250.*cm,
          250.*cm, 250.*cm, 250.*cm, 250.*cm};

    a = 1.01*g/mole;
    G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
    a=28.09*g/mole;
    G4Element* elSi = new G4Element(name="Silicon", symbol="Si", z=14., a);
    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);
    a = 14.01*g/mole;
    G4Element* elN  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);
    a = 12.01*g/mole;
    G4Element* elC  = new G4Element(name="Carbon"  ,symbol="C" , z= 6., a);
    a = 132.9*g/mole;
    G4Element* elCs = new G4Element(name="Cesium"  ,symbol="Cs" , z= 55., a);
    a = 126.9*g/mole;
    G4Element* elI  = new G4Element(name="Iodio"  ,symbol="I" , z= 53., a);
    density = 2.200*g/cm3;
    G4Material* SiO2 = new G4Material(name="quartz", density, ncomponents=2);
    SiO2->AddElement(elSi, natoms=1);
    SiO2->AddElement(elO , natoms=2);
    density = 1.290*mg/cm3;
    G4Material* Air = new G4Material(name="Air  "  , density, ncomponents=2);
    Air->AddElement(elN, fractionmass=0.7);
    Air->AddElement(elO, fractionmass=0.3);
    density = 1.000*g/cm3;
    G4Material* H2O = new G4Material(name="Water", density, ncomponents=2);
    H2O->AddElement(elH, natoms=2);
    H2O->AddElement(elO, natoms=1);
    density = 0.200*g/cm3;
    _material = new G4Material(name="Aerogel", density, ncomponents=3);
    _material->AddMaterial(SiO2, fractionmass=62.5*perCent);
    _material->AddMaterial(H2O , fractionmass=37.4*perCent);
    _material->AddElement (elC , fractionmass= 0.1*perCent);
    G4MaterialPropertiesTable* myaerog= new G4MaterialPropertiesTable();
    myaerog->AddConstProperty("SCINTILLATIONYIELD",0./MeV);
    myaerog->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex_Aerogel,nEntries)
          ->SetSpline(true);
    _material->SetMaterialPropertiesTable(myaerog);

     G4double shape1_dx = 3.6*cm, shape1_dy = 3.6*cm, shape1_dz = 3.6*cm;
    _shape =  new G4Box("Shape1",                     //its name
               0.5*shape1_dx, 0.5*shape1_dy, 0.5*shape1_dz);     //its size
 

  }
}

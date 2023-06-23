/// \file DetectorConstruction.cc
/// \brief Implementation of the P1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"

#include "G4UserLimits.hh"

namespace SH
{

DetectorConstruction::DetectorConstruction()
{}


DetectorConstruction::~DetectorConstruction()
{
  // delete fStepLimit_daq;
  // delete fStepLimit_alpide;

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // Material I made ------------------------------------------
  G4double a, z, density_Acrylic, density_PLA, density_Air;
  G4String name, symbol;
  G4int nel;
  
  a = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen", symbol="H", z=1., a);
 
  a = 12.01*g/mole;
  G4Element* elC  = new G4Element(name="Carbon",   symbol="C", z=6., a);

  a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen",   symbol="O", z=8., a);
  
  a = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen",symbol="N",z= 7.,a);

  // // PMMA C5H8O2 ( Acrylic )
  // density_Acrylic = 1.19*g/cm3;
  // G4Material* Acrylic = new G4Material(name="Acrylic", density_Acrylic, nel=3);
  // Acrylic->AddElement(elC, 5);
  // Acrylic->AddElement(elH, 8);
  // Acrylic->AddElement(elO, 2);    

  // // PLA C3H4O2 ( pilament of 3D printer ) 
  // density_PLA = 1.24*g/cm3;
  // G4Material* PLA = new G4Material(name="PLA", density_PLA, nel=3);
  // PLA->AddElement(elC, 3);
  // PLA->AddElement(elH, 4);
  // PLA->AddElement(elO, 2);   

  // Air
  density_Air = 0.0012*g/cm3;
  G4Material* My_Air = new G4Material(name="My_Air",density_Air,nel=2); 
  G4double fracMass;
  My_Air->AddElement(elN, fracMass=70.0*perCent); My_Air->AddElement(elO, fracMass=30.0*perCent);

  //material
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al");  
  G4Material* Pb_mat = nist->FindOrBuildMaterial("G4_Pb");
  //G4Material* Si_mat = nist->FindOrBuildMaterial("G4_Si");
  // G4Material* Alpide_mat = nist->FindOrBuildMaterial("G4_Si");
  // G4Material* Daq_mat = nist->FindOrBuildMaterial("G4_Si");
  // G4Material* Pi_mat = nist->FindOrBuildMaterial("G4_Si");
  G4Material* Border_mat = nist->FindOrBuildMaterial("G4_AIR");
  // G4Material* Dump_mat = nist->FindOrBuildMaterial("G4_Al");
  // G4Material* Plastic_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");



  //G4Material* ShieldPl_mat = nist->FindOrBuildMaterial("G4_POLYCARBONATE");



  // Size ------------------------------------------------------------   
   //world
  G4double world_sizeXY = 4000*mm;
  G4double world_sizeZ  = 7500*mm;
  
  //target
  // G4double Alpide_sizeX = 15*mm, Alpide_sizeY= 30*mm, Alpide_sizeZ = 5*um;
  // G4double Daq_sizeX = 110*mm, Daq_sizeY= 115*mm, Daq_sizeZ = 3*mm;
  
  G4double AlBox1_sizeX = 260*mm,  AlBox1_sizeY= 150*mm, AlBox1_sizeZ = 5*mm;
  // G4double Subtract_sizeX = 17*mm, Subtract_sizeY= 32*mm, Subtract_sizeZ = 5*mm;

  // G4double ShieldPb_sizeXY = 200*mm, ShieldPb_sizeZ = 50*mm;
  // G4double ShieldAl_s_sizeXY = 100*mm, ShieldAl_s_sizeZ = 40*mm;
  // G4double ShieldAl_m_sizeXY = 110*mm,  ShieldAl_m_sizeZ = 50*mm;
  // G4double ShieldAl_l_sizeXY = 250*mm,  ShieldAl_l_sizeZ = 40*mm;
  // G4double ShieldPlas_sizeX = 200*mm, ShieldPlas_sizeY = 400*mm, ShieldPlas_sizeZ = 50*mm;
  G4double Shield1_sizeX = 100*mm, Shield1_sizeY = 200*mm, Shield1_sizeZ = 50*mm;
  G4double Shield2_sizeX = 200*mm, Shield2_sizeY = 200*mm, Shield2_sizeZ = 50*mm;
  G4double Shield3_sizeX = 200*mm, Shield3_sizeY = 200*mm, Shield3_sizeZ = 100*mm;
  // G4double Shield3_sizeX = 200*mm, Shield3_sizeY = 200*mm, Shield3_sizeZ = 50*mm;
  G4double Detector_sizeXY = 300*mm, Detector_sizeZ = 10*mm;

  // G4double Pi_sizeX = 200*mm,  Pi_sizeY = 25*mm, Pi_sizeZ = 70*mm;
  G4double Dump_sizeX = 450*mm,  Dump_sizeY = 450*mm, Dump_sizeZ = 40*mm;
  // G4double Border_sizeX = 2000*mm,  Border_sizeY = 2000*mm, Border_sizeZ = 4*mm;
  G4double Beam_sizeX = 240*mm,  Beam_sizeY = 240*mm, Beam_sizeZ = 10*mm;

  //G4double ShieldPl_sizeX = 100*mm,  ShieldPl_sizeY = 3*mm, ShieldPl_sizeZ = 70*mm;



  
  //Position ------------------------------------------------------------    
  // auto Alpide_pos =G4ThreeVector(0, 0, 1950*mm);
  // auto Daq_pos =G4ThreeVector(90*mm, 0, 1951.5*mm);
  auto AlBox1_pos =G4ThreeVector(-208*mm, -24*mm, 1880*mm);
  // auto Border_pos =G4ThreeVector(0, 0, 1945*mm);
  auto Beam_pos =G4ThreeVector(0, 0, 0*mm);


  // auto Pb_pos =G4ThreeVector(121.25*mm, 25*mm, 847*mm);
  // auto Al_s_pos =G4ThreeVector(121.25*mm, 85*mm, 1791.9*mm);
  // auto Al_m_pos =G4ThreeVector(121.25*mm, -20*mm, 1796.9*mm);
  // auto Al_l_pos =G4ThreeVector(142*mm, 50*mm, 751.8*mm);
  //auto Shield_pos=G4ThreeVector(121.25*mm, 25*mm, 1847*mm); ----------original position
  // auto Shield_pos=G4ThreeVector(70*mm, 25*mm, 1847*mm);
auto Shield1_pos=G4ThreeVector(-80*mm, -24*mm, 1547*mm);
auto Shield_pos_di=G4ThreeVector(0*mm, -24*mm, 1897.5*mm);
auto Shield2_pos=G4ThreeVector(-105*mm, -24*mm, 1800*mm);
auto Shield21_pos=G4ThreeVector(-105*mm, -24*mm, 1901*mm);
auto Shield3_pos=G4ThreeVector(-160*mm, -24*mm, 1724*mm);
auto Shield4_pos=G4ThreeVector(-160*mm, -24*mm, 1673*mm);
auto Shield5_pos=G4ThreeVector(-160*mm, -24*mm, 1622*mm);
auto Shield6_pos=G4ThreeVector(-156*mm, -24*mm, 1800*mm);
auto Shield61_pos=G4ThreeVector(-156*mm, -24*mm, 1901*mm);

auto Shield7_pos=G4ThreeVector(-236*mm, -24*mm, 1649*mm);

auto Nebu_shield_pos=G4ThreeVector(140*mm, -24*mm, 1815*mm);
// auto Det1_pos=G4ThreeVector(0*mm, 0*mm, 2067*mm);
auto Det2_pos=G4ThreeVector(-236*mm, -24*mm, 1900*mm);
// auto Det3_pos=G4ThreeVector(-220*mm, 0*mm, 1847*mm);
// auto Det4_pos=G4ThreeVector(0*mm, 220*mm, 1847*mm);
// auto Det5_pos=G4ThreeVector(0*mm, -220*mm, 1847*mm);

  //new position
// auto Pb_pos =G4ThreeVector(121.25*mm, 25*mm, 1746.8*mm);
// auto Al_l_pos =G4ThreeVector(142*mm, 50*mm, 1842*mm);


  // auto Pi_pos =G4ThreeVector(-400*mm, -900*mm, 1985*mm);
  auto Dump_pos =G4ThreeVector(0, 0, 3500*mm);
  // auto Plas_pos =G4ThreeVector(-400, -750, 2145*mm);
  // auto Pi2_pos =G4ThreeVector(-600*mm, -900*mm, 950*mm);
  // auto Pi1_top_pos =G4ThreeVector(-400*mm, -887.5*mm, 950*mm);
  // auto Pi2_top_pos =G4ThreeVector(-600*mm, -887.5*mm, 950*mm);
  //auto ShieldPl_pos =G4ThreeVector(*mm, *mm, *mm);


  //Construct ------------------------------------------------------------   
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //World
  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =                                                                   //Define logical volume - world
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
  
  G4VPhysicalVolume* physWorld =                                                                  //Define physical volume (place logic in big volume) - world
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  // // Alpide
  // //
  // G4Box* solidAlpide =
  //   new G4Box("Alpide",                    //its name                                           
  //       0.5*Alpide_sizeX, 0.5*Alpide_sizeY, 0.5*Alpide_sizeZ); //its size

  // G4LogicalVolume* logicAlpide =
  //   new G4LogicalVolume(solidAlpide,            //its solid
  //                       Alpide_mat,             //its material                                       
  //                       "Alpide");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Alpide_pos,                //position
  //                   logicAlpide,                //its logical volume
  //                   "Alipde",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   1,                       //copy number
  //                   checkOverlaps);          //overlaps checking



  // // DAQ
  
  // G4Box* solidDaq =
  //   new G4Box("DAQ",                    //its name                                           
  //       0.5*Daq_sizeX, 0.5*Daq_sizeY, 0.5*Daq_sizeZ); //its size

  // G4LogicalVolume* logicDaq =
  //   new G4LogicalVolume(solidDaq,            //its solid
  //                       Daq_mat,             //its material                                       
  //                       "DAQ");              //its name

   
  //   new G4PVPlacement(0,                       //no rotation
  //                   Daq_pos,                //position
  //                   logicDaq,                //its logical volume
  //                   "DAQ",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   2,                       //copy number
  //                   checkOverlaps);          //overlaps checking

  // Shield
  
  G4Box* solidShield =
    new G4Box("Shield",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield =
    new G4LogicalVolume(solidShield,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield");              //its name

  
    new G4PVPlacement(0,                       //no rotation
                    Shield1_pos,                //position
                    logicShield,                //its logical volume
                    "Shield_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    33,                       //copy number
                    checkOverlaps);          //overlaps checking

    // Double Shield
    // G4LogicalVolume* logicShield_di =
    // new G4LogicalVolume(solidShield,            //its solid
    //                     Pb_mat,             //its material                                       
    //                     "Pb_Shield_di");              //its name

    // new G4PVPlacement(0,                       //no rotation
    //                 Shield_pos_di,                //position
    //                 logicShield_di,                //its logical volume
    //                 "Shield_Pb_di",              //its name                                           
    //                 logicWorld,              //its mother  volume
    //                 false,                   //no boolean operation
    //                 32,                       //copy number
    //                 checkOverlaps);          //overlaps checking


  // // New Shield
    G4RotationMatrix* rot1 = new G4RotationMatrix();
  rot1->rotateY(90.0 * deg);

  G4Box* solidShield2 =
    new G4Box("Shield2",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield2 =
    new G4LogicalVolume(solidShield2,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_2");              //its name

  
    new G4PVPlacement(rot1,                       //no rotation
                    Shield2_pos,                //position
                    logicShield2,                //its logical volume
                    "Shield2_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    34,                       //copy number
                    checkOverlaps);          //overlaps checking
 // // New Shield
  G4Box* solidShield21 =
    new G4Box("Shield21",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield21 =
    new G4LogicalVolume(solidShield21,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_21");              //its name

  
    new G4PVPlacement(rot1,                       //no rotation
                    Shield21_pos,                //position
                    logicShield21,                //its logical volume
                    "Shield21_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    41,                       //copy number
                    checkOverlaps);          //overlaps checking
  // // New Shield2
  G4Box* solidShield3 =
    new G4Box("Shield3",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield3 =
    new G4LogicalVolume(solidShield3,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_3");              //its name

  
    new G4PVPlacement(0,                       //no rotation
                    Shield3_pos,                //position
                    logicShield3,                //its logical volume
                    "Shield3_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    35,                       //copy number
                    checkOverlaps);          //overlaps checking

    // // New Shield3
  G4Box* solidShield4 =
    new G4Box("Shield4",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield4 =
    new G4LogicalVolume(solidShield4,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_4");              //its name

  
    new G4PVPlacement(0,                       //no rotation
                    Shield4_pos,                //position
                    logicShield4,                //its logical volume
                    "Shield4_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    36,                       //copy number
                    checkOverlaps);          //overlaps checking


    // // New Shield4
  G4Box* solidShield5 =
    new G4Box("Shield5",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield5 =
    new G4LogicalVolume(solidShield5,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_5");              //its name

  
    new G4PVPlacement(0,                       //no rotation
                    Shield5_pos,                //position
                    logicShield5,                //its logical volume
                    "Shield5_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    37,                       //copy number
                    checkOverlaps);          //overlaps checking

    // // New Shield5
  G4Box* solidShield6 =
    new G4Box("Shield6",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield6 =
    new G4LogicalVolume(solidShield6,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_6");              //its name

  
    new G4PVPlacement(rot1,                       //no rotation
                    Shield6_pos,                //position
                    logicShield6,                //its logical volume
                    "Shield6_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    38,                       //copy number
                    checkOverlaps);          //overlaps checking
    // // New Shield5
  G4Box* solidShield61 =
    new G4Box("Shield61",                    //its name                                           
        0.5*Shield1_sizeX, 0.5*Shield1_sizeY, 0.5*Shield1_sizeZ); //its size

  G4LogicalVolume* logicShield61 =
    new G4LogicalVolume(solidShield61,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_61");              //its name

  
    new G4PVPlacement(rot1,                       //no rotation
                    Shield61_pos,                //position
                    logicShield61,                //its logical volume
                    "Shield61_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    42,                       //copy number
                    checkOverlaps);          //overlaps checking

    // // Nebula shield
  G4Box* solidShieldn =
    new G4Box("Shieldn",                    //its name                                           
        0.5*Shield3_sizeX, 0.5*Shield3_sizeY, 0.5*Shield3_sizeZ); //its size

  G4LogicalVolume* logicShieldn =
    new G4LogicalVolume(solidShieldn,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_n");              //its name

  
    new G4PVPlacement(0,                       //no rotation
                    Nebu_shield_pos,                //position
                    logicShieldn,                //its logical volume
                    "Shieldn_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    39,                       //copy number
                    checkOverlaps);          //overlaps checking
    // New Shield6
  G4Box* solidShield7 =
    new G4Box("Shield7",                    //its name                                           
        0.5*Shield2_sizeX, 0.5*Shield2_sizeY, 0.5*Shield2_sizeZ); //its size

  G4LogicalVolume* logicShield7 =
    new G4LogicalVolume(solidShield7,            //its solid
                        Pb_mat,             //its material                                       
                        "Pb_Shield_7");              //its name

  
    new G4PVPlacement(rot1,                       //no rotation
                    Shield7_pos,                //position
                    logicShield7,                //its logical volume
                    "Shield7_Pb",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    40,                       //copy number
                    checkOverlaps);          //overlaps checking
  // Detector1
  
  G4Box* solidDetector =
    new G4Box("Detector2",                    //its name                                           
        0.5*Detector_sizeXY, 0.5*Detector_sizeXY, 0.5*Detector_sizeZ); //its size

  G4LogicalVolume* logicDetector =
    new G4LogicalVolume(solidDetector,            //its solid
                        Si_mat,             //its material
                        "Detector2");              //its name

  
    // new G4PVPlacement(0,                       //no rotation
    //                 Det1_pos,                //position
    //                 logicDetector,                //its logical volume
    //                 "Detector1",              //its name                                           
    //                 logicWorld,              //its mother  volume
    //                 false,                   //no boolean operation
    //                 1,                       //copy number
    //                 checkOverlaps);          //overlaps checking

    // Detector2

    new G4PVPlacement(rot1,                       //no rotation
                    Det2_pos,                //position
                    logicDetector,                //its logical volume
                    "Detector2",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    2,                       //copy number
                    checkOverlaps);          //overlaps checking
  
// // Detector3

//     new G4PVPlacement(rot1,                       //no rotation
//                     Det3_pos,                //position
//                     logicDetector,                //its logical volume
//                     "Detector3",              //its name                                           
//                     logicWorld,              //its mother  volume
//                     false,                   //no boolean operation
//                     3,                       //copy number
//                     checkOverlaps);          //overlaps checking

// // Detector4
//   G4RotationMatrix* rot2 = new G4RotationMatrix();
//   rot2->rotateX(90.0 * deg);
//     new G4PVPlacement(rot2,                       //no rotation
//                     Det4_pos,                //position
//                     logicDetector,                //its logical volume
//                     "Detector4",              //its name                                           
//                     logicWorld,              //its mother  volume
//                     false,                   //no boolean operation
//                     4,                       //copy number
//                     checkOverlaps);          //overlaps checking
  
// // Detecto5

//     new G4PVPlacement(rot2,                       //no rotation
//                     Det5_pos,                //position
//                     logicDetector,                //its logical volume
//                     "Detector5",              //its name                                           
//                     logicWorld,              //its mother  volume
//                     false,                   //no boolean operation
//                     5,                       //copy number
//                     checkOverlaps);          //overlaps checking
   // Border
  
  // G4Box* solidBorder =
  //   new G4Box("Border",                    //its name                                           
  //       0.5*Border_sizeX, 0.5*Border_sizeY, 0.5*Border_sizeZ); //its size

  // G4LogicalVolume* logicBorder =
  //   new G4LogicalVolume(solidBorder,            //its solid
  //                       Border_mat,             //its material                                       
  //                       "Border");              //its name

   
  //   new G4PVPlacement(0,                       //no rotation
  //                   Border_pos,                //position
  //                   logicBorder,                //its logical volume
  //                   "Border",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   4,                       //copy number
  //                   checkOverlaps);          //overlaps checking
   // Beam
  
  // G4Box* solidBeam =
  //   new G4Box("Beam",                    //its name                                           
  //       0.5*Beam_sizeX, 0.5*Beam_sizeY, 0.5*Beam_sizeZ); //its size

  // G4LogicalVolume* logicBeam =
  //   new G4LogicalVolume(solidBeam,            //its solid
  //                       Border_mat,             //its material                                       
  //                       "Beam");              //its name

   
  //   new G4PVPlacement(0,                       //no rotation
  //                   Beam_pos,                //position
  //                   logicBeam,                //its logical volume
  //                   "Beam",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   5,                       //copy number
  //                   checkOverlaps);          //overlaps checking

   //Beam dump
  
  G4Box* solidDump =
    new G4Box("Dump",                    //its name                                           
        0.5*Dump_sizeX, 0.5*Dump_sizeY, 0.5*Dump_sizeZ); //its size

  G4LogicalVolume* logicDump =
    new G4LogicalVolume(solidDump,            //its solid
                        Al_mat,             //its material                                       
                        "Dump");              //its name

   
    new G4PVPlacement(0,                       //no rotation
                    Dump_pos,                //position
                    logicDump,                //its logical volume
                    "Dump",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    6,                       //copy number
                    checkOverlaps);          //overlaps checking

 // AlBox
  

  G4Box* solidAlBox1 =
    new G4Box("AlBox1",                                          
        0.5*AlBox1_sizeX, 0.5*AlBox1_sizeY, 0.5*AlBox1_sizeZ); 


  // G4Box* solidSubtract =
  //   new G4Box("Sub",                                                            
  //   0.5*Subtract_sizeX, 0.5*Subtract_sizeY, 0.5*Subtract_sizeZ); 


  // G4VSolid* solidAlBoxSub= 
  //   new G4SubtractionSolid("AlBoxSub", 
  //                         solidAlBox1, 
  //                         solidSubtract,
  //                         0, 
  //                         G4ThreeVector(-57*mm,0*mm,0));

  G4LogicalVolume* logicAlBox1 =
    new G4LogicalVolume(solidAlBox1,            //its solid
                        Al_mat,             //its material                                       
                        "AlBox1");              //its name

  new G4PVPlacement(rot1,                       //no rotation
                    AlBox1_pos,                //position
                    logicAlBox1,                //its logical volume
                    "AlBox1",              //its name                                           
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    100,                       //copy number
                    checkOverlaps);          //overlaps checking
  


  // Pb
  
  // G4Box* solidShieldPb =
  //   new G4Box("ShieldPb",                    //its name                                           
  //       0.5*ShieldPb_sizeXY, 0.5*ShieldPb_sizeXY, 0.5*ShieldPb_sizeZ); //its size

  // G4LogicalVolume* logicShieldPb =
  //   new G4LogicalVolume(solidShieldPb,            //its solid
  //                       Pb_mat,             //its material                                       
  //                       "ShieldPb");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Pb_pos,                //position
  //                   logicShieldPb,                //its logical volume
  //                   "ShieldPb",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   7,                       //copy number
  //                   checkOverlaps);          //overlaps checking


  // // Al_s
  // //
  // G4Box* solidShieldAl_s =
  //   new G4Box("ShieldAl_s",                    //its name                                           
  //       0.5*ShieldAl_s_sizeXY, 0.5*ShieldAl_s_sizeXY, 0.5*ShieldAl_s_sizeZ); //its size

  // G4LogicalVolume* logicShieldAl_s =
  //   new G4LogicalVolume(solidShieldAl_s,            //its solid
  //                       Al_mat,             //its material                                       
  //                       "ShieldAl_s");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Al_s_pos,                //position
  //                   logicShieldAl_s,                //its logical volume
  //                   "ShieldAl_s",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   8,                       //copy number
  //                   checkOverlaps);          //overlaps checking
  // // Al_m
  // //
  // G4Box* solidShieldAl_m =
  //   new G4Box("ShieldAl_m",                    //its name                                           
  //       0.5*ShieldAl_m_sizeXY, 0.5*ShieldAl_m_sizeXY, 0.5*ShieldAl_m_sizeZ); //its size

  // G4LogicalVolume* logicShieldAl_m =
  //   new G4LogicalVolume(solidShieldAl_m,            //its solid
  //                       Al_mat,             //its material                                       
  //                       "ShieldAl_m");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Al_m_pos,                //position
  //                   logicShieldAl_m,                //its logical volume
  //                   "ShieldAl_m",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   9,                       //copy number
  //                   checkOverlaps);          //overlaps checking
  // // Al_l
  // //
  // G4Box* solidShieldAl_l =
  //   new G4Box("ShieldAl_l",                    //its name                                           
  //       0.5*ShieldAl_l_sizeXY, 0.5*ShieldAl_l_sizeXY, 0.5*ShieldAl_l_sizeZ); //its size

  // G4LogicalVolume* logicShieldAl_l =
  //   new G4LogicalVolume(solidShieldAl_l,            //its solid
  //                       Al_mat,             //its material                                       
  //                       "ShieldAl_l");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Al_l_pos,                //position
  //                   logicShieldAl_l,                //its logical volume
  //                   "Shield_Al_l",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   10,                       //copy number
  //                   checkOverlaps);          //overlaps checking

  //Plastic shield
  
  // G4Box* solidPlas =
  //   new G4Box("Plas",                    //its name                                           
  //       0.5*ShieldPlas_sizeX, 0.5*ShieldPlas_sizeY, 0.5*ShieldPlas_sizeZ); //its size


  // G4LogicalVolume* logicPlas =
  //   new G4LogicalVolume(solidPlas,            //its solid
  //                       Plastic_mat,             //its material                                       
  //                       "Plas");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Plas_pos,                //position
  //                   logicPlas,                //its logical volume
  //                   "Plas",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   11,                       //copy number
  //                   checkOverlaps);          //overlaps checking


  // PI
  
  // G4Box* solidPi =
  //   new G4Box("Pi",                    //its name                                           
  //       0.5*Pi_sizeX, 0.5*Pi_sizeY, 0.5*Pi_sizeZ); //its size

  // // G4Box* solidPi_top =
  // //   new G4Box("Pi_top",                    //its name                                           
  // //       0.5*Pi_top_sizeX, 0.5*Pi_top_sizeY, 0.5*Pi_top_sizeZ); //its size

  // G4LogicalVolume* logicPi =
  //   new G4LogicalVolume(solidPi,            //its solid
  //                       Pi_mat,             //its material                                       
  //                       "Pi");              //its name

  
  //   new G4PVPlacement(0,                       //no rotation
  //                   Pi_pos,                //position
  //                   logicPi,                //its logical volume
  //                   "Pi",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   3,                       //copy number
  //                   checkOverlaps);          //overlaps checking

  //   new G4PVPlacement(0,                       //no rotation
  //                   Pi1_top_pos,                //position
  //                   logicPi_top,                //its logical volume
  //                   "Pi1_top",              //its name                                           
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   9,                       //copy number
  //                   checkOverlaps);          //overlaps checking

  // new G4PVPlacement(0,                       //no rotation
  //                     Pi2_pos,                //position
  //                     logicPi,                //its logical volume
  //                     "Pi2",              //its name                                           
  //                     logicWorld,              //its mother  volume
  //                     false,                   //no boolean operation
  //                     10,                       //copy number
  //                     checkOverlaps);          //overlaps checking

  // new G4PVPlacement(0,                       //no rotation
  //                     Pi2_top_pos,                //position
  //                     logicPi_top,                //its logical volume
  //                     "Pi2_top",              //its name                                           
  //                     logicWorld,              //its mother  volume
  //                     false,                   //no boolean operation
  //                     11    ,                   //copy number
  //                     checkOverlaps);          //overlaps checking                    


  // G4double maxStep_alpide = 20*um;
  // fStepLimit_alpide = new G4UserLimits(maxStep_alpide);
  // logicAlpide->SetUserLimits(fStepLimit_alpide);

  // G4double maxStep_daq = 1*mm;
  // fStepLimit_daq = new G4UserLimits(maxStep_daq);
  // logicDaq->SetUserLimits(fStepLimit_daq);


  

  return physWorld;
}

}

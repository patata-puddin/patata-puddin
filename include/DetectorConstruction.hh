/// \file DetectorConstruction.hh

#ifndef P1DetectorConstruction_h
#define P1DetectorConstruction_h 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4UserLimits;

/// Detector construction class to define materials and geometry.

namespace SH
{

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    // get methods
    //
    //const G4VPhysicalVolume* GetAlpidePV() const;
    // void SetMaxStep_daq (G4double );
    // void SetMaxStep_alpide (G4double );
   
  private:
    

    //G4VPhysicalVolume* fAlpidePV = nullptr; 
    // G4UserLimits* fStepLimit_daq = nullptr;
    // G4UserLimits* fStepLimit_alpide = nullptr;
};

// inline const G4VPhysicalVolume* DetectorConstruction::GetAlpidePV() const {
//   return fAlpidePV;
// }
}


#endif


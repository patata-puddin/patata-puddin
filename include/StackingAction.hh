/// \file P1b/include/StackingAction.hh
//
//

#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4Step.hh"
#include "globals.hh"

namespace SH
{
class DetectorConstruction;
class SteppingAction;

class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction(const DetectorConstruction* detConstruction);
   ~StackingAction();
     
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    
    private:
  const DetectorConstruction* fDetConstruction = nullptr;
 
};
}


#endif
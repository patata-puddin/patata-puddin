/// \file SteppingAction.hh

#ifndef P1SteppingAction_h
#define P1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"


/// Stepping action class
///

namespace SH

{
class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(const DetectorConstruction* detConstruction
                 );
    ~SteppingAction() override;

    // method from the base class
    void UserSteppingAction(const G4Step* step) override;

  private:
  const DetectorConstruction* fDetConstruction = nullptr;
    // EventAction* fEventAction = nullptr;
    
};

}

#endif

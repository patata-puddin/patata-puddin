/// \file ActionInitialization.cc

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "StackingAction.hh"
#include "TrackingAction.hh"

namespace SH
{


ActionInitialization::ActionInitialization
                            (DetectorConstruction* detConstruction)
 : fDetConstruction(detConstruction)
{}



ActionInitialization::~ActionInitialization()
{}


void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}


void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new RunAction);
  auto eventAction = new EventAction;
  SetUserAction(eventAction);
  SetUserAction(new SteppingAction(fDetConstruction));
  SetUserAction(new StackingAction(fDetConstruction));
  SetUserAction(new TrackingAction());

}


}
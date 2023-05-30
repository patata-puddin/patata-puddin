/// \file RunAction.hh

#ifndef P1RunAction_h
#define P1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

namespace SH
{
class PrimaryGeneratorAction;
//class HistoManager;
class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;
  
  private:
    //HistoManager*           fHistoManager;
  
};

}

#endif

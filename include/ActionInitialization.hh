/// \file ActionInitialization.hh

#ifndef P1ActionInitialization_h
#define P1ActionInitialization_h 

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

namespace SH
{
class DetectorConstruction;
class ActionInitialization : public G4VUserActionInitialization

{
  public:
    ActionInitialization(SH::DetectorConstruction*);
    ~ActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;

  private:
    DetectorConstruction* fDetConstruction = nullptr;
    

};

}



#endif

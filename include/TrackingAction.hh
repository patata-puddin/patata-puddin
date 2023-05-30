/// \file TrackingAction.hh
/// \brief Definition of the TrackingAction class

#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

namespace SH
{
class TrackingMessenger;

class TrackingAction : public G4UserTrackingAction {

  public:  
    TrackingAction();
   ~TrackingAction() override;
   
    void  PreUserTrackingAction(const G4Track*) override;  
    void PostUserTrackingAction(const G4Track*) override;
    //void ParticleInfo(G4double trackID, G4double partPDG);
    
    // void SetParticleCount(G4bool flag) { fParticleCount = flag;};
    
  private:
    //G4bool fParticleCount;    
};

// inline void TrackingAction::ParticleInfo(G4double trackID, G4double partPDG) {
//   auto analysisManager = G4AnalysisManager::Instance();

//   analysisManager->FillNtupleDColumn(0, 0, trackID);
//   analysisManager->FillNtupleDColumn(0, 1, partPDG);
//   analysisManager->AddNtupleRow(0);
// }
}
#endif
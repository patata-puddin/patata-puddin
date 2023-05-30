/// \file EventAction.hh

#ifndef P1EventAction_h
#define P1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"


/// Event action class
///

namespace SH
{

class RunAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddTar(G4double de, G4double dl);
    //void AddTarElectron(G4double Electronde, G4double Electrondl);
    void AddTarProton(G4double Protonde, G4double Protondl);
    void AddTarGamma(G4double Gammade, G4double Gammadl);
    // void ParticleInfo(G4double trackID, G4double partPDG);


  private:
    G4double  fEnergy = 0.;
    G4double  fTrackL = 0.;

    // G4double  fElectronEnergy = 0.;
    // G4double  fElectronTrackL = 0.;

    G4double  fProtonEnergy = 0.;
    G4double  fProtonTrackL = 0.;

    G4double  fGammaEnergy = 0.;
    G4double  fGammaTrackL = 0.;

    G4String PartName;
    //G4int PartTrackID;
    //G4int electN=0.;



};
// inline void EventAction::AddTar(G4double de, G4double dl) {
//   fEnergy += de;
//   fTrackL += dl;
// }

// inline void EventAction::AddTarElectron(G4double Electronde, G4double Electrondl) {
//   fElectronEnergy += Electronde;
//   fElectronTrackL += Electrondl;
// }

// inline void EventAction::AddTarProton(G4double Protonde, G4double Protondl) {
//   fProtonEnergy += Protonde;
//   fProtonTrackL += Protondl;
// }

// inline void EventAction::AddTarGamma(G4double Gammade, G4double Gammadl) {
//   fGammaEnergy += Gammade;
//   fGammaTrackL += Gammadl;
// }


// inline void EventAction::ParticleInfo(G4double trackID, G4double partPDG) {
//   auto analysisManager = G4AnalysisManager::Instance();

//   analysisManager->FillNtupleDColumn(0, 0, trackID);
//   analysisManager->FillNtupleDColumn(0, 1, partPDG);
//   analysisManager->AddNtupleRow(0);
// }
}

#endif
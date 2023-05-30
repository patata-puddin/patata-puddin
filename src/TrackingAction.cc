/// \file TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//


#include "TrackingAction.hh"

// #include "Run.hh"
// #include "HistoManager.hh"
// #include "TrackingMessenger.hh"

#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4RunManager.hh"

namespace SH
{
TrackingAction::TrackingAction()
:G4UserTrackingAction()
{
}


TrackingAction::~TrackingAction()
{
}


void TrackingAction::PreUserTrackingAction(const G4Track* track)
{  
  auto analysisManager = G4AnalysisManager::Instance();

    
  auto PartPDG = track->GetParticleDefinition()->GetPDGEncoding();
  // auto PartID= track->GetTrackID();
  auto PartName = track->GetParticleDefinition()->GetParticleName();
  auto vp_vol = track->GetLogicalVolumeAtVertex()->GetName();
  auto vp_KE=track->GetVertexKineticEnergy();
  auto vp_mom = track->GetVertexMomentumDirection();
  auto vp_pos = track->GetVertexPosition();

// //sheild 에서 만들어진 것
// if(vp_vol=="Pb_Shield"){
//   auto vp_proc=track->GetCreatorProcess()->GetProcessName();
//   analysisManager->FillNtupleSColumn(5, 0, PartName);
//   analysisManager->FillNtupleSColumn(5, 1, vp_proc);
//   analysisManager->FillNtupleDColumn(5, 2, vp_KE);
//       analysisManager->AddNtupleRow(5);

// }


// if(vp_vol=="Pb_Shield" && PartPDG == 22){
//   auto vp_proc=track->GetCreatorProcess()->GetProcessName();
//   analysisManager->FillNtupleSColumn(6, 0, vp_proc);
//   analysisManager->FillNtupleDColumn(6, 1, vp_KE);
//   analysisManager->FillNtupleDColumn(6, 2, vp_mom[0]);
//   analysisManager->FillNtupleDColumn(6, 3, vp_mom[1]);
//   analysisManager->FillNtupleDColumn(6, 4, vp_mom[2]);
//   analysisManager->FillNtupleDColumn(6, 5, vp_pos[0]);
//   analysisManager->FillNtupleDColumn(6, 6, vp_pos[1]);
//   analysisManager->FillNtupleDColumn(6, 7, vp_pos[2]);
//   analysisManager->AddNtupleRow(6);

// }

// if(vp_vol=="Pb_Shield"&& PartPDG == 2112){
//   auto vp_proc=track->GetCreatorProcess()->GetProcessName();
//   analysisManager->FillNtupleSColumn(7, 0, vp_proc);
//   analysisManager->FillNtupleDColumn(7, 1, vp_KE);
//   analysisManager->FillNtupleDColumn(7, 2, vp_mom[0]);
//   analysisManager->FillNtupleDColumn(7, 3, vp_mom[1]);
//   analysisManager->FillNtupleDColumn(7, 4, vp_mom[2]);
//   analysisManager->FillNtupleDColumn(7, 5, vp_pos[0]);
//   analysisManager->FillNtupleDColumn(7, 6, vp_pos[1]);
//   analysisManager->FillNtupleDColumn(7, 7, vp_pos[2]);
//   analysisManager->AddNtupleRow(7);

// }


//   G4int iabs        = track->GetTouchableHandle()->GetCopyNumber();
//   G4String name     = track->GetDefinition()->GetParticleName();
//   G4double meanLife = track->GetDefinition()->GetPDGLifeTime();  
//   G4double energy   = track->GetKineticEnergy();

}


void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
//   // get Run
//   Run* run 
//     = static_cast<Run*>(
//         G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  
  // where are we ?
  // G4StepStatus status = track->GetStep()->GetPostStepPoint()->GetStepStatus();

  //   const G4ParticleDefinition* particle = track->GetParticleDefinition();
  // G4String name     = particle->GetParticleName();
  // G4double meanLife = particle->GetPDGLifeTime();  
  // G4double energy   = track->GetKineticEnergy();

  // G4cout << name << "  Please  " << energy << G4endl;
  //status of primary particle : absorbed, transmited, reflected ?
//   if (track->GetTrackID() == 1) {
//     G4int flag = 0;
//     if (status == fWorldBoundary) {
//       if (track->GetMomentumDirection().x() > 0.) flag = 1;
//       else                                        flag = 2;
//     }
//     // run->AddTrackStatus(flag);
//   }
  
//   // keep only emerging particles
//   if (status != fWorldBoundary) return;

//   // count particles

  //run->ParticleCount(0,name,energy,meanLife);

 ////G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
}
}

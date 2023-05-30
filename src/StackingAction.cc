// \file electromagnetic/TestEm1/src/StackingAction.cc
/// \brief Implementation of the StackingAction class

#include "StackingAction.hh"
//#include "HistoManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "DetectorConstruction.hh"
#include "G4VProcess.hh"
#include "G4Step.hh"


namespace SH
{
  
StackingAction::StackingAction(const DetectorConstruction* detConstruction)
 : G4UserStackingAction(), fDetConstruction(detConstruction)
{ }


StackingAction::~StackingAction()
{ }


G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{  
  //keep primary particle
  // if (track->GetParentID() == 0) return fUrgent;

  //
  //energy spectrum of secondaries
  
  // auto prevolume = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  // auto postvolume = step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();




  // if(postvolume==33 && prevolume==0){
  // analysisManager->FillNtupleDColumn(14, 1, PartPDG);
  // analysisManager->FillNtupleDColumn(14, 0, TrackId);
  // analysisManager->FillNtupleSColumn(14, 2, PartName);
  // analysisManager->AddNtupleRow(14);
  // }

// analysisManager->FillNtupleDColumn(14, 1, PartPDG);
//   analysisManager->FillNtupleDColumn(14, 0, TrackId);
//   analysisManager->FillNtupleSColumn(14, 2, PartName);
//   analysisManager->AddNtupleRow(14);
  // analysisManager->FillH1(6,energy);

//   if( (PartPDG == 2212) && (TrackId > 1)){
//         auto creatproc=track->GetCreatorProcess();
//         auto VpProcess = creatproc->GetProcessName();

//         analysisManager->FillNtupleSColumn(6, 0, VpProcess);
//         // auto vertexpoint_vol = step -> GetTrack()->GetLogicalVolumeAtVertex()->GetName();

      
//         // analysisManager->FillNtupleSColumn(6, 5, vertexpoint_vol);

//    analysisManager->AddNtupleRow(6);
// }

// if(PartPDG == 22){
//       // if (step->GetPreStepPoint()->GetProcessDefinedStep()){
//         // track->GetCreatorProcess()
//         auto creatproc=track->GetCreatorProcess();
//         auto VpProcess = creatproc->GetProcessName();
//         analysisManager->FillNtupleSColumn(7, 0, VpProcess);
      
//         auto vertexpoint_x = track->GetVertexPosition().x();
//         auto vertexpoint_y = track->GetVertexPosition().y();
//         auto vertexpoint_z = track->GetVertexPosition().z();
//         auto vertexpoint_KE = track->GetVertexKineticEnergy();
//         // auto vertexpoint_vol = track->GetLogicalVolumeAtVertex()->GetName();
//         analysisManager->FillNtupleDColumn(7, 1, vertexpoint_x);
//         analysisManager->FillNtupleDColumn(7, 2, vertexpoint_y);
//         analysisManager->FillNtupleDColumn(7, 3, vertexpoint_z);
//         analysisManager->FillNtupleDColumn(7, 4, vertexpoint_KE);
//         //analysisManager->FillNtupleSColumn(7, 5, vertexpoint_vol);
//         analysisManager->AddNtupleRow(7);
 return fUrgent;
}

  //inside material
//   auto Partposition = track->GetVolume();
  
//   if ( Partposition == fDetConstruction->GetTargetPV() ) {
// G4cout << "Hanyi" << Partposition << G4endl;
//   }
 
}

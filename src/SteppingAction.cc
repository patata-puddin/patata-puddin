/// \file SteppingAction.cc
/// \brief Implementation of the P1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include <iostream>


using namespace std;
namespace SH
{


SteppingAction::SteppingAction(const DetectorConstruction* detConstruction
                               )
  : fDetConstruction(detConstruction)


{}

SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  //get info
  auto prevolume = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  auto postvolume=step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
  auto PartKE = step -> GetPostStepPoint()->GetKineticEnergy();
  auto PartName = step->GetTrack()->GetDefinition()->GetParticleName();
  auto PartPDG = step->GetTrack()->GetDefinition()->GetPDGEncoding();  
  auto PartPosx =  step->GetPostStepPoint()->GetPosition().x();
  auto PartPosy = step->GetPostStepPoint()->GetPosition().y();
  auto PartPosz = step->GetPostStepPoint()->GetPosition().z();
  auto momdirec = step->GetTrack()->GetMomentumDirection();
  auto tracklength = step->GetTrack()->GetTrackLength();
  auto vp_vol = step -> GetTrack()->GetLogicalVolumeAtVertex()->GetName();
  auto vp_pos = step->GetTrack()->GetVertexPosition();

  auto analysisManager = G4AnalysisManager::Instance();

//Particle "entering" SHIELD----------------------
   if(  postvolume== 33 && prevolume == 0 ){

      analysisManager->FillNtupleDColumn(0, 0, PartPDG);
      analysisManager->FillNtupleSColumn(0, 1, PartName);
      analysisManager->FillNtupleSColumn(0, 2, vp_vol);
      analysisManager->FillNtupleDColumn(0, 3, PartKE);
      analysisManager->FillNtupleDColumn(0, 4, PartPosx);
      analysisManager->FillNtupleDColumn(0, 5, PartPosy);
      analysisManager->FillNtupleDColumn(0, 6, PartPosz);
          analysisManager->AddNtupleRow(0);
    }

// //Particle "exiting" SHIELD----------------------For All
//    if(  postvolume== 0 && prevolume == 33 ){

//       analysisManager->FillNtupleDColumn(1, 0, PartPDG);
//       analysisManager->FillNtupleSColumn(1, 1, PartName);
//       analysisManager->FillNtupleDColumn(1, 2, PartKE);

//           analysisManager->AddNtupleRow(1);
//     }

// //Particle "exiting" SHIELD----------------------For proton 
//    if(  (postvolume== 0 && prevolume == 33 )&& (PartPDG ==2212) ){

//       analysisManager->FillNtupleSColumn(2, 0, vp_vol);
//       analysisManager->FillNtupleDColumn(2, 1, PartKE);
//       analysisManager->FillNtupleDColumn(2, 2, PartPosx);
//       analysisManager->FillNtupleDColumn(2, 3, PartPosy);
//       analysisManager->FillNtupleDColumn(2, 4, PartPosz);
//       analysisManager->FillNtupleDColumn(2, 5, momdirec[0]);
//       analysisManager->FillNtupleDColumn(2, 6, momdirec[1]);
//       analysisManager->FillNtupleDColumn(2, 7, momdirec[2]);
//       analysisManager->FillNtupleDColumn(2, 8, tracklength);
//       analysisManager->FillNtupleDColumn(2, 9, vp_pos[0]);
//       analysisManager->FillNtupleDColumn(2, 10, vp_pos[1]);
//       analysisManager->FillNtupleDColumn(2, 11, vp_pos[2]);

//           analysisManager->AddNtupleRow(2);
//     }
    
// //Particle "exiting" SHIELD----------------------For gamma
//    if(  (postvolume== 0 && prevolume == 33) && (PartPDG ==22)){
//       auto vp_proc = step -> GetTrack() -> GetCreatorProcess() -> GetProcessName();

//       analysisManager->FillNtupleSColumn(3, 0, vp_vol);
//       analysisManager->FillNtupleDColumn(3, 1, PartKE);
//       analysisManager->FillNtupleDColumn(3, 2, PartPosx);
//       analysisManager->FillNtupleDColumn(3, 3, PartPosy);
//       analysisManager->FillNtupleDColumn(3, 4, PartPosz);
//       analysisManager->FillNtupleDColumn(3, 5, momdirec[0]);
//       analysisManager->FillNtupleDColumn(3, 6, momdirec[1]);
//       analysisManager->FillNtupleDColumn(3, 7, momdirec[2]);
//       analysisManager->FillNtupleDColumn(3, 8, tracklength);
//       analysisManager->FillNtupleSColumn(3, 9, vp_proc);
//       analysisManager->FillNtupleDColumn(3, 10, vp_pos[0]);
//       analysisManager->FillNtupleDColumn(3, 11, vp_pos[1]);
//       analysisManager->FillNtupleDColumn(3, 12, vp_pos[2]);
//           analysisManager->AddNtupleRow(3);
//     }

// //Particle "exiting" SHIELD----------------------For neutron
//    if(  (postvolume== 0 && prevolume == 33) && (PartPDG ==2112) ){
//       auto vp_proc = step -> GetTrack() -> GetCreatorProcess() -> GetProcessName();

//       analysisManager->FillNtupleSColumn(4, 0, vp_vol);
//       analysisManager->FillNtupleDColumn(4, 1, PartKE);
//       analysisManager->FillNtupleDColumn(4, 2, PartPosx);
//       analysisManager->FillNtupleDColumn(4, 3, PartPosy);
//       analysisManager->FillNtupleDColumn(4, 4, PartPosz);
//       analysisManager->FillNtupleDColumn(4, 5, momdirec[0]);
//       analysisManager->FillNtupleDColumn(4, 6, momdirec[1]);
//       analysisManager->FillNtupleDColumn(4, 7, momdirec[2]);
//       analysisManager->FillNtupleDColumn(4, 8, tracklength);
//       analysisManager->FillNtupleSColumn(4, 9, vp_proc);
//       analysisManager->FillNtupleDColumn(4, 10, vp_pos[0]);
//       analysisManager->FillNtupleDColumn(4, 11, vp_pos[1]);
//       analysisManager->FillNtupleDColumn(4, 12, vp_pos[2]);
//           analysisManager->AddNtupleRow(4);
//     }


//Particle entering detector 2----------------------
   if(  (postvolume== 2 && prevolume == 0)){

      analysisManager->FillNtupleSColumn(1, 0, vp_vol);
      analysisManager->FillNtupleDColumn(1, 1, PartKE);
      analysisManager->FillNtupleDColumn(1, 2, PartPosx);
      analysisManager->FillNtupleDColumn(1, 3, PartPosy);
      analysisManager->FillNtupleDColumn(1, 4, PartPosz);
      analysisManager->FillNtupleDColumn(1, 5, momdirec[0]);
      analysisManager->FillNtupleDColumn(1, 6, momdirec[1]);
      analysisManager->FillNtupleDColumn(1, 7, momdirec[2]);
      analysisManager->FillNtupleDColumn(1, 8, tracklength);
      analysisManager->FillNtupleDColumn(1, 9, PartPDG);
      analysisManager->FillNtupleDColumn(1, 10, vp_pos[0]);
      analysisManager->FillNtupleDColumn(1, 11, vp_pos[1]);
      analysisManager->FillNtupleDColumn(1, 12, vp_pos[2]);
      analysisManager->FillNtupleSColumn(1, 13, PartName);
          analysisManager->AddNtupleRow(1);
    }


// //For gamma exiting shield, made in shield
//    if((PartPDG ==22) && (vp_vol == "Al_Shield") && (postvolume== 0 && prevolume == 33)){
      // auto vp_proc = step -> GetTrack() -> GetCreatorProcess() -> GetProcessName();

//       analysisManager->FillNtupleSColumn(2, 0, vp_proc);
//       analysisManager->FillNtupleDColumn(2, 1, vp_pos[0]);
//       analysisManager->FillNtupleDColumn(2, 2, vp_pos[1]);
//       analysisManager->FillNtupleDColumn(2, 3, vp_pos[2]);
//       analysisManager->FillNtupleDColumn(2, 4, tracklength);
//       analysisManager->FillNtupleDColumn(2, 5, PartPosx);
//       analysisManager->FillNtupleDColumn(2, 6, PartPosy);
//       analysisManager->FillNtupleDColumn(2, 7, PartPosz);
//       analysisManager->FillNtupleDColumn(2, 8, PartKE);
//       analysisManager->FillNtupleDColumn(2, 9, momdirec[0]);
//       analysisManager->FillNtupleDColumn(2, 10, momdirec[1]);
//       analysisManager->FillNtupleDColumn(2, 11, momdirec[2]);
//           analysisManager->AddNtupleRow(2);
//                   cout << "Hanyi is last gamma made in sheild" << endl;

// //       }

// //For gamma not exiting shield, made in shield
//    if(laststep){
//        if((PartPDG ==22) && (vp_vol == "Al_Shield") && (postvolume == 33)){
//           auto current_pos=step->GetTrack()->GetPosition();
//           auto gamma_tracklength_sub = (current_pos-vp_pos).mag();

//           analysisManager->FillNtupleDColumn(3, 0, tracklength);
//           analysisManager->FillNtupleDColumn(3, 1, PartPosx);
//           analysisManager->FillNtupleDColumn(3, 2, PartPosy);
//           analysisManager->FillNtupleDColumn(3, 3, PartPosz);
//           analysisManager->FillNtupleDColumn(3, 4, PartKE);
//           analysisManager->FillNtupleDColumn(3, 5, gamma_tracklength_sub);
//               analysisManager->AddNtupleRow(3);
//           cout << "mirae is last step_gamma" << endl;
//         }
//       }
}

}


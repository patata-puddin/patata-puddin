/// \file EventAction.cc

#include "EventAction.hh"
#include "RunAction.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
//#include "HistoManager.hh"
#include "Randomize.hh"
#include <iomanip>

namespace SH
{


EventAction::EventAction()
{}
EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    // fEnergy= 0.;
    // fTrackL= 0.;
    // fElectronEnergy= 0.;
    // fElectronTrackL= 0.;
    // fProtonEnergy=0.;
    // fProtonTrackL= 0.;
    // fGammaEnergy=0.;
    // fGammaTrackL= 0.;
    //electN=0.;
}

void EventAction::EndOfEventAction(const G4Event *event)
{
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  // analysisManager->FillH1(0, fEnergy);
  // analysisManager->FillH1(1, fTrackL);
  // analysisManager->FillH1(2, fGammaEnergy);
  // analysisManager->FillH1(3, fGammaTrackL);
  // analysisManager->FillH1(4, fProtonEnergy);
  // analysisManager->FillH1(5, fProtonTrackL);

 /////////////////**************************************************************
  // fill 1st ntuple
  // if (fEnergy !=0){
  // analysisManager->FillNtupleDColumn(2, 0, fEnergy);
  // analysisManager->FillNtupleDColumn(2, 1, fTrackL);
  // analysisManager->AddNtupleRow(2);
  // }

  // if (fProtonEnergy !=0){
  // analysisManager->FillNtupleDColumn(3, 0, fProtonEnergy);
  // analysisManager->FillNtupleDColumn(3, 1, fProtonTrackL);
  // analysisManager->AddNtupleRow(3);
  // }
 /////////////////**************************************************************
  // Print per event (modulo n)
  // //
  auto eventID = event->GetEventID();
  // auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();

  // auto eventPart = event -> GetPrimaryVertex()->G

//   G4int electN;
// if(PartName == "e-"){
//   electN += 1;
// };


//   if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    //G4cout << "---> End of event: " << eventID << G4endl; ---- to see end of event

//     // G4cout
//     //    << "   Absorber: total energy: " << std::setw(7)
//     //                                     << G4BestUnit(fEnergy,"Energy")
//     //    << "       total track length: " << std::setw(7)
//     //                                     << G4BestUnit(fTrackL,"Length")
//     //    << G4endl;

    
//     // // G4cout
//     // //    << "   Energy deposited by GAMMA: total energy: " << std::setw(7)
//     // //                                     << G4BestUnit(fGammaEnergy,"Energy")
//     // //    << "       total track length: " << std::setw(7)
//     // //                                     << G4BestUnit(fGammaTrackL,"Length")
//     // //    << G4endl;

//     //    G4cout
//     //    << "   Energy deposited by PROTON: total energy: " << std::setw(7)
//     //                                     << G4BestUnit(fProtonEnergy,"Energy")
//     //    << "       total track length: " << std::setw(7)
//     //                                     << G4BestUnit(fProtonTrackL,"Length")
//     //    << G4endl;

//     //G4cout << "Number of electron: " << electN << G4endl;
       
// }
 
  //count particle
  // G4cout << "\n  processes :                ";
  // for (size_t j=0; j<emName.size(); ++j) {
  //   G4cout << "\t" << std::setw(14) << emName[j] << "\t";
  // }
  // G4cout << "\t" << std::setw(14) <<"total";

  // G4StepPoint* postPoint=step->GetPostStepPoint();
  // G4string ParticleName=postPoint->GetTrack()->GetDefinition()->GetParticleName();
  
  // if (procName == "electron") NameId = 1;
  // if (procName == "proton") NameId = 2;

  //extended muon process 보기
}
}
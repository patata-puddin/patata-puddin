// // \file electromagnetic/TestEm1/src/HistoManager.cc
// /// \brief Implementation of the HistoManager class



// #include "HistoManager.hh"
// #include "G4UnitsTable.hh"

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// namespace P1d
// {
// HistoManager::HistoManager()
//   : fFileName("P1d")
// {
//   Book();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// HistoManager::~HistoManager()
// {
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HistoManager::Book()
// {
//   // Create or get analysis manager
//   // The choice of analysis technology is done via selection of a namespace
//   // in HistoManager.hh
//   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//   analysisManager->SetDefaultFileType("root");
//   analysisManager->SetFileName(fFileName);
//   analysisManager->SetVerboseLevel(1);
//   analysisManager->SetFirstHistoId(1);     // start histogram numbering from 1
//   analysisManager->SetActivation(true);    // enable inactivation of histograms

  
  
//   // Define histograms start values
//   const G4int kMaxHisto = 7;
//   const G4String id[] = { "0", "1", "2", "3" , "4", "5", "6"};
//   const G4String title[] = 
//                 { "Energy deposit in Target",      //1
//                   "Track length in Target",                //2
//                   "Energy deposit in Target by Gamma",               //3
//                   "Track length in Target by Gamma",                        //4
//                   "Energy deposit in Target by Proton",   //5
//                   "Track length in Target by Proton",   //6
//                   "Energy"                          //7
//                  };
//   // Default values (to be reset via /analysis/h1/set command)
//   G4int nbins = 100;
//   G4double vmin = 0.;
//   G4double vmax = 100.;

//   // Create all histograms as inactivated 
//   // as we have not yet set nbins, vmin, vmax
//   for (G4int k=0; k<kMaxHisto; k++) {
//     G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
//     analysisManager->SetH1Activation(ih, false);
//   }
//   analysisManager->CreateNtuple("P1d", "All info");
//   analysisManager->CreateNtupleDColumn("Track_ID");
//   analysisManager->CreateNtupleDColumn("Part_PDG");
//   analysisManager->FinishNtuple();
// }
  

// }

/// \file RunAction.cc

#include "RunAction.hh"
#include "G4ProcessManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "PrimaryGeneratorAction.hh"
//#include "HistoManager.hh"

#include <vector>
namespace SH
{


RunAction::RunAction()
{
    // set printing event number per each event
   G4RunManager::GetRunManager()->SetPrintProgress(1000);

  //

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //fHistoManager = new HistoManager();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);


  //Creating ntuple
 
    //Ntuple 0
  analysisManager->CreateNtuple("ent_shield", "Particle entering shield");
  analysisManager->CreateNtupleDColumn("pdg");
  analysisManager->CreateNtupleSColumn("name");
  analysisManager->CreateNtupleSColumn("vp_vol");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleDColumn("PartPosx");
  analysisManager->CreateNtupleDColumn("PartPosy");
  analysisManager->CreateNtupleDColumn("PartPosz");

  analysisManager->FinishNtuple();

  //   //Ntuple 1
  // analysisManager->CreateNtuple("ext_shield", "Particle exiting shield");
  // analysisManager->CreateNtupleDColumn("pdg");
  // analysisManager->CreateNtupleSColumn("name");
  // analysisManager->CreateNtupleDColumn("KE");

  // analysisManager->FinishNtuple();

  //   //Ntuple 2
  // analysisManager->CreateNtuple("ext_shield_proton", "Particle exiting shield");
  // analysisManager->CreateNtupleSColumn("vpvol");
  // analysisManager->CreateNtupleDColumn("KE");
  // analysisManager->CreateNtupleDColumn("PartPosx");
  // analysisManager->CreateNtupleDColumn("PartPosy");
  // analysisManager->CreateNtupleDColumn("PartPosz");
  // analysisManager->CreateNtupleDColumn("mx");
  // analysisManager->CreateNtupleDColumn("my");
  // analysisManager->CreateNtupleDColumn("mz");  
  // analysisManager->CreateNtupleDColumn("tracklen");
  // analysisManager->CreateNtupleDColumn("vpx");
  // analysisManager->CreateNtupleDColumn("vpy");
  // analysisManager->CreateNtupleDColumn("vpz");  

  // analysisManager->FinishNtuple();

  //   //Ntuple 3
  // analysisManager->CreateNtuple("ext_shield_gamma", "Particle exiting shield");
  // analysisManager->CreateNtupleSColumn("vpvol");
  // analysisManager->CreateNtupleDColumn("KE");
  // analysisManager->CreateNtupleDColumn("PartPosx");
  // analysisManager->CreateNtupleDColumn("PartPosy");
  // analysisManager->CreateNtupleDColumn("PartPosz");
  // analysisManager->CreateNtupleDColumn("mx");
  // analysisManager->CreateNtupleDColumn("my");
  // analysisManager->CreateNtupleDColumn("mz");  
  // analysisManager->CreateNtupleDColumn("tracklen");
  // analysisManager->CreateNtupleSColumn("proc");
  // analysisManager->CreateNtupleDColumn("vpx");
  // analysisManager->CreateNtupleDColumn("vpy");
  // analysisManager->CreateNtupleDColumn("vpz"); 

  // analysisManager->FinishNtuple();

  //   //Ntuple 4
  // analysisManager->CreateNtuple("ext_shield_neutron", "Particle exiting shield");
  // analysisManager->CreateNtupleSColumn("vpvol");
  // analysisManager->CreateNtupleDColumn("KE");
  // analysisManager->CreateNtupleDColumn("PartPosx");
  // analysisManager->CreateNtupleDColumn("PartPosy");
  // analysisManager->CreateNtupleDColumn("PartPosz");
  // analysisManager->CreateNtupleDColumn("mx");
  // analysisManager->CreateNtupleDColumn("my");
  // analysisManager->CreateNtupleDColumn("mz");  
  // analysisManager->CreateNtupleDColumn("tracklen");
  // analysisManager->CreateNtupleSColumn("proc");
  // analysisManager->CreateNtupleDColumn("vpx");
  // analysisManager->CreateNtupleDColumn("vpy");
  // analysisManager->CreateNtupleDColumn("vpz"); 

  // analysisManager->FinishNtuple();

  //   //Ntuple 5
  // analysisManager->CreateNtuple("made_shield", "Particle made in sheild");
  // analysisManager->CreateNtupleSColumn("name");
  // analysisManager->CreateNtupleSColumn("proc");
  // analysisManager->CreateNtupleDColumn("KE");

  // analysisManager->FinishNtuple();

//below 6 and 7 is from tracking action. Will // for moment
  //   //Ntuple 6
  // analysisManager->CreateNtuple("made_shield_gamma", "Particle made in sheild");
  // analysisManager->CreateNtupleSColumn("proc");
  // analysisManager->CreateNtupleDColumn("KE");
  // analysisManager->CreateNtupleDColumn("vpmx");
  // analysisManager->CreateNtupleDColumn("vpmy");
  // analysisManager->CreateNtupleDColumn("vpmz"); 
  // analysisManager->CreateNtupleDColumn("vpx");
  // analysisManager->CreateNtupleDColumn("vpy");
  // analysisManager->CreateNtupleDColumn("vpz"); 
  // analysisManager->FinishNtuple();

  //   //Ntuple 7
  // analysisManager->CreateNtuple("made_shield_neutron", "Particle made in sheild");
  // analysisManager->CreateNtupleSColumn("proc");
  // analysisManager->CreateNtupleDColumn("KE");
  // analysisManager->CreateNtupleDColumn("vpmx");
  // analysisManager->CreateNtupleDColumn("vpmy");
  // analysisManager->CreateNtupleDColumn("vpmz"); 
  // analysisManager->CreateNtupleDColumn("vpx");
  // analysisManager->CreateNtupleDColumn("vpy");
  // analysisManager->CreateNtupleDColumn("vpz"); 
  // analysisManager->FinishNtuple();

    //Ntuple 6
  analysisManager->CreateNtuple("Detector_2", "Particle made in sheild");
  analysisManager->CreateNtupleSColumn("vpvol");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleDColumn("px");
  analysisManager->CreateNtupleDColumn("py");
  analysisManager->CreateNtupleDColumn("pz"); 
  analysisManager->CreateNtupleDColumn("mx");
  analysisManager->CreateNtupleDColumn("my");
  analysisManager->CreateNtupleDColumn("mz"); 
  analysisManager->CreateNtupleDColumn("tracklen"); 
  analysisManager->CreateNtupleDColumn("pdg"); 
  analysisManager->CreateNtupleDColumn("vpx");
  analysisManager->CreateNtupleDColumn("vpy");
  analysisManager->CreateNtupleDColumn("vpz"); 
  analysisManager->CreateNtupleSColumn("name");
  analysisManager->FinishNtuple();

}


RunAction::~RunAction()
{//delete fHistoManager;
}


void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  
    

  // // Open an output file
  // G4String fileName = "P1d.root";
  
  // G4String fileName = ".csv";
  analysisManager->SetDefaultFileType("root");
  analysisManager->OpenFile(); 
  //^-----Do this to change the name in mac file
  // analysisManager->OpenFile("H.root");
  //^------Do this to use gui
  // G4cout << "Using " << analysisManager->GetType() << G4endl;
}


void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
  
  // if ( analysisManager->GetH1(5) ) {
    
  //   if(isMaster) {
  //     G4cout << "for the entire run " << G4endl << G4endl;
  //   }
  //   else {
  //     G4cout << "for the local thread " << G4endl << G4endl;
  //   }

  //   G4cout << " Energy deposited in Target : mean = "
  //      << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
  //      << " rms = "
  //      << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

  //   G4cout << " Length in Target : mean = "
  //     << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length")
  //     << " rms = "
  //     << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;

  //   G4cout << " EofGAMMA : mean = "
  //     << G4BestUnit(analysisManager->GetH1(2)->mean(), "Energy")
  //     << " rms = "
  //     << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Energy") << G4endl;
  //   G4cout << " LofGAMMA : mean = "
  //      << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
  //      << " rms = "
  //      << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;


  //   auto EProtonMean= analysisManager->GetH1(4)->mean();
  //   auto LProtonMean= analysisManager->GetH1(5)->mean();

  //   G4cout << " EofProton : mean = "
  //     << G4BestUnit(analysisManager->GetH1(4)->mean(), "Energy")
  //     << " rms = "
  //     << G4BestUnit(analysisManager->GetH1(4)->rms(),  "Energy")
  //     << " ,  E per cm: "
  //     << (EProtonMean/LProtonMean) << G4endl;

  //     G4cout << " EofProton without best unit: mean = "
  //     << analysisManager->GetH1(4)->mean()
  //     << " ,  E per cm: "
  //     << (EProtonMean/LProtonMean)
  //     << " , LofProton without best unit:: mean = "
  //     << analysisManager->GetH1(5)->mean() << G4endl;


  //   G4cout << " LofProton : mean = "
  //      << G4BestUnit(analysisManager->GetH1(5)->mean(), "Length")
  //      << " rms = "
  //      << G4BestUnit(analysisManager->GetH1(5)->rms(),  "Length") << G4endl;



  
  // }   

    analysisManager->Write();


    analysisManager->CloseFile();

        

    


}
}
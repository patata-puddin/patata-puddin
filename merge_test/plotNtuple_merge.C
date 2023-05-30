#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TSystemDirectory.h"
#include "stdio.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TChain.h"

//Merge files and plot them
void plotNtuple_merge()
{
    gROOT->Reset();
  
  // TChain chtotal("ent_shield");


  // // char filename[40];
  // // int d;
  // // for(d=1;d<=3;d++){
  // //   sprintf (filename, "good%d.root", d);
  // //   chtotal.Add(filename);

  // // }
  // chtotal.Add("good1.root");
  // chtotal.Add("good2.root");
  // chtotal.Add("good3.root");
TChain *chain=new TChain("ent_shield");
   chain->Add("good1.root");
   chain->Add("good2.root");
   chain->Add("good3.root");

//     TFile *P1dfile =new TFile(filename, "read");
//     // // Create a canvas and divide it into 2x2 pads
5F97E9
TCanvas* c1 = new TCanvas("c1", "Histogram of Entering Particle", 20, 20, 1000, 1000);
  c1->Divide(2,2);
  c1->SetGrid();
  int markersize= 2;
  double labelsize=0.09;  

  Double_t sh_KE;
  Double_t sh_Pdg;
  //   chtotal.SetBranchAddress("KE",&sh_KE);
  // chtotal.SetBranchAddress("pdg",&sh_Pdg);
chain->SetBranchAddress("KE",&sh_KE);
chain->SetBranchAddress("pdg",&sh_Pdg);

    TH1D *hist = new TH1D("All", "All particle", 50,0,30);
auto Entry_KE = chain->GetBranch("pdg")->GetEntries() ;
 int j=0;
 cout << Entry_KE << endl;
   for (j=0;j<Entry_KE; j++){
      chain->GetEntry(j);
      
 cout << sh_KE << endl;
      
     
   }

   //-------------------------------
cout << endl << " In Total " << endl;
  c1->cd(1);
gStyle->SetPaintTextFormat("g ");

gPad->SetLogy();
  gPad->SetGrid();
  // TTree *TAll = (TTree *) P1dfile -> Get("P1d");
  chain->Draw("name>>h","","");

  TH1F *h = (TH1F*)gDirectory->Get("h");
  //h1->SetBarOffset();
  h->SetMarkerSize(markersize);
  // h->SetLabelSize(labelsize);
  h->LabelsOption(">");
  h->SetStats(0);
  h->SetFillColor(kRed);
  h->SetFillStyle(3001);
 // h->SetAxisRange(0,1000,"y"); // -----자른다면 
  h->Draw("Text0 same");

  int i;
  int totentry = h->GetNbinsX();

  cout << "Bin       " << "# of particle" << endl;
  for(i=1;i<=totentry;i++){
    int num_part = h->GetBinContent(i);
    cout << i << "              " << num_part << endl;
  }

}

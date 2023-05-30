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

// Plot over all the files
void plotNtuple_loopver()
{
    gROOT->Reset();
  
  // gROOT->SetStyle("Plain");
  // TString myfolder = "/Users/hanyijang/geant4/geant4-v11.0.2-install/share/Geant4-11.0.2/examples/basic/P1d/meme/file";
  // TSystemDirectory dir(myfolder, myfolder);
  // TList *files = dir.GetListOfFiles();
  // TSystemFile *file;
  // TString fname;
  // TIter next(files);
  //     while ((file=(TSystemFile*)next())) {
  //       fname = file->GetName();
  //       ;}
  
  char filename[40];
  int d;
  for(d=1;d<=3;d++){
    sprintf (filename, "good%d.root", d);

    TFile *P1dfile =new TFile(filename, "read");
    // // Create a canvas and divide it into 2x2 pads

TCanvas* c1 = new TCanvas("c1", "Histogram of Entering Particle", 20, 20, 1000, 1000);
  c1->Divide(2,2);
  c1->SetGrid();
  int markersize= 2;
  double labelsize=0.09;  

   //-------------------------------
cout << endl << " In Total " << endl;
  c1->cd(1);
gStyle->SetPaintTextFormat("g ");


  gPad->SetGrid();
  TTree *TAll = (TTree *) P1dfile -> Get("ent_shield");
  TAll -> Draw("name>>h","","");

  TH1F *h = (TH1F*)gDirectory->Get("h");
  //h1->SetBarOffset();
  h->SetMarkerSize(markersize);
  h->SetLabelSize(labelsize);
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

  
char outputfile[150];
sprintf (outputfile, "/Users/hanyijang/geant4/geant4-v11.0.2-install/share/Geant4-11.0.2/examples/basic/SH/lala/lala_result/good%d_1.png", d);
  c1->Print(outputfile);

  //-------------------------------**********************************
// TCanvas* c2 = new TCanvas("c2", "Entering Particle Energy distribution", 20, 20, 2000, 1000);
//   c2->Divide(4,3);
//   c2->SetGrid();

//   // TTree *TVol1 = (TTree *) P1dfile -> Get("In_Alpide_Particle");
//   Double_t Al_KE;
//   Double_t Al_2212_KE;
//   Double_t Al_22_KE;
//   Double_t Al_11_KE;


//   TVol1 -> SetBranchAddress("Alp_KE",&Al_KE);
//   TVol1 -> SetBranchAddress("Alp_2212_KE",&Al_2212_KE);
//   TVol1 -> SetBranchAddress("Alp_22_KE",&Al_22_KE);
//   TVol1 -> SetBranchAddress("Alp_11_KE",&Al_11_KE);


//   TH1D *hist_Alp_KE = new TH1D("hist_Alp_E", "Particle Energy entering Alpide", 300, 0, 30);
//   TH1D *hist_Alp_2212_KE = new TH1D("hist_Alp_2212_E", "Proton Energy entering Alpide", 300, 0, 30);
//   TH1D *hist_Alp_22_KE = new TH1D("hist_Alp_22_E", "Gamma Energy entering Alpide", 300, 0, 30);
//   TH1D *hist_Alp_11_KE = new TH1D("hist_Alp_11_E", "Electron Energy entering Alpide", 300, 0, 30);

//   //xbins로 하고 싶은데, 범위를 항상 지정해주고 싶지 않음
//   int j;
//  if(TVol1 -> GetBranch("Alp_KE") != nullptr){
//   auto Entry_Al_KE = TVol1->GetBranch("Alp_KE")->GetEntries() ;
//    for (j=0;j<Entry_Al_KE; j++){
//       TVol1 -> GetEntry(j);
//           hist_Alp_KE -> Fill(Al_KE);

//       if(Al_2212_KE != 0) {
//           hist_Alp_2212_KE -> Fill(Al_2212_KE);  
//       }
//       if(Al_22_KE != 0) {
//           hist_Alp_22_KE -> Fill(Al_22_KE);  
//       }
//       if(Al_11_KE != 0) {
//           hist_Alp_11_KE -> Fill(Al_11_KE);  
//       }

//    }

//   c2->cd(2);
//   gPad->SetGrid();
//   hist_Alp_2212_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_Alp_2212_KE->GetYaxis()->SetTitle("Count");
//   hist_Alp_2212_KE->SetFillColor(kRed);
//   hist_Alp_2212_KE->SetFillStyle(3001);
//   hist_Alp_2212_KE->Draw("hist same");
//      c2->Update();
//   TPaveStats *s1 = (TPaveStats*)hist_Alp_2212_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//   s1->SetX1NDC(0.4); s1->SetX2NDC(0.6);
//    gPad->Modified();
//    gPad->Update();

//     c2->cd(1);
//   gPad->SetGrid();
//   hist_Alp_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_Alp_KE->GetYaxis()->SetTitle("Count");
//   hist_Alp_KE->SetFillColor(kRed);
//   hist_Alp_KE->SetFillStyle(3001);
//   hist_Alp_KE->Draw("hist same");
//      c2->Update();
//   TPaveStats *s2 = (TPaveStats*)hist_Alp_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//   s2->SetX1NDC(0.4); s2->SetX2NDC(0.6);
//    gPad->Modified();
//    gPad->Update();
  

//       c2->cd(3);
//   gPad->SetGrid();
//   hist_Alp_22_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_Alp_22_KE->GetYaxis()->SetTitle("Count");
//   hist_Alp_22_KE->SetFillColor(kRed);
//   hist_Alp_22_KE->SetFillStyle(3001);
//   hist_Alp_22_KE->Draw("hist same");
//        c2->Update();
//   TPaveStats *s3 = (TPaveStats*)hist_Alp_22_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//   s3->SetX1NDC(0.4); s3->SetX2NDC(0.6);
//    gPad->Modified();
//    gPad->Update();

//         c2->cd(4);
//   gPad->SetGrid();
//   hist_Alp_11_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_Alp_11_KE->GetYaxis()->SetTitle("Count");
//   hist_Alp_11_KE->SetFillColor(kRed);
//   hist_Alp_11_KE->SetFillStyle(3001);
//   hist_Alp_11_KE->Draw("hist same");
//        c2->Update();
//   TPaveStats *s4 = (TPaveStats*)hist_Alp_11_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//   s4->SetX1NDC(0.4); s4->SetX2NDC(0.6);
//    gPad->Modified();
//    gPad->Update();

//   //  cout << "Std of Alpide proton is "<< hist_Alp_2212_KE-> GetStdDev() << endl;
//  }
  
// char outputfile_2[150];
// sprintf (outputfile_2, "/Users/hanyijang/geant4/geant4-v11.0.2-install/share/Geant4-11.0.2/examples/basic/P1d/meme/file/result2/good%d_2.png", d);
//   c2->Print(outputfile_2);


  }



}

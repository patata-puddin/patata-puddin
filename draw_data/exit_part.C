#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"

//exiting shield- total particle 
//exiting shield- E dist of p,r,n
void exit_part()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Al.root", "read");
TCanvas* c1 = new TCanvas("c1", "Histogram of Particle exiting shield", 20, 20, 1000, 1000);
  c1->SetGrid();
  c1->Divide(1,2);

  c1->cd(1)->SetLogy();
  c1->cd(2)->SetLogy();
  c1->cd(3)->SetLogy();

  int markersize= 1;
  int i;
  double labelsize=0.09;  

  //For total particle entering shield

  gPad->SetGrid();
  gPad->SetLogy();
  c1->cd(1);
  TTree *TVol1 = (TTree *) P1dfile -> Get("ext_shield");
  TVol1 -> Draw("name>>h1","","");

  TH1F *h1 = (TH1F*)gDirectory->Get("h1");
  if(h1 != nullptr){
  h1->SetMarkerSize(markersize);
  // h1->SetLabelSize(labelsize);
  h1->LabelsOption(">");
  h1->SetStats(0);
  h1->SetTitle("Total particle exiting shield");
  h1->SetFillColor(kRed);
  h1->SetFillStyle(3001);
  h1->Draw("Text0 same");
  }



  c1->cd(2);

  TTree *TVol2 = (TTree *) P1dfile -> Get("made_shield");
  TVol2 -> Draw("name>>h2","","");

  TH1F *h2 = (TH1F*)gDirectory->Get("h2");
  if(h2 != nullptr){
  h2->SetMarkerSize(markersize);
  // h1->SetLabelSize(labelsize);
  h2->LabelsOption(">");
  h2->SetStats(0);
  h2->SetTitle("Particle made in shield");
  h2->SetFillColor(kRed);
  h2->SetFillStyle(3001);
  h2->Draw("Text0 same");
  }


}
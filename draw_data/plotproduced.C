#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"


void plotproduced()
{
    //Shield
TFile *P1dfile =new TFile("meme.root", "read");
TCanvas* c1 = new TCanvas("c1", "Produced", 20, 20, 2000, 2000);
  c1->Divide(2,2);
  c1->SetGrid();


//Shield
  c1->cd(1);
TTree *shield = (TTree *) P1dfile -> Get("made_shield");
shield -> Draw("name>>h_part","","");
 TH1F *h1 = (TH1F*)gDirectory->Get("h_part");

if(h1 != nullptr){
  //h1->SetBarOffset();
  // h->SetMarkerSize(markersize);
  // h->SetLabelSize(labelsize);
  h1->LabelsOption(">");
  h1->SetStats(0);
  h1->SetTitle("particle produced in shield");
  h1->SetFillColorAlpha(kRed, 0.3);
  h1->SetFillStyle(3001);
 // h->SetAxisRange(0,1000,"y"); // -----자른다면 
  h1->Draw("Text90 same");
    }
//get KE fron it


  Double_t shield_KE, shield_PDG;
  

  shield -> SetBranchAddress("KE",&shield_KE);
  shield -> SetBranchAddress("pdg",&shield_PDG);

  TH1D *shield_KE_hist_2212 = new TH1D("shield_KE_hist_2212", "Proton Energy produced in shield", 200, 0, 30);
  TH1D *shield_KE_hist_22 = new TH1D("shield_KE_hist_22", "Gamma Energy produced in shield", 200, 0, 30);

  //xbins로 하고 싶은데, 범위를 항상 지정해주고 싶지 않음
  int j;
 
  auto Entry = shield->GetBranch("vp_KE")->GetEntries() ;
   for (j=0;j<Entry; j++){
      shield -> GetEntry(j);

      if(shield_PDG == 2212) {
          shield_KE_hist_2212 -> Fill(shield_KE);  
      }
       if(shield_PDG == 22) {
          shield_KE_hist_22 -> Fill(shield_KE);  
      }
   }
    c1->cd(2);
  gPad->SetGrid();gPad->SetLogy();
  
  shield_KE_hist_2212->GetXaxis()->SetTitle("Energy (MeV)");
  shield_KE_hist_2212->GetYaxis()->SetTitle("Count");
  shield_KE_hist_2212->SetFillColor(kRed);
  shield_KE_hist_2212->SetFillStyle(3001);
  shield_KE_hist_2212->Draw("hist same");
     c1->Update();
  TPaveStats *s1 = (TPaveStats*)shield_KE_hist_2212->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s1->SetX1NDC(0.4); s1->SetX2NDC(0.6);
   gPad->Modified();
   gPad->Update();

       c1->cd(3);
  gPad->SetGrid();gPad->SetLogy();
  
  shield_KE_hist_22->GetXaxis()->SetTitle("Energy (MeV)");
  shield_KE_hist_22->GetYaxis()->SetTitle("Count");
  shield_KE_hist_22->SetFillColor(kRed);
  shield_KE_hist_22->SetFillStyle(3001);
  shield_KE_hist_22->Draw("hist same");
     c1->Update();
  TPaveStats *s2 = (TPaveStats*)shield_KE_hist_22->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s2->SetX1NDC(0.4); s2->SetX2NDC(0.6);
   gPad->Modified();
   gPad->Update();


////-------Dump-----
TCanvas* c2 = new TCanvas("c2", "Produced", 20, 20, 2000, 2000);
  c2->Divide(2,2);
  c2->SetGrid();


//Shield
  c2->cd(1);
TTree *dump = (TTree *) P1dfile -> Get("Dump_made");
dump -> Draw("part>>h_dump_part","","");
 TH1F *h2 = (TH1F*)gDirectory->Get("h_dump_part");

if(h2 != nullptr){
  //h1->SetBarOffset();
  // h->SetMarkerSize(markersize);
  // h->SetLabelSize(labelsize);
  h2->LabelsOption(">");
  h2->SetStats(0);
  h2->SetTitle("particle produced in dump");
  h2->SetFillColorAlpha(kRed, 0.3);
  h2->SetFillStyle(3001);
 // h->SetAxisRange(0,1000,"y"); // -----자른다면 
  h2->Draw("Text90 same");
    }
//get KE fron it


  Double_t dump_KE, dump_PDG;
  

  dump -> SetBranchAddress("vp_KE",&dump_KE);
  dump -> SetBranchAddress("partpdg",&dump_PDG);

  TH1D *dump_KE_hist_2212 = new TH1D("dump_KE_hist_2212", "Proton Energy produced in dump", 200, 0, 30);
  TH1D *dump_KE_hist_22 = new TH1D("dump_KE_hist_22", "Gamma Energy produced in dump", 200, 0, 30);

 
  auto Entry_dump = dump->GetBranch("vp_KE")->GetEntries() ;
   for (j=0;j<Entry_dump; j++){
      dump -> GetEntry(j);

      if(dump_PDG == 2212) {
          dump_KE_hist_2212 -> Fill(dump_KE);  
      }
       if(dump_PDG == 22) {
          dump_KE_hist_22 -> Fill(dump_KE);  
      }
   }
    c2->cd(2);
  gPad->SetGrid();gPad->SetLogy();
  
  dump_KE_hist_2212->GetXaxis()->SetTitle("Energy (MeV)");
  dump_KE_hist_2212->GetYaxis()->SetTitle("Count");
  dump_KE_hist_2212->SetFillColor(kRed);
  dump_KE_hist_2212->SetFillStyle(3001);
  dump_KE_hist_2212->Draw("hist same");
     c2->Update();
  TPaveStats *s3 = (TPaveStats*)dump_KE_hist_2212->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s3->SetX1NDC(0.4); s3->SetX2NDC(0.6);
   gPad->Modified();
   gPad->Update();

       c2->cd(3);
  gPad->SetGrid();gPad->SetLogy();
  
  dump_KE_hist_22->GetXaxis()->SetTitle("Energy (MeV)");
  dump_KE_hist_22->GetYaxis()->SetTitle("Count");
  dump_KE_hist_22->SetFillColor(kRed);
  dump_KE_hist_22->SetFillStyle(3001);
  dump_KE_hist_22->Draw("hist same");
     c2->Update();
  TPaveStats *s4 = (TPaveStats*)dump_KE_hist_22->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s4->SetX1NDC(0.4); s4->SetX2NDC(0.6);
   gPad->Modified();
   gPad->Update();
}
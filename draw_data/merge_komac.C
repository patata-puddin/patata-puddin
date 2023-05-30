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
void merge_komac()
{
    gROOT->Reset();
  
  TChain chtotal("Detector_2");


  // char filename[40];
  // int d;
  // for(d=1;d<=2;d++){
  //   sprintf (filename, "Pb_108_komac_real%d.root", d);
  //   chtotal.Add(filename);

  // }

chtotal.Add("Pb_108_komac_real1.root");
chtotal.Add("Pb_108_komac_real2.root");

//     TFile *P1dfile =new TFile(filename, "read");
//     // // Create a canvas and divide it into 2x2 pads

  Double_t sh_KE;
  Double_t sh_Pdg;
  Double_t posx, posy, posz;
  Char_t vpvol_p[100];

  int j;
  int counte;
  Double_t max=1;
  Double_t min=10000000;
   int p_count = 0 ;  
  int g_count = 0 ;  
  int e_count = 0 ;


  chtotal.SetBranchAddress("KE",&sh_KE);
  chtotal.SetBranchAddress("pdg",&sh_Pdg);
  chtotal.SetBranchAddress("px",&posx);
  chtotal.SetBranchAddress("py",&posy);
  chtotal.SetBranchAddress("pz",&posz);
  chtotal.SetBranchAddress("vpvol",&vpvol_p); 

  TH2D *hist = new TH2D("All", "All particle", 50, 1750, 2050 , 50, -174, 126);
  TH2D *hist_p = new TH2D("proton", "proton", 50, 1750, 2050 , 50, -174, 126);
  TH2D *hist_g = new TH2D("gamma", "gamma",  50, 1750, 2050 , 50, -174, 126);
  TH2D *hist_e = new TH2D("electron", "electron",  50, 1750, 2050 , 50, -174, 126);
  TH2D *hist_pge = new TH2D("p_g_e", "proton+gamma+electron",  50, 1750, 2050 , 50, -174, 126);
  TH2D *hist_ge = new TH2D("g_e", "gamma+electron",  50, 1750, 2050 , 50, -174, 126);
  
//      if((abs(posx-215) < 0.0000001) && ((strcmp(vpvol_p, "Pb_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0)||(strcmp(vpvol_p, "Dump") == 0))){           

  auto Entry_KE = chtotal.GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      chtotal.GetEntry(j);
      if((abs(posx+231) < 0.0000001) && (strcmp(vpvol_p, "Detector2") != 0)){           
           //if((posz >1627  && posz<2067) && (posy> -220 && posy < 220)){
            hist->Fill(posz, posy);
            if (sh_Pdg == 2212) {
              hist_p -> Fill(posz, posy);    
                           p_count +=1;

            }
            if (sh_Pdg == 22) {
              hist_g -> Fill(posz, posy);    
                           g_count +=1;

            }
            if (sh_Pdg == 11) {
              hist_e -> Fill(posz, posy);    
                           e_count +=1;

            }
            if (sh_Pdg ==2212 || sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_pge ->Fill(posz, posy); 
            }
            if (sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_ge ->Fill(posz, posy); 
            }
          //}
          if (posy > max) {
      max = posy;
    }
              if (posy < min) {
      min = posy;
    }
      }
   }

   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1300, 650);
c3->Divide(4,2);
    std::cout <<"proton: " <<p_count<< "\n";
    std::cout <<"gamma: " <<g_count<< "\n";
    std::cout <<"electron: " <<e_count<< "\n";

    c3->cd(1);
    hist_p->GetXaxis()->SetTitle("z(mm)");
  hist_p->GetYaxis()->SetTitle("y(mm)");
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;

    hist_p->Draw("colz");    

    std::cout <<"max: " <<max<< "\n";
    std::cout <<"min: " <<min<< "\n";

    c3->cd(2);
    hist_g->GetXaxis()->SetTitle("z(mm)");
  hist_g->GetYaxis()->SetTitle("y(mm)");
    // hist_g->SetMaximum(206);
  // auto mad = hist_g->GetMaximum();
  //   cout << mad << endl;
    hist_g->Draw("colz"); 

    c3->cd(3);
    hist_e->GetXaxis()->SetTitle("z(mm)");
  hist_e->GetYaxis()->SetTitle("y(mm)");
    hist_e->Draw("colz"); 
    
    //c3->cd();
    //hist_pge->Draw("colz");

  //   c3->cd(4);
  //   TH2D *h2_ratio = (TH2D*)hist_p->Clone("h2_ratio");
  //   h2_ratio->Divide(hist_pge);
  //   h2_ratio->SetTitle("proton/(p+g+e)");
  //   h2_ratio->SetStats(0);  
  //     h2_ratio->GetXaxis()->SetTitle("z(mm)");
  //   h2_ratio->GetYaxis()->SetTitle("y(mm)");
  //   h2_ratio->Draw("colz");

  //  c3->cd(5);
  //   TH2D *h2_ratio1 = (TH2D*)hist_p->Clone("h2_ratio1");
  //   h2_ratio1->Divide(hist_ge);
  //   h2_ratio1->SetTitle("p/(g+e)");
  //   h2_ratio1->SetStats(0);  
  //   h2_ratio1->GetXaxis()->SetTitle("z(mm)");
  //   h2_ratio1->GetYaxis()->SetTitle("y(mm)");
  //   h2_ratio1->Draw("colz");
  
c3->Print("merge_result1.png");

}

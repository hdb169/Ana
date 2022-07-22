
#include <sstream>
#include <string>
#include <fstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TPaveLabel.h"

void plot_new_pimYield(){

  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  c1->SetGrid();

  auto mg = new TMultiGraph("mg","Q2 = 4 GeV2, x = 0.35, pi- yield data / pi- yield simc");

 
  //2
  std::ifstream infile2("newtxtfiles/z04_pim.txt");

  std::string line2;
  
  vector <double> z2; 
  vector <double> ratio2;//current
  vector <double> datasig2;
  vector <double> sig2;
  vector <double> er2;
  vector <double> err2;

  while (std::getline(infile2, line2)){

    std::istringstream iss(line2);
    double a2, b2, c2, d2, e2, f2 ;
    if(line2[0] == '#') continue;

    if (!(iss >> a2 >> b2 >> c2 >> d2 >>e2 >>f2))
      {
           
	break;
           
      } 
       
    z2.push_back(a2);//z
    ratio2.push_back(b2);//yield ratio
    datasig2.push_back(c2);//measured sighad =  ratio*sighad
    sig2.push_back(d2);//sighad sim 
    er2.push_back(e2);//error in ratio pi-data/pi-simc
    err2.push_back(f2);//err in measured sighad

  }

  ///add new

//2
  std::ifstream infile3("newtxtfiles/z05_pim.txt");

  std::string line3;
  
  vector <double> z3; 
  vector <double> ratio3;//current
  vector <double> datasig3;
  vector <double> sig3;
  vector <double> er3;
  vector <double> err3;

  while (std::getline(infile3, line3)){

    std::istringstream iss(line3);
    double a3, b3, c3, d3, e3, f3 ;
    if(line3[0] == '#') continue;

    if (!(iss >> a3 >> b3 >> c3 >> d3 >>e3 >>f3))
      {
           
	break;
           
      } 
       
    z3.push_back(a3);
    ratio3.push_back(b3);
    datasig3.push_back(c3);
    sig3.push_back(d3);
    er3.push_back(e3);
    err3.push_back(f3);

  }

  ///add new






//2
  std::ifstream infile4("newtxtfiles/z06_pim.txt");

  std::string line4;
  
  vector <double> z4; 
  vector <double> ratio4;//current
  vector <double> datasig4;
  vector <double> sig4;
  vector <double> er4;
  vector <double> err4;

  while (std::getline(infile4, line4)){

    std::istringstream iss(line4);
    double a4, b4, c4, d4, e4, f4 ;
    if(line4[0] == '#') continue;

    if (!(iss >> a4 >> b4 >> c4 >> d4 >>e4 >>f4))
      {
           
	break;
           
      } 
       
    z4.push_back(a4);
    ratio4.push_back(b4);
    datasig4.push_back(c4);
    sig4.push_back(d4);
    er4.push_back(e4);
    err4.push_back(f4);

  }

  ///add new




//2
  std::ifstream infile5("newtxtfiles/z07_pim.txt");

  std::string line5;
  
  vector <double> z5; 
  vector <double> ratio5;//current
  vector <double> datasig5;
  vector <double> sig5;
  vector <double> er5;
  vector <double> err5;

  while (std::getline(infile5, line5)){

    std::istringstream iss(line5);
    double a5, b5, c5, d5, e5, f5 ;
    if(line5[0] == '#') continue;

    if (!(iss >> a5 >> b5 >> c5 >> d5 >>e5 >>f5))
      {
           
	break;
           
      } 
       
    z5.push_back(a5);
    ratio5.push_back(b5);
    datasig5.push_back(c5);
    sig5.push_back(d5);
    er5.push_back(e5);
    err5.push_back(f5);

  }

  ///add new










  
  


  //simc
  auto gr22 = new TGraphErrors(z2.size(), &z2[0], &ratio2[0], 0, &er2[0]);
  gr22->SetName("gr22");
  gr22->SetMarkerStyle(20);
  gr22->SetMarkerSize(1.4);
  gr22->SetTitle("pi- z = 0.4 data/simc");
  gr22->SetLineColor(kBlack);
  gr22->SetLineWidth(2);
  gr22->SetMarkerColor(kBlack);
  gr22->SetFillStyle(0); 
  // gr22->Draw("AP");

  

  //simc
  auto gr33 = new TGraphErrors(z3.size(), &z3[0], &ratio3[0], 0,  &er3[0]);
  gr33->SetName("gr33");
  gr33->SetMarkerStyle(20);
  gr33->SetMarkerSize(1.4);
  gr33->SetTitle("pi- z = 0.5 data/simc");
  gr33->SetLineColor(kRed);
  gr33->SetLineWidth(2);
  gr33->SetMarkerColor(kRed);
  gr33->SetFillStyle(0); 
  // gr22->Draw("AP");

  auto gr44 = new TGraphErrors(z4.size(), &z4[0], &ratio4[0], 0, &er4[0]);
  gr44->SetName("gr44");
  gr44->SetMarkerStyle(20);
  gr44->SetMarkerSize(1.4);
  gr44->SetTitle("pi- z = 0.6: data/simc");
  gr44->SetLineColor(kGreen);
  gr44->SetLineWidth(2);
  gr44->SetMarkerColor(kGreen);
  gr44->SetFillStyle(0); 
  // gr22->Draw("AP");
  


  //simc
  auto gr55 = new TGraphErrors(z5.size(), &z5[0], &ratio5[0], 0, &er5[0]);
  gr55->SetName("gr55");
  gr55->SetMarkerStyle(20);
  gr55->SetMarkerSize(1.4);
  gr55->SetTitle("pi- z = 0.7: data/simc");
  gr55->SetLineColor(kBlue);
  gr55->SetLineWidth(2);
  gr55->SetMarkerColor(kBlue);
  gr55->SetFillStyle(0); 
  // gr22->Draw("AP");
  
  
  
  mg->Add(gr22);

  
  mg->Add(gr33);

  mg->Add(gr44);
  mg->Add(gr55);
 
  
  mg->Draw("AP");
  mg->GetYaxis()->SetRangeUser(0.,1.2);

  c1->BuildLegend();
  mg->SetTitle("Q2 = 4 GeV2, x = 0.35,Q2 = 4 GeV2, x = 0.35, pi- yield data / pi- yield simc;z;ratio");

   c1->Print("pdf/ratio_pimdatasimc.gif"); 
}

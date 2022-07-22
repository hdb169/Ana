
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

void plot_new_pipMult(){

  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  c1->SetGrid();

  auto mg = new TMultiGraph("mg","Q2 = 4 GeV2, x = 0.35, pi+: Multiplicity: data = (Yield_Data/Yield_simc)*sighad and Multiplicity simc = Sighad");

 
  //2
  std::ifstream infile2("newtxtfiles/z04_pip.txt");

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
       
    z2.push_back(a2);
    ratio2.push_back(b2);
    datasig2.push_back(c2);
    sig2.push_back(d2);
    er2.push_back(e2);
    err2.push_back(f2);

  }

  ///add new

//2
  std::ifstream infile3("newtxtfiles/z05_pip.txt");

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
  std::ifstream infile4("newtxtfiles/z06_pip.txt");

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
  std::ifstream infile5("newtxtfiles/z07_pip.txt");

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










  
  

  //plot data
 auto gr2 = new TGraphErrors(z2.size(), &z2[0], &datasig2[0], 0, 0);
  gr2->SetName("gr2");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.4);
  gr2->SetTitle("pi+ z = 0.4: simc");
  gr2->SetLineColor(kBlack);
  gr2->SetLineWidth(2);
  gr2->SetMarkerColor(kBlack);
  gr2->SetFillStyle(0);
  //gr2->Draw("L");

  //simc
  auto gr22 = new TGraphErrors(z2.size(), &z2[0], &sig2[0], 0, &err2[0]);
  gr22->SetName("gr22");
  gr22->SetMarkerStyle(20);
  gr22->SetMarkerSize(1.4);
  gr22->SetTitle("pi+ z = 0.4 data");
  gr22->SetLineColor(kBlack);
  gr22->SetLineWidth(2);
  gr22->SetMarkerColor(kBlack);
  gr22->SetFillStyle(0); 
  // gr22->Draw("AP");

  

  //plot data
 auto gr3 = new TGraphErrors(z3.size(), &z3[0], &datasig3[0], 0,0);
  gr3->SetName("gr3");
  gr3->SetMarkerStyle(21);
  gr3->SetMarkerSize(1.4);
  gr3->SetTitle("pi+ z = 0.5: simc");
  gr3->SetLineColor(kRed);
  gr3->SetLineWidth(2);
  gr3->SetMarkerColor(kRed);
  gr3->SetFillStyle(0);
  //gr3->Draw("L");

  //simc
  auto gr33 = new TGraphErrors(z3.size(), &z3[0], &sig3[0], 0,  &err3[0]);
  gr33->SetName("gr33");
  gr33->SetMarkerStyle(20);
  gr33->SetMarkerSize(1.4);
  gr33->SetTitle("pi+ z = 0.5 data");
  gr33->SetLineColor(kRed);
  gr33->SetLineWidth(2);
  gr33->SetMarkerColor(kRed);
  gr33->SetFillStyle(0); 
  // gr22->Draw("AP");

  
 //plot data
 auto gr4 = new TGraphErrors(z4.size(), &z4[0], &datasig4[0], 0, 0);
  gr4->SetName("gr4");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerSize(1.4);
  gr4->SetTitle("pi+ z = 0.6: simc");
  gr4->SetLineColor(kGreen);
  gr4->SetLineWidth(2);
  gr4->SetMarkerColor(kGreen);
  gr4->SetFillStyle(0);
  //gr4->Draw("L");

  //simc
  auto gr44 = new TGraphErrors(z4.size(), &z4[0], &sig4[0], 0, &err4[0]);
  gr44->SetName("gr44");
  gr44->SetMarkerStyle(20);
  gr44->SetMarkerSize(1.4);
  gr44->SetTitle("pi+ z = 0.6: data");
  gr44->SetLineColor(kGreen);
  gr44->SetLineWidth(2);
  gr44->SetMarkerColor(kGreen);
  gr44->SetFillStyle(0); 
  // gr22->Draw("AP");
  
 //plot data
 auto gr5 = new TGraphErrors(z5.size(), &z5[0], &datasig5[0], 0,0);
  gr5->SetName("gr5");
  gr5->SetMarkerStyle(21);
  gr5->SetMarkerSize(1.4);
  gr5->SetTitle("pi+ z = 0.7: simc");
  gr5->SetLineColor(kBlue);
  gr5->SetLineWidth(2);
  gr5->SetMarkerColor(kBlue);
  gr5->SetFillStyle(0);
  //gr5->Draw("L");

  //simc
  auto gr55 = new TGraphErrors(z5.size(), &z5[0], &sig5[0], 0, &err5[0]);
  gr55->SetName("gr55");
  gr55->SetMarkerStyle(20);
  gr55->SetMarkerSize(1.4);
  gr55->SetTitle("pi+ z = 0.7: data");
  gr55->SetLineColor(kBlue);
  gr55->SetLineWidth(2);
  gr55->SetMarkerColor(kBlue);
  gr55->SetFillStyle(0); 
  // gr22->Draw("AP");
  
  
  
  mg->Add(gr2);
  mg->Add(gr22);

  
  mg->Add(gr3);
  mg->Add(gr33);

 mg->Add(gr4);
  mg->Add(gr44);
  mg->Add(gr5);
  mg->Add(gr55);
 
  
  mg->Draw("AP");
  c1->BuildLegend();
  mg->SetTitle("Q2 = 4 GeV2, x = 0.35, pi+: Multiplicity: data = (Yield_Data/Yield_simc)*sighad and Multiplicity simc = Sighad; z ; Multiplicity");

   c1->Print("pdf/sighad_pip.gif"); 
}

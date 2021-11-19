
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

//void read_shms_leg(){
void read_hcaleff_posAddedRuns(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  c1->SetGrid();

  auto mg = new TMultiGraph("mg","PCAL Efficiency");
  TFile * f1 = new TFile("root/cal_effAug5.root","RECREATE");

  std::string line;

  ///sept 13


  // std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/txtfileYield/fadc_LT_boilingSept13_5367.txt");



  // std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/txtfileYield/fadc_LT_boilingSept13_6429.txt");
  // std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/txtfileYield/fadc_LT_boilingSept13_6459.txt");

  // std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/READ/pcal_eff_posAddedRuns.txt");
  std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/READ/hcal_pip_pim_all.txt");

 //run shms rate curr charge yield_uncorr yield_uncorr_err  yield_corr_lt_boil yield_corr_lt_boil_err yield_corr_lt_boil_fadc yield_corr_lt_boil_fadc_err entries


 vector <int> run; 
 vector <double> runNo;
 vector <double> shmsrate;
 vector <double> hcaleff;
 vector <double> hcaerr;
 vector <double> pcaleff;
 vector <double> pcaerr;
 
  while (std::getline(infile, line)){

    std::istringstream iss(line);
    double a, b, c, d, e, f;
    if (!(iss >> a >> b >> c >> d >> e >>f))
      {
           
	break;
           
      } 
       
    run.push_back(a);
    runNo.push_back(a);
    shmsrate.push_back(b);
    hcaleff.push_back(c);
    hcaerr.push_back(d);
    pcaleff.push_back(e);
    pcaerr.push_back(f);
   


  }
  
  
  
  for (int i =0; i< run.size(); i++)
    {
      cout<< run[i] <<endl;
      // cout << sigmaErr[i]<<endl;//you have to cout each elements , so need i
      
     }

  



  

   auto gr = new TGraphErrors(run.size(), &runNo[0], &hcaleff[0], 0, &hcaerr[0]);
   

  gr->SetName("gr");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(2);
  gr->SetTitle("Yield");
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlue);
  gr->SetFillStyle(0);
  gr->Draw("AP");
  //  gr->Fit("pol0");
  // gr->Fit("pol1");
  mg->Add(gr);
 
  gr->Draw("AP");//grlast->Draw();
  mg->Draw("AP");
 

  mg->Write();//Save as rootfile

 
  mg->SetTitle("Hcal Final Eff (For E/P > 0.7); RunNum;Efficiency");

  mg->GetYaxis()->CenterTitle(true);
  mg->GetXaxis()->CenterTitle(true);
  c1->Print("pdf/hcal_posRuns_addedRoot.gif");

  
}







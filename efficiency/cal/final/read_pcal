
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
void read_pcaleff_neg_pos_fallspring_PCALETRACKNORM_RunNum(){
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

  std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/READ/good_runratehcalpcal_eff_neg.txt");

 //run shms rate curr charge yield_uncorr yield_uncorr_err  yield_corr_lt_boil yield_corr_lt_boil_err yield_corr_lt_boil_fadc yield_corr_lt_boil_fadc_err entries


 vector <int> run; 
 vector <double> runNo;
 vector <double> hcaleff;
 vector <double> hcaerr;
 vector <double> pcaleff;
 vector <double> pcaerr;
  vector <double> rate;

  while (std::getline(infile, line)){

    std::istringstream iss(line);
    double a, b, c, d, e, f;
    if (!(iss >> a >> b >> c >> d >> e >>f))
      {
           
	break;
           
      } 
       
    run.push_back(a);//
    runNo.push_back(a);//
    rate.push_back(b);//
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

  //////do the same for pos runs
  // std::ifstream infile1("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/READ/hcal_pcal_eff_pos_pcaletrack_RATE.txt");
 std::ifstream infile1("/u/group/c-csv/hdbhatt/my_analysis/efficiency/cal/READ/good_runratehcalpcal_eff_pos.txt");

 //run shms rate curr charge yield_uncorr yield_uncorr_err  yield_corr_lt_boil yield_corr_lt_boil_err yield_corr_lt_boil_fadc yield_corr_lt_boil_fadc_err entries
  std::string line1;


  vector <int> run1; //rate
 vector <double> runNo1;
 vector <double> hcaleff1;
 vector <double> hcaerr1;
 vector <double> pcaleff1;
 vector <double> pcaerr1;
  vector <double> rate1;

  while (std::getline(infile1, line1)){

    std::istringstream iss(line1);
    double a1, b1, c1, d1, e1, f1;
    if (!(iss >> a1 >> b1 >> c1 >> d1 >> e1 >>f1))
      {
           
	break;
           
      } 
       
    run1.push_back(a1);//
    runNo1.push_back(a1);//
    rate1.push_back(b1);//
    hcaleff1.push_back(c1);
    hcaerr1.push_back(d1);
    pcaleff1.push_back(e1);
    pcaerr1.push_back(f1);
   


  }
  
  
  
  for (int i =0; i< run1.size(); i++)
    {
      cout<< run1[i] <<endl;
      // cout << sigmaErr[i]<<endl;//you have to cout each elements , so need i
      
     }










  ////



  

  //auto gr = new TGraphErrors(run.size(), &runNo[0], &pcaleff[0], 0, &pcaerr[0]);
  // auto gr = new TGraphErrors(run.size(), &rate[0], &pcaleff[0], 0, &pcaerr[0]);
  // auto gr = new TGraphErrors(runNo.size(), &rate[0], &pcaleff[0], 0, &pcaerr[0]);
  //auto gr = new TGraphErrors(runNo.size(), &runNo[0], &pcaleff[0], 0, &pcaerr[0]);
      auto gr = new TGraphErrors(runNo.size(), &rate[0], &pcaleff[0], 0, &pcaerr[0]);


  gr->SetName("gr");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(2);
  gr->SetTitle("Yield Pi- Fall+Spring");
  gr->SetLineColor(kRed);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kRed);
  gr->SetFillStyle(0);
  //gr->Draw("AP");
  gr->Fit("pol0"); 


  //  auto gr1 = new TGraphErrors(runNo1.size(), &runNo1[0], &pcaleff1[0], 0, &pcaerr1[0]);
    auto gr1 = new TGraphErrors(runNo1.size(), &rate1[0], &pcaleff1[0], 0, &pcaerr1[0]);


  gr1->SetName("gr1");
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(2);
  gr1->SetTitle("Yield Pi+ Fall+Spring");
  gr1->SetLineColor(kBlue);
  gr1->SetLineWidth(2);
  gr1->SetMarkerColor(kBlue);
  gr1->SetFillStyle(0);
  // // gr1->Draw("AP same");
  gr1->Fit("pol0"); 


  //gr->Fit("pol1");
  mg->Add(gr);
  mg->Add(gr1);

  gr->Draw("AP");//grlast->Draw();
  mg->Draw("AP");
   c1->BuildLegend();
  mg->Write();//Save as rootfile

 
  //mg->SetTitle("Pcal Final Eff (Runs Grouped (no Al runs): For pcaletracknorm < 0.8); RunNumber;Efficiency");
  mg->SetTitle("Pcal Final Eff (Runs Grouped (no Al runs): For pcaletracknorm < 0.8); SHMS 3/4 Rate;Efficiency");

  mg->GetYaxis()->CenterTitle(true);
  mg->GetXaxis()->CenterTitle(true);
  mg->GetYaxis()->SetRangeUser(0.935,0.97);
  mg->GetXaxis()->SetRangeUser(0,550);

  c1->Print("pdf/pcal_negRuns_addedRootSpring.gif");

  
}







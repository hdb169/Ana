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
void read_tlt_eff_short(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
  c1->SetGrid();

  auto mg = new TMultiGraph("mg","TLT");
  //TFile * f1 = new TFile("root/cal_effAug5.root","RECREATE");

  std::string line;

  std::ifstream infile("/u/group/c-csv/hdbhatt/my_analysis/livetime/txtfile_livetime/total_livetime_mark.txt");

 //run shms rate curr charge yield_uncorr yield_uncorr_err  yield_corr_lt_boil yield_corr_lt_boil_err yield_corr_lt_boil_fadc yield_corr_lt_boil_fadc_err entries


 vector <int> run; 
 vector <double> runNo;
 vector <double> tlt;
 vector <double> tltErr;
 vector <double> rate;
 vector <double> current;
 
  while (std::getline(infile, line)){

    std::istringstream iss(line);
    double a, b, c,d,e;
    if (!(iss >> a >> b >> c  >>  d  >> e))
      {
           
	break;
           
      } 
       

    run.push_back(a);
    runNo.push_back(a);
    tlt.push_back(b);
    tltErr.push_back(c);
    rate.push_back(d);
    current.push_back(e);
   


  }
  
  cout<<"hi"<<endl;
  
  for (int i =0; i< run.size(); i++)
    {
      cout<< run[i] <<endl;
      // cout << sigmaErr[i]<<endl;//you have to cout each elements , so need i
      //cout<<"hhhi"<<endl;

     }

  



  

   auto gr = new TGraphErrors(run.size(), &rate[0], &tlt[0], 0, &tltErr[0]);
   

  gr->SetName("gr");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(2);
  gr->SetTitle("Yield");
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlue);
  gr->SetFillStyle(0);
  gr->Draw("AP");
  gr->Fit("pol1");
  // gr->Fit("pol1");
  mg->Add(gr);

  gr->Draw("AP");//grlast->Draw();
  mg->Draw("AP");
 

  mg->Write();//Save as rootfile

 
  mg->SetTitle("Total Live Time; SHMS 3/4 Rate (Khz) ;Total Live Time");
  mg->GetYaxis()->SetRangeUser(0.95,1);;

  mg->GetYaxis()->CenterTitle(true);
  mg->GetXaxis()->CenterTitle(true);
c1->Print("pdf/total_lt_finalll.gif");
  
  
}







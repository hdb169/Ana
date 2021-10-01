
//root -l aimple_method_allruns.C
//make a "pdf" directory
//give run list and write number of runs 
#define ROOT_header
#include "TH1F.h"
#include "TH2F.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TDecompLU.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <time.h>
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>
#define NRUNS 22
void simple_method_5367_5377(){

  ofstream txtfile("fadc_live_timeSept2021_kin13_14.txt",ios::app);
  // txtfile <<" Run "<<"\t"<<std::setprecision(5)<<fixed<<"edtm acc. trig"<<"\t"<<"edtm trig"<<"\t"< "rmeas"<<"\t"<< "Live Time"<< "Error"<<endl;
  txtfile <<" Run "<<"\t"<<"LT"<<"\t"<<"LT_err"<<"\t"<<"curr"<<"\t"<<"boiling_fact"<<endl;

  /*  if (RunNumber == 0){
      cout<<"enter a run number:";
      cin >> RunNumber;
      if(RunNumber <= 0)
      return;
      }
  */
  gROOT->SetBatch(kTRUE);
  Int_t runs[NRUNS]={6429,6430,6431,6432,6433,6459,6460,6461,6462,6463,6464,      5367,5368,5369,5370,5371,5372,5373,5374,5375,5376,5377};//
  // Int_t runs[NRUNS]={6281,6282,6284,6285,6286,6287,6288,6289,6290,6291,6292,6293,6294,6295,6296,6297,6298,6299,6300,6301,6302,6304,6305,6306,6307,6308,6309,6310,6311,6312,6313,6314,6315,6316,6317,6318,6322,6323,6325,6326,6327,6328,6329,6331,6332,6334,6335,6336,6337,6338,6339,6340,6341,6342,6343,6344,6345,6346,6347,6348,6349,6350,6351,6352,6353,6354,6355,6356,6357,6358};
  
  gStyle->SetOptStat(111111);
  gStyle->SetErrorX(0);

  for(Int_t r=0; r<NRUNS; r++){
    //  TString filename  = Form("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/fadc/coin_replay_production_%d_-1.root", runs[r]);//6381

    TString filename  = Form("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_%d_-1.root", runs[r]);//6381
    TFile *f = new TFile(filename, "READ");

    // cout<< "Opening Run Num = "<< runs[r] <<endl; 
    
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      exit(-1);
    }

  
    TTree * tt = (TTree *)f->Get("T");
    TTree * ss = (TTree *)f->Get("TSP");
    //  TFile *ff = new TFile("root/livetime_pm.root","RECREATE");   

    double total_scaler1MHztime=0.;
    double total_bcm1charge=0;
    double total_ptrig6scaler=0;
    double total_pedtmscaler=0;
    double total_ptrig1scaler=0;//added

    double previous_scaler1MHztime =0;
    double previous_bcmcharge =0;
    double previous_ptrig6scaler=0;;
    double previous_pedtmscaler=0;
    double previous_ptrig1scaler=0;//addeds

    double total_scaler1MHztime_new=0;
    double total_bcm1charge_new=0;
    double total_ptrig6scaler_new=0;
    double total_pedtmscaler_new=0;
    double total_ptrig1scaler_new=0;//added


    TH1F *hcurrent = new TH1F("current","",100, -10, 100);
    TH1F *hcurrent_bcmcut = new TH1F("hcurrent_bcmcut","",100, -10, 100);
    TH1F *hcurrent_nobcmcut = new TH1F("hcurrent_nobcmcut","",100, -10, 100);

    TH1F *hcharge = new TH1F("hcharge","",100, -10, 15000);
    TH1F *hchargecut = new TH1F("hchargecut","",100, -10, 15000);

    TH1F *htime = new TH1F("htime","",100, -1000, 5000);
    TH1F *htimecut = new TH1F("htimecut","",100, -1000, 5000);




    double data_eventnum,ngcer,pcaletottrack,pcaleprtrack,pcaletotnorm,pdelta,xptar,ytar,pdcntrack,eventtype,phodbetanotrack,phodgoodscinhit,pdctnhit,edtmtdctimeraw,ptrig6tdctimeraw,ptrig2tdctimeraw,pelcleantdctimeraw;

    double scaler_eventnum,bcm1charge,bcm1current,scaler1MHztime,scaler1MHztimecut,bcm1chargecut,s1xscaler,s1yscaler,s2xscaler,s2yscaler,ptrig1scaler,ptrig2scaler,ptrig3scaler,ptrig4scaler,ptrig6scaler,pedtmscaler,pelcleanscaler,pl1acceptscaler;

    double  current_bcmcut, current_nobcmcut;
    tt->SetBranchAddress("g.evnum",&data_eventnum);
    tt->SetBranchAddress("P.ngcer.npeSum",&ngcer); 
    tt->SetBranchAddress("P.cal.etottracknorm",&pcaletottrack);
    tt->SetBranchAddress("P.cal.eprtracknorm",&pcaleprtrack);
    tt->SetBranchAddress("P.cal.etotnorm",&pcaletotnorm);
    tt->SetBranchAddress("P.gtr.dp",&pdelta);
    tt->SetBranchAddress("P.gtr.th",&xptar);
    tt->SetBranchAddress("P.gtr.y",&ytar);
    tt->SetBranchAddress("P.dc.ntrack", &pdcntrack);
    tt->SetBranchAddress("g.evtyp", &eventtype);
    tt->SetBranchAddress("P.hod.betanotrack",&phodbetanotrack);    
    tt->SetBranchAddress("P.hod.goodscinhit",&phodgoodscinhit);
    tt->SetBranchAddress("P.dc.nhit",&pdctnhit);
    tt->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&edtmtdctimeraw);
    tt->SetBranchAddress("T.coin.pTRIG6_ROC2_tdcTimeRaw",&ptrig6tdctimeraw);
    tt->SetBranchAddress("T.coin.pTRIG2_ROC2_tdcTimeRaw",&ptrig2tdctimeraw);
    //tt->SetBranchAddress("T.coin.pEL_CLEAN_ROC2_tdcTimeRaw",&pelcleantdctimeraw);


    ss->SetBranchAddress("evNumber", &scaler_eventnum);
    ss->SetBranchAddress("P.BCM1.scalerCharge", &bcm1charge);
    ss->SetBranchAddress("P.BCM1.scalerCurrent", &bcm1current);
    ss->SetBranchAddress("P.1MHz.scalerTime", &scaler1MHztime);
    ss->SetBranchAddress("P.1MHz.scalerTimeCut",&scaler1MHztimecut);
    ss->SetBranchAddress("P.BCM1.scalerChargeCut",&bcm1chargecut);
    ss->SetBranchAddress("P.S1X.scaler", &s1xscaler);
    ss->SetBranchAddress("P.S1Y.scaler", &s1yscaler);
    ss->SetBranchAddress("P.S2X.scaler", &s2xscaler);
    ss->SetBranchAddress("P.S2Y.scaler", &s2yscaler);
    ss->SetBranchAddress("P.pTRIG1.scaler", &ptrig1scaler);
    ss->SetBranchAddress("P.pTRIG2.scaler", &ptrig2scaler);
    ss->SetBranchAddress("P.pTRIG3.scaler", &ptrig3scaler);
    ss->SetBranchAddress("P.pTRIG4.scaler", &ptrig4scaler);
    ss->SetBranchAddress("P.pTRIG6.scaler", &ptrig6scaler);
    ss->SetBranchAddress("P.EDTM.scaler",&pedtmscaler);
    ss->SetBranchAddress("P.pEL_CLEAN.scaler", &pelcleanscaler);
    ss->SetBranchAddress("P.pL1ACCP.scaler",&pl1acceptscaler);
 

    Long64_t nentriesD = tt->GetEntries();
    // cout<<" Data entries = "<<nentriesD<<"  "<<endl;
    Long64_t nscalerD = ss->GetEntries();
    // cout<<" Scaler entries = "<<nscalerD<<"  "<<endl;

    int ev_flag[nscalerD];
    int scal_evt_num[nscalerD];
  
  
    for (int j = 0; j < nscalerD; j++){
      ss->GetEntry(j);
    
      hcurrent->Fill(bcm1current);
      hcharge->Fill(bcm1charge);
      hchargecut->Fill(bcm1chargecut);
      htime->Fill(scaler1MHztime);
      htimecut->Fill(scaler1MHztimecut);
      current_bcmcut = bcm1chargecut/scaler1MHztimecut;
      current_nobcmcut = bcm1charge/scaler1MHztime;
      hcurrent_bcmcut->Fill(current_bcmcut);//take Integral 
      hcurrent_nobcmcut->Fill(current_nobcmcut);//take Integarl

    }
    // double  current_integral_bcmcut   =  hcurrent_bcmcut->Integral();
    //double  current_integral_nobcmcut =  hcurrent_nobcmcut->Integral();


 
    TCanvas * c1 = new TCanvas ("c1", "c1", 600, 400);
    c1->Divide(4,2);
 
    c1->cd(1);
    hcurrent->Draw();
 
    c1->cd(2);
    hcharge->Draw();
    hcharge->SetTitle(Form("Run Number: %d", runs[r]));
  
    c1->cd(3);
    hchargecut->Draw();
 
    c1->cd(4);
    htime->Draw();
 
    c1->cd(5);
    htimecut->Draw();
 
    c1->cd(6);
    hcurrent_nobcmcut->Draw();
 
    c1->cd(7);
    hcurrent_bcmcut->Draw();
    /////////////////////////////////Main part//////////////////////
    for (int k = 0; k < nscalerD; k++) {
      ss->GetEntry(k);
      // ev_flag[k] = 0;
      scal_evt_num[k] = scaler_eventnum;

      total_scaler1MHztime=scaler1MHztime;
      total_bcm1charge=bcm1charge;
      total_ptrig6scaler=ptrig6scaler;
      total_pedtmscaler=pedtmscaler;

      total_scaler1MHztime_new  =  total_scaler1MHztime_new + ( scaler1MHztime - previous_scaler1MHztime);
      total_bcm1charge_new      =  total_bcm1charge_new + (bcm1charge - previous_bcmcharge);
      total_ptrig6scaler_new    = total_ptrig6scaler_new + (ptrig6scaler - previous_ptrig6scaler);
      total_pedtmscaler_new     = total_pedtmscaler_new + (pedtmscaler - previous_pedtmscaler); 

      previous_scaler1MHztime = scaler1MHztime;
      previous_bcmcharge = bcm1charge;
      previous_ptrig6scaler = ptrig6scaler;
      previous_pedtmscaler = pedtmscaler;

    }


    double ptrig6_rate = total_ptrig6scaler_new/total_scaler1MHztime_new/1000.;// unit KHz
    double pedtm_rate = total_pedtmscaler_new/total_scaler1MHztime_new/1000.;//unit KHz
    double ptrig1_rate = total_ptrig1scaler_new/total_scaler1MHztime_new/1000.;// unit KHz

    //////////////////////data Tree/////////////
    double total_pedtm_trigger_accp = 0.;
    int scal = 0;
    for (int kk=0; kk<nentriesD;  kk++){
      tt->GetEntry(kk);
      if( edtmtdctimeraw > 0) { total_pedtm_trigger_accp++; }  //-------------------Numerator
      if(data_eventnum==scal_evt_num[scal]){scal++;}

    }
 
    double rmeas ;
    double TLT_err;
    double cpuLT_factor;

    double  current_mean_bcmcut   =  hcurrent_bcmcut->GetMean();
    double  current_mean_nobcmcut =  hcurrent_nobcmcut->GetMean();
    double current_factor  = current_mean_nobcmcut/ current_mean_bcmcut;
 
    rmeas = total_pedtm_trigger_accp / total_pedtmscaler_new;
    //cout <<" rmeas " << rmeas << endl;
    //cout<<" current_factor(f) = " <<current_factor<< endl;
    double newlt = (rmeas - ( 1.0 - current_factor))/ current_factor;
    TLT_err = sqrt(total_pedtm_trigger_accp) / total_pedtmscaler_new;
     txtfile<<runs[r]<<"\t\t"<<newlt<<"\t\t"<<TLT_err<<"\t\t"<<current_mean_bcmcut<<endl;

    c1->SaveAs(Form("pdf/current_%d.pdf",runs[r]));
    c1->~TCanvas();
    delete c1;
    cout << " ======================================================== "<<endl;
    cout << ""<<endl;

  }
}

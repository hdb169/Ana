Dec10,2021
All cuts are shown, 
1)current cut of 5 uA
2)hgcer cut
3)hgcer eff
4)acc sub
5)RF and all normal pids
6)calorimeter position cut
7)cal < 0.8 and hcal > 0.8
8)acceptance cuts
9)all eff correction, For hgcer P>3.3, eff = 0.986, P = 3-3.3 =0.982, p<3 = 0.995 (RF)
	A yield table is attached here
  ////////See script//
  
  #include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include<math.h>
using namespace std;
#define NRUNS 629

void mark_hgcer_cut(){
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(1000011);
  gStyle->SetOptFit(11);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.12);
  gROOT->SetBatch("kTRUE");

  ofstream txtfile("txtfile_current_cut/with_hgcer_and_cal_position_.txt",ios::app);


  for(Int_t r = 0; r<NRUNS;r++){

    // Int_t runs[NRUNS]     ={6020,6021,6022,6023,6024};
    //Double_t efficiency[NRUNS] ={0.8521,0.8522,0.8783,0.8483,0.8538};


    Int_t runs[NRUNS]     ={6020,6021,6022,6023,6024,6025,6026,6027,6028,6029,6030,6031,6032,6033,6034,6035,6036,6038,6039,6040,6041,6042,6043,6044,6045,6046,6049,6050,6051,6052,6053,6054,6055,6056,6057,6058,6059,6060,6061,6062,6063,6064,6065,6066,6067,6068,6070,6071,6080,6081,6082,6083,6084,6085,6086,6087,6088,6089,6090,6091,6093,6094,6095,6096,6097,6098,6099,6101,6102,6103,6104,6105,6106,6109,6110,6111,6112,6114,6115,6116,6117,6118,6119,6120,6121,6122,6123,6124,6125,6126,6127,6128,6129,6130,6132,6133,6135,6136,6137,6138,6139,6140,6141,6142,6144,6145,6146,6154,6155,6163,6164,6166,6568,6169,6170,6171,6172,6174,6175,6177,6178,6179,6180,6181,6182,6183,6184,6185,6186,6187,6188,6189,6190,6192,6193,6194,6195,6196,6197,6198,6199,6200,6201,6202,6203,6204,6205,6208,6209,6210,6211,6212,6213,6214,6215,6216,6217,6219,6220,6221,6222,6223,6224,6225,6237,6240,6241,6242,6243,6244,6245,6246,6247,6248,6249,6250,6251,6252,6253,6254,6255,6256,6257,6258,6259,6260,6261,6262,6263,6264,6265,6266,6267,6270,6271,6272,6273,6274,6275,6276,6281,6282,6284,6285,6286,6287,6288,6289,6290,6291,6292,6293,6294,6295,6296,6297,6298,6299,6300,6301,6302,6304,6305,6306,6307,6308,6309,6310,6311,6312,6313,6314,6315,6316,6317,6318,6322,6323,6325,6326,6327,6328,6329,6331,6332,6334,6335,6336,6337,6338,6339,6340,6341,6342,6343,6344,6345,6346,6347,6348,6349,6350,6351,6352,6353,6354,6355,6356,6357,6358,6359,6360,6363,6364,6365,6367,6368,6370,6371,6372,6373,6374,6375,6376,6377,6378,6379,6380,6381,6382,6383,6385,6386,6387,6388,6389,6390,6391,6393,6394,6395,6396,6397,6398,6399,6400,6401,6402,6403,6404,6405,6406,6407,6408,6410,6411,6412,6413,6415,6416,6417,6419,6421,6422,6423,6425,6426,6427,6428,6429,6430,6431,6432,6433,6434,6435,6436,6439,6440,6441,6442,6443,6444,6445,6446,6447,6448,6451,6452,6453,6454,6455,6456,6459,6460,6461,6462,6463,6464,6465,6466,6467,6468,6469,6470,6471,6472,6473,6474,6475,6476,6477,6478,6479,6486,6487,6488,6489,6490,6491,6493,6494,6495,6496,6497,6498,6499,6500,6501,6502,6503,6504,6506,6507,6509,6510,6512,6513,6514,6515,6516,6517,6518,6519,6520,6521,6522,6523,6524,6525,6526,6527,6528,6529,6531,6532,6533,6534,6535,6536,6537,6538,6539,6541,6542,6543,6544,6545,6546,6547,6548,6549,6550,6551,6552,7593,7594,7595,7596,7597,7599,7600,7601,7602,7603,7604,7605,7606,7607,7608,7609,7610,7611,7612,7613,7614,7615,7616,7617,7618,7619,7620,7621,7622,7623,7625,7626,7627,7628,7629,7630,7631,7632,7633,7634,7635,7636,7637,7638,7639,7640,7641,7642,7643,7644,7645,7646,7647,7648,7649,7650,7651,7652,7654,7655,7657,7658,7659,7660,7661,7662,7663,7666,7667,7668,7669,7670,7671,7672,7673,7674,7675,7676,7677,7678,7679,7680,7681,7682,7684,7685,7686,7687,7688,7689,7690,7692,7694,7695,7697,7698,7699,7702,7703,7706,7707,7708,7709,7710,7711,7712,7713,7714,7715,7716,7717,7718,7719,7720,7721,7722,7723,7724,7725,7727,7728,7729,7730,7733,7735,7736,7737,7738,7739,7740,7741,7742,7743,7747,7748,7749,7750,7751,7752,7753,7754,7755,7757,7758,7759,7760,7762,7763,7765,7766,7768,7769,7770,7771,7772,7773,7774,7775,7776,7777,7778,7779,7781,7782,7783,7784,7785,7786,7787,7790,7791,7792,7793,7794,7796,7797,7798,7799,7800,7801,7802,7803,7804,7805,7806,7807,7808,7809,7811,7812,7813,7814,7815,7816,7817,7819,7820};


    Double_t efficiency[NRUNS] ={0.8521,0.8522,0.8783,0.8483,0.8538,0.8538,0.8784,0.8731,0.8731,0.8531,0.8572,0.8575,0.8574,0.8489,0.8488,0.8490,0.8489,0.8573,0.8573,0.8573,0.8573,0.8573,0.8556,0.8556,0.8556,0.8641,0.8558,0.8558,0.8557,0.8559,0.8558,0.8497,0.8496,0.8491,0.8491,0.8491,0.8544,0.8544,0.8498,0.8497,0.8497,0.8497,0.8598,0.8590,0.8802,0.8460,0.8462,0.8462,0.8775,0.8506,0.8481,0.8487,0.8487,0.8487,0.8485,0.8726,0.8531,0.8531,0.8531,0.8547,0.8551,0.8552,0.8549,0.8547,0.8633,0.8633,0.8559,0.8558,0.8557,0.8557,0.8814,0.8834,0.8834,0.8862,0.8862,0.8778,0.8778,0.8778,0.8655,0.8696,0.8770,0.8742,0.8819,0.8819,0.8737,0.8513,0.8541,0.8496,0.8493,0.8550,0.8790,0.8791,0.8739,0.8740,0.8740,0.8921,0.8896,0.8531,0.8531,0.8531,0.8496,0.8475,0.8474,0.8664,0.8659,0.8506,0.8506,0.8757,0.8877,0.8561,0.8597,0.8641,0.8823,0.8809,0.8573,0.8573,0.8770,0.8467,0.8467,0.8507,0.8508,0.8552,0.8552,0.8701,0.8701,0.8609,0.8585,0.8532,0.8537,0.8535,0.8525,0.8525,0.8525,0.8600,0.8600,0.8539,0.8539,0.8811,0.8772,0.8492,0.8492,0.8462,0.8462,0.8504,0.8504,0.8505,0.8544,0.8539,0.8543,0.8543,0.8703,0.8703,0.8582,0.8582,0.8563,0.8563,0.8562,0.8564,0.8563,0.8514,0.8515,0.8515,0.8515,0.8516,0.8719,0.8719,0.8719,0.8828,0.8828,0.8828,0.8558,0.8559,0.8559,0.8430,0.8429,0.8429,0.8812,0.8812,0.8621,0.8620,0.8621,0.8470,0.8470,0.8471,0.8470,0.8469,0.8779,0.8780,0.8484,0.8484,0.8481,0.8481,0.8480,0.8509,0.8509,0.8510,0.8508,0.8718,0.8718,0.8718,0.8492,0.8492,0.8492,0.8756,0.8723,0.8723,0.8841,0.8841,0.8641,0.8641,0.8515,0.8515,0.8830,0.8830,0.8831,0.8709,0.8710,0.8710,0.8612,0.8558,0.8558,0.8809,0.8809,0.8452,0.8450,0.8450,0.8492,0.8491,0.8823,0.8823,0.8634,0.8634,0.8477,0.8477,0.8793,0.8794,0.8456,0.8456,0.8548,0.8548,0.8548,0.8737,0.8737,0.8460,0.8460,0.8524,0.8524,0.8524,0.8523,0.8524,0.8543,0.8545,0.8543,0.8542,0.8542,0.8541,0.8636,0.8636,0.8541,0.8521,0.8522,0.8522,0.8522,0.8769,0.8769,0.8769,0.8467,0.8426,0.8426,0.8425,0.8674,0.8673,0.8844,0.8844,0.8844,0.8567,0.8567,0.8567,0.8835,0.8835,0.8817,0.8817,0.8436,0.8435,0.8435,0.8535,0.8535,0.8533,0.8533,0.8782,0.8782,0.8828,0.8826,0.8532,0.8532,0.8827,0.8798,0.8798,0.8433,0.8432,0.8432,0.8432,0.8530,0.8531,0.8493,0.8493,0.8493,0.8493,0.8493,0.8493,0.8744,0.8744,0.8648,0.8648,0.8544,0.8546,0.8545,0.8514,0.8513,0.8514,0.8511,0.8424,0.8424,0.8424,0.8819,0.8819,0.8819,0.8786,0.8786,0.8445,0.8444,0.8444,0.8566,0.8691,0.8494,0.8537,0.8537,0.8725,0.8723,0.8615,0.8615,0.8553,0.8550,0.8552,0.8550,0.8551,0.8551,0.8628,0.8627,0.8627,0.8834,0.8836,0.8821,0.8449,0.8450,0.8524,0.8576,0.8676,0.8676,0.8482,0.8482,0.8482,0.8795,0.8795,0.8795,0.8745,0.8745,0.8521,0.8522,0.8521,0.8520,0.8521,0.8521,0.8521,0.8658,0.8838,0.8826,0.8529,0.8474,0.8475,0.8475,0.8802,0.8759,0.8553,0.8552,0.8551,0.8552,0.8479,0.8441,0.8814,0.8779,0.8778,0.8487,0.8486,0.8525,0.8525,0.8714,0.8607,0.8541,0.8537,0.8536,0.8537,0.8478,0.8440,0.8440,0.8819,0.8832,0.8832,0.8564,0.8564,0.8564,0.8441,0.8441,0.8441,0.8817,0.8817,0.8786,0.8785,0.8487,0.8487,0.8468,0.8801,0.8757,0.8500,0.8543,0.8545,0.8682,0.8449,0.8827,0.8808,0.8472,0.8473,0.8517,0.8510,0.8768,0.8758,0.8758,0.8758,0.8758,0.8758,0.8845,0.8845,0.8845,0.8845,0.8843,0.8843,0.8835,0.8835,0.8835,0.8688,0.8688,0.8689,0.8542,0.8542,0.8542,0.8542,0.8540,0.8542,0.8819,0.8819,0.8819,0.8785,0.8785,0.8785,0.8785,0.8486,0.8486,0.8486,0.8486,0.8486,0.8486,0.8486,0.8487,0.8486,0.8487,0.8810,0.8811,0.8811,0.8830,0.8830,0.8806,0.8806,0.8748,0.8748,0.8748,0.8749,0.8618,0.8619,0.8618,0.8618,0.8617,0.8569,0.8553,0.8757,0.8757,0.8666,0.8666,0.8666,0.8667,0.8530,0.8531,0.8530,0.8531,0.8531,0.8545,0.8543,0.8543,0.8489,0.8489,0.8812,0.8812,0.8782,0.8782,0.8782,0.8852,0.8487,0.8486,0.8486,0.8487,0.8504,0.8509,0.8509,0.8509,0.8509,0.8504,0.8506,0.8508,0.8723,0.8723,0.8780,0.8779,0.8523,0.8523,0.8522,0.8521,0.8521,0.8521,0.8521,0.8520,0.8717,0.8717,0.8603,0.8603,0.8604,0.8550,0.8551,0.8552,0.8551,0.8549,0.8544,0.8540,0.8812,0.8792,0.8848,0.8836,0.8836,0.8773,0.8773,0.8775,0.8702,0.8702,0.8580,0.8577,0.8581,0.8581,0.8725,0.8767,0.8723,0.8825,0.8825,0.8826,0.8798,0.8798,0.8798,0.8615,0.8615,0.8615,0.8487,0.8487,0.8487,0.8786,0.8847,0.8809,0.8847,0.8849,0.8813,0.8813,0.8813,0.8813,0.8820,0.8786,0.8784,0.8641,0.8641,0.8641,0.8787,0.8787,0.8680,0.8680,0.8528,0.8528,0.8527,0.8525,0.8524,0.8708,0.8708,0.8708,0.8832,0.8832,0.8655,0.8655,0.8506,0.8506,0.8723,0.8816,0.8816,0.8782,0.8781,0.8492,0.8492,0.8492,0.8707,0.8707,0.8810,0.8769,0.8561,0.8561,0.8535,0.8535,0.8536,0.8692,0.8691};


    TH1F* h_pcal_clean = new TH1F("h_pcal_clean","hist_pcal_clean",100, 0,2);
    TH1F* h_pcal_coin = new TH1F("h_pcal_coin","h_pcal_coin",100, 0,2);
    TH1F* h_pcal_acc = new TH1F("h_pcal_acc","h_pcal_acc",100, 0,2);
    TH1F* h_ctime = new TH1F("h_ctime","h_ctime",300,0,100);
    TH1F* h_ctime_coin = new TH1F("h_ctime_coin","h_ctime_coin",300,0,100);
    TH1F* h_ctime_acc = new TH1F("h_ctime_acc","h_ctime_acc",300,0,100);
    TH1F* h_ctime_clean = new TH1F("h_ctime_clean"," h_ctime_clean",300,0,100);
    TH1F* h_mom = new TH1F("h_mom"," h_mom",70, 0, 7);



    TH1F* h_hStartTime = new TH1F("h_hStartTime",";HMS Starttime",200,0,200.);
    TH1F* h_hStartTime_track = new TH1F("h_hStartTime_track",";HMS Starttime",200,0,200.);
    TH1F* h_hFpTime = new TH1F("h_hFpTime",";HMS Fptime",200,0,200.);
    TH1F* h_etotnorm = new TH1F("h_etotnorm"," ; Etot norm",100,0.,2.);
    TH1F* h_npeSum = new TH1F("h_npeSum"," ; Cer Npe",100,0.,20.);
    TH1F* h_ev2 = new TH1F("h_ev2"," ; hEv2",10,0.,10.);
    TH1F* h_goodev2 = new TH1F("h_goodev2"," ; hgoodEv2",10,0.,10.);
    TH1F* h_goodev = new TH1F("h_goodev"," ; Good ev2 with PID cuts",10,0.,10.);
    TH1F* h_goodevTrack = new TH1F("h_goodevTrack"," ; Good ev2 with PID/track cuts",10,0.,10.);


    TString filename  = Form("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_%d.root",runs[r]);
    TFile *f = new TFile(filename, "READ");
    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }
    cout<<runs[r]<<endl;

  
  
    Double_t pionmass   = 0.1395701835; 
    Double_t protonmass = 0.93827231;//GeV/c2

    TTree *tt = (TTree*) f->Get("T");
    TTree *ss = (TTree*) f->Get("TSP");
    //
    Double_t  Scal_evNumber;
    ss->SetBranchAddress("evNumber",&Scal_evNumber);
    Double_t  Scal_BCM1_charge;
    ss->SetBranchAddress("P_BCM1_scalerCharge",&Scal_BCM1_charge);
    Double_t  Scal_BCM1_current;
    ss->SetBranchAddress("P_BCM1_scalerCurrent",&Scal_BCM1_current);
    Double_t  Scal_time;
    ss->SetBranchAddress("P_1MHz_scalerTime",&Scal_time);
    Double_t  Scal_EDTM;
    ss->SetBranchAddress("P_EDTM_scaler",&Scal_EDTM);
    Double_t  Scal_TRIG2;
    ss->SetBranchAddress("P_pTRIG2_scaler",&Scal_TRIG2);
    Double_t  Scal_TRIG3;
    ss->SetBranchAddress("P_pTRIG3_scaler",&Scal_TRIG3);
    Double_t  Scal_TRIG1;
    ss->SetBranchAddress("P_pTRIG1_scaler",&Scal_TRIG1);
    Double_t  Scal_TRIG4;
    ss->SetBranchAddress("P_pTRIG4_scaler",&Scal_TRIG4);
    Double_t  Scal_TRIG5;
    ss->SetBranchAddress("P_pTRIG5_scaler",&Scal_TRIG5);
    Double_t  Scal_TRIG6;
    ss->SetBranchAddress("P_pTRIG6_scaler",&Scal_TRIG6);
  
  
    //loop through scalers
    Int_t nscal_reads=0;
    Int_t nscal_reads_cut=0;
    Double_t prev_read=-1;
    Double_t charge_sum=0;
    Double_t charge_sum_cut=0;
    Double_t prev_charge=0;
    Double_t charge_sum_corr=0;
    Double_t charge_sum_cut_corr=0;
    Double_t prev_charge_corr=0;
    Double_t event_flag[100000];
    Double_t scal_event_number[100000];
    Double_t tot_scal_EDTM=0;
    Double_t tot_scal_cut_EDTM=0;
    Double_t prev_EDTM=0;
    Double_t tot_scal_hEL_CLEAN=0;
    Double_t tot_scal_cut_hEL_CLEAN=0;
    Double_t prev_hEL_CLEAN=0;
    Double_t tot_scal_hEL_REAL=0;
    Double_t tot_scal_cut_hEL_REAL=0;
    Double_t prev_hEL_REAL=0;
    Double_t tot_scal_TRIG2=0;
    Double_t tot_scal_TRIG3=0;
    Double_t prev_TRIG2=0;
    Double_t prev_TRIG3=0;
    Double_t tot_scal_cut_TRIG2=0;
    Double_t tot_scal_cut_TRIG3=0;
    Double_t tot_scal_TRIG1=0;
    Double_t tot_scal_TRIG4=0;
    Double_t prev_TRIG1=0;
    Double_t prev_TRIG4=0;
    Double_t tot_scal_cut_TRIG1=0;
    Double_t tot_scal_cut_TRIG4=0;
    Double_t tot_scal_cut_time=0;
    Double_t tot_scal_TRIG5=0;
    Double_t prev_TRIG5=0;
    Double_t tot_scal_cut_TRIG5=0;
    Double_t tot_scal_TRIG6=0;
    Double_t prev_TRIG6=0;
    Double_t tot_scal_cut_TRIG6=0;
    Double_t threshold_cut=5.;
    Double_t ctmin = 2;
    Double_t ctmax = 2;
    //
    Double_t tot_scal_time=0;
    Double_t prev_time=0;
    //
    Long64_t scal_entries = ss->GetEntries();
    //cout << " scal ent = " << scal_entries << endl;
    Double_t nlast=float(scal_entries);
    TH1F *h_cur_entry = new TH1F("h_cur_entry","; ENtry;current",nlast,0,nlast);
    TH1F *h_cur = new TH1F("h_cur","; Current ;",200,0,100);
    Long64_t data_entries = tt->GetEntries();
    for (int i = 0; i < scal_entries; i++) {
      ss->GetEntry(i);
      h_cur_entry->Fill(float(i),Scal_BCM1_current);
      if (Scal_BCM1_current > 3) h_cur->Fill(Scal_BCM1_current);
    }
   
    Double_t peak_current = h_cur->GetBinCenter(h_cur->GetMaximumBin());
    //cout << " Peak current = " << peak_current  <<" " <<  h_cur->GetMaximumBin() << endl;
    Double_t Scal_BCM1_charge_corr=0;
    for (int i = 0; i < scal_entries; i++) {
      ss->GetEntry(i);
      event_flag[nscal_reads] = 0;
      scal_event_number[nscal_reads] = Scal_evNumber;
      Double_t BCM1_correction=1.;
      if (Scal_BCM1_current >2.) {
	if (Scal_BCM1_current <= 60) {
	  BCM1_correction =1.0 + 0.045* ( log(60.)-log(Scal_BCM1_current))/( log(60.)-log(2.) );
	} else {
	  BCM1_correction =1.0 + 0.010*(Scal_BCM1_current-60)/25.;
	} 
      }
      Scal_BCM1_charge_corr+=Scal_BCM1_current*(Scal_time-prev_time)*BCM1_correction;
      ///cout << Scal_BCM1_charge << " "  << Scal_BCM1_charge_corr << " " << BCM1_correction << endl;
      //if (TMath::Abs(Scal_BCM1_current-peak_current) < threshold_cut) {
      if (TMath::Abs(Scal_BCM1_current) > threshold_cut) {


	event_flag[nscal_reads] = 1;
	tot_scal_cut_time+=(Scal_time-prev_time);
	tot_scal_cut_TRIG2+=(Scal_TRIG2-prev_TRIG2);
	tot_scal_cut_TRIG3+=(Scal_TRIG3-prev_TRIG3);
	tot_scal_cut_TRIG1+=(Scal_TRIG1-prev_TRIG1);
	tot_scal_cut_TRIG4+=(Scal_TRIG4-prev_TRIG4);
	tot_scal_cut_TRIG5+=(Scal_TRIG5-prev_TRIG5);
	tot_scal_cut_TRIG6+=(Scal_TRIG6-prev_TRIG6);

	charge_sum_cut+=(Scal_BCM1_charge-prev_charge);
	charge_sum_cut_corr+=(Scal_BCM1_charge_corr-prev_charge_corr);
	nscal_reads_cut++;
      }
      prev_charge = Scal_BCM1_charge;
      prev_charge_corr = Scal_BCM1_charge_corr;
      prev_time = Scal_time;
      prev_TRIG2 = Scal_TRIG2;
      prev_TRIG3 = Scal_TRIG3;
      prev_TRIG1 = Scal_TRIG1;
      prev_TRIG4 = Scal_TRIG4;
      prev_TRIG5 = Scal_TRIG5;
      prev_TRIG6 = Scal_TRIG6;

      nscal_reads++;

      charge_sum=Scal_BCM1_charge;
      charge_sum_corr=Scal_BCM1_charge_corr;
      tot_scal_TRIG2=Scal_TRIG2;
      tot_scal_TRIG3=Scal_TRIG3;
      tot_scal_TRIG1=Scal_TRIG1;
      tot_scal_TRIG4=Scal_TRIG4;
      tot_scal_TRIG5=Scal_TRIG5;
      tot_scal_TRIG6=Scal_TRIG6;
      tot_scal_time=Scal_time;
    }
    //cout << "nscal_reads_cut " << nscal_reads_cut<< endl;
  

    //
    Double_t gevtyp;
    tt->SetBranchAddress("g_evtyp",&gevtyp);
    Double_t gevnum;
    tt->SetBranchAddress("g_evnum",&gevnum);
    Double_t mom;
    tt->SetBranchAddress("P_gtr_p",&mom);
    Double_t pbeta;
    tt->SetBranchAddress("P_gtr_beta",&pbeta);
    Double_t pdelta;
    tt->SetBranchAddress("P_gtr_dp",&pdelta);
    Double_t pcaletottrack;
    tt->SetBranchAddress("P_cal_etottracknorm",&pcaletottrack);
    Double_t pcaletrack;
    tt->SetBranchAddress("P_cal_etracknorm",&pcaletrack); 
    Double_t hgcer;
    tt->SetBranchAddress("P_hgcer_npeSum",&hgcer);
    Double_t hcaletottrack;
    tt->SetBranchAddress("H_cal_etottracknorm",&hcaletottrack);
    Double_t ctime;
    tt->SetBranchAddress("CTime_ePiCoinTime_ROC2",&ctime);
    double_t hgcer_xAtcer;
    tt->SetBranchAddress("P_hgcer_xAtCer", &hgcer_xAtcer);
    double_t hgcer_yAtcer;
    tt->SetBranchAddress("P_hgcer_yAtCer", &hgcer_yAtcer);
    Double_t track_x_fp;
    tt->SetBranchAddress("P_dc_x_fp", &track_x_fp);
    Double_t track_y_fp;
    tt->SetBranchAddress("P_dc_y_fp", &track_y_fp);
    Double_t track_xp_fp;
    tt->SetBranchAddress("P_dc_xp_fp", &track_xp_fp);
    Double_t track_yp_fp;
    tt->SetBranchAddress("P_dc_yp_fp", &track_yp_fp);
    Double_t dW2;
    tt->SetBranchAddress("H_kin_primary_W2",&dW2);
    Double_t dnu;
    tt->SetBranchAddress("H_kin_primary_omega",&dnu);
    Double_t dpmiss;
    tt->SetBranchAddress("P_kin_secondary_pmiss",&dpmiss);

    //cout<<"good"<<endl;
    Int_t nscal_reads_2=0;
    for (int i = 0; i < data_entries; i++) {
      tt->GetEntry(i);
      //
      if (event_flag[nscal_reads_2]==1) {
	Bool_t pidcut = pcaletottrack<0.8 && hcaletottrack > 0.8;
	if (pidcut){
	  h_ctime->Fill(ctime);
	  h_mom->Fill(mom);
	}
      }//evt flag
      if (gevnum > scal_event_number[nscal_reads_2])  nscal_reads_2++;
    }//entries
    //
    
    //accidental cut
    Double_t momentum = h_mom->GetMean();
    Int_t bin_max = h_ctime->GetMaximumBin();
    Double_t max_value = h_ctime->GetBinCenter(bin_max); 


    Bool_t accL_cut, accR_cut, accidental_cut, ctime_cut, coin_cut,acc_cut, central_hole, right_or_left_of_hole, remove_region, position_cut, common_cuts;
    Double_t xatpreshower, yatpreshower, xatshower, yatshower,xatpreshowerback , yatpreshowerback, xatshowerback, yatshowerback, Epi, zhad, Mx2;
 
    //cout<<"max_val = "<<max_value<<endl;
    Int_t nscal_reads_3=0;
    for (int i = 0; i < data_entries; i++) {
      tt->GetEntry(i);
      if (event_flag[nscal_reads_3]==1) {

	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	accidental_cut = (accR_cut || accL_cut);
	ctime_cut = ctime > (max_value - ctmax) && ctime < (max_value + ctmin);
	coin_cut = ctime_cut && pcaletottrack<0.8 && hcaletottrack > 0.8;
	acc_cut = accidental_cut && pcaletottrack<0.8 && hcaletottrack > 0.8;
	central_hole = (pow(hgcer_yAtcer-1.33, 2) +  pow(hgcer_xAtcer-0.83, 2) >= pow(6.0, 2));//radius = 6
	right_or_left_of_hole = ((hgcer_yAtcer > 1.33 && (hgcer_xAtcer < 0. ||  hgcer_xAtcer > 3.0) ) ||  (hgcer_yAtcer < 1.33 && (hgcer_xAtcer < 0.||  hgcer_xAtcer > 3)));
	remove_region = central_hole && right_or_left_of_hole;//ok
	xatpreshower = track_x_fp + 292.64 * (track_xp_fp);
	yatpreshower = track_y_fp + 292.64 * (track_yp_fp);

	xatshower = track_x_fp + 306.44 * (track_xp_fp);
	yatshower = track_y_fp + 306.44 * (track_yp_fp);

	xatpreshowerback = track_x_fp + 302.64 * (track_xp_fp);
	yatpreshowerback = track_y_fp + 302.64 * (track_yp_fp);

	xatshowerback = track_x_fp + 356.44 * (track_xp_fp);
	yatshowerback = track_y_fp + 356.44 * (track_yp_fp);
	position_cut =  xatshowerback>-60  &&  xatshowerback < 60  && yatshowerback>-60  && yatshowerback < 60 && xatpreshowerback  > -60 && xatpreshowerback  < 60  && yatpreshowerback >-60 && yatpreshowerback < 60;
		
	Epi = sqrt(pow(pionmass,2) + pow(mom,2));
	zhad = Epi/dnu;
	Mx2 = (protonmass + dnu - zhad*dnu) *  (protonmass + dnu - zhad*dnu) - abs(dpmiss)*abs(dpmiss);
	
	Bool_t common_cuts = Mx2 > 2 && dW2 > 4 && position_cut;

	if(mom>=3){
	  if (coin_cut && common_cuts && remove_region){
	    h_pcal_coin->Fill(pcaletottrack); 
	    h_ctime_coin->Fill(ctime);
	  }
	  if (acc_cut && common_cuts && remove_region){
	    h_pcal_acc->Fill(pcaletottrack); 
	    h_ctime_acc->Fill(ctime);
	  }
	}
	if(mom < 3){
	  if (coin_cut && common_cuts ){
	    h_pcal_coin->Fill(pcaletottrack); 
	    h_ctime_coin->Fill(ctime);
	  }
	  if (acc_cut && common_cuts){
	    h_pcal_acc->Fill(pcaletottrack); 
	    h_ctime_acc->Fill(ctime);
	  }
	}
      }//evt flag
      if (gevnum > scal_event_number[nscal_reads_3])  nscal_reads_3++;
    }//entries
 
    //
   
    //acc subtraction just do math
    Double_t coin_integral = h_pcal_coin->Integral(); 
    Double_t acc_integral_4 = h_pcal_acc->Integral(); 
    Double_t acc_integral = acc_integral_4 *(ctmin+ctmax)/16; 
    Double_t clean_integral = coin_integral-acc_integral;

    //cout<<runs[r]<<"\t\t"<<"clean_integral =====>   "<<clean_integral<<endl;
    //cout<<runs[r]<<"\t\t"<<"coin_integral  =====>   "<<coin_integral<<endl;
    //cout<<runs[r]<<"\t\t"<<"acc_integral   =====>   "<<acc_integral<<endl;
   
    //verify these yields by actual subtraction of coin and acc hists
    TH1D *  h_pcal_acc_copy = (TH1D*)h_pcal_acc->Clone();
    h_pcal_acc_copy->Scale(0.25); 
    TH1D *  h_pcal_coin_copy = (TH1D*)h_pcal_coin->Clone();
    TH1D *  h_pcal_acc_only = (TH1D*)h_pcal_acc_copy->Clone();
    h_pcal_clean->Add(h_pcal_coin_copy,h_pcal_acc_only,1.0,-1.0);
    

    TH1D *  h_ctime_acc_copy = (TH1D*)h_ctime_acc->Clone();
    h_ctime_acc_copy->Scale(0.25); 
    TH1D *  h_ctime_coin_copy = (TH1D*)h_ctime_coin->Clone();
    TH1D *  h_ctime_acc_only = (TH1D*)h_ctime_acc_copy->Clone();
    h_ctime_clean->Add(h_ctime_coin_copy,h_ctime_acc_only,1.0,-1.0);
   



    Double_t coin_integral_hist = h_pcal_coin_copy->Integral(); 
    Double_t acc_integral_4_hist = h_pcal_acc_copy->Integral(); 
    Double_t acc_integral_hist = h_pcal_acc_only->Integral();
    Double_t clean_integral_hist =  h_pcal_clean->Integral();
    
    // cout<<runs[r]<<"\t\t"<<"clean_integral =====>   "<<clean_integral_hist<<endl;
    // cout<<runs[r]<<"\t\t"<<"coin_integral  =====>   "<<coin_integral_hist<<endl;
    // cout<<runs[r]<<"\t\t"<<"acc_integral   =====>   "<<acc_integral_hist<<endl;
    // verified that these yields are exactly same  by actual subtraction of coin and acc hists

    Double_t charge_cut5uA_bcmcorr  = charge_sum_cut_corr/1000.0;//mC
    Double_t yield;
    Double_t yield_err;
    //getting correct yield for each run:
    if(momentum >= 3 && momentum < 3.3 ){
      yield = clean_integral/(charge_cut5uA_bcmcorr*efficiency[r] * 0.982);
      yield_err = sqrt(clean_integral)/(charge_cut5uA_bcmcorr*efficiency[r] *0.982 );
    }
    if(momentum >=3.3){
      yield = clean_integral/(charge_cut5uA_bcmcorr*efficiency[r] * 0.986);
      yield_err = sqrt(clean_integral)/(charge_cut5uA_bcmcorr*efficiency[r] * 0.986);
    }
    if(momentum<3){
      yield = clean_integral/(charge_cut5uA_bcmcorr*efficiency[r] * 0.995 );
      yield_err = sqrt(clean_integral)/(charge_cut5uA_bcmcorr*efficiency[r] *0.995);
    }

    ///cout<<runs[r]<<setprecision(4)<<fixed<<"\t\t"<<"curr, charge, yield, yield_err ="<<peak_current<<"\t\t"<<charge_cut5uA_bcmcorr<<"\t\t"<<yield<<"\t\t"<<yield_err<<endl;
    
    txtfile<<runs[r]<<setprecision(6)<<fixed<<"\t\t"<<peak_current<<"\t\t"<<charge_cut5uA_bcmcorr<<"\t\t"<<yield<<"\t\t"<<yield_err<<endl;

    TCanvas * cc = new TCanvas ("cc", "cc", 1200, 800);
    cc->Divide(3,3);

    cc->cd(1);
    h_cur_entry->Draw();
    h_cur_entry->SetTitle(Form("current %d",runs[r]));
    h_cur_entry->SetMarkerStyle(20);
    h_cur_entry->SetLineWidth(2);


    cc->cd(2);gPad->SetLogy();
    h_cur->Draw();
    h_cur->SetLineWidth(2);

    cc->cd(3);
    h_pcal_coin->Draw();
    h_pcal_coin->SetLineWidth(2);
    h_pcal_acc->Draw("sames");
    h_pcal_acc->SetLineWidth(2);
    h_pcal_acc->SetLineColor(kRed);
    h_pcal_coin->SetTitle(Form("shms cal %d",runs[r]));

   
    cc->cd(4);
    h_ctime->Draw();
    h_ctime->SetLineWidth(2);
    h_ctime_coin->Draw("sames");
    h_ctime_coin->SetLineWidth(2);
    h_ctime_coin->SetLineColor(kGreen);
    h_ctime_acc->Draw("sames");
    h_ctime_acc->SetLineWidth(2);
    h_ctime_acc->SetLineColor(kRed);

    cc->cd(5);
    h_ctime_clean->Draw("hist");
    h_ctime_clean->SetLineWidth(2);


    cc->cd(6);
    h_pcal_clean->Draw("hist");
    h_pcal_clean->SetLineWidth(2);

    cc->cd(7);
    h_mom->Draw("hist");
    h_mom->SetLineWidth(2);


    cc->SaveAs(Form("pdfdec10/base_%d.pdf", runs[r]));

    
  }
}








/*
  Int_t nev2 = h_ev2->Integral();
  Int_t good_ev2 = h_goodev2->Integral();
  Double_t good_ev2_err = TMath::Sqrt(good_ev2);
  Int_t nEDTM = h_EDTM_CUT->Integral();
  Int_t nEDTM2 = h_EDTM_CUT2->Integral();
  Double_t clt = (good_ev2)/(tot_scal_cut_TRIG2);
  Double_t clt_err = sqrt(tot_scal_cut_TRIG2-good_ev2)/tot_scal_cut_TRIG2;
  Double_t calc_treff= float(h_hStartTime_track->Integral())/float(h_hStartTime->Integral()) ;
  Double_t lt=  nEDTM/tot_scal_cut_EDTM;
  Double_t lt_err = sqrt(tot_scal_cut_EDTM-nEDTM)/tot_scal_cut_EDTM;
  Double_t good_ev = float(h_goodev->Integral())/clt;
  Double_t good_ev_err = TMath::Sqrt(h_goodev->Integral())/clt;
  Double_t good_evTrack = float(h_goodevTrack->Integral())/clt/calc_treff;
  Double_t good_evTrack_err = TMath::Sqrt(h_goodevTrack->Integral())/clt/calc_treff;
  //
  cout << nEDTM << " " << nEDTM2 << " " << tot_scal_cut_EDTM<< " EDTM rate = " << tot_scal_cut_EDTM/tot_scal_cut_time << endl;
  //
  Double_t err_hEL_CLEAN = 1./TMath::Sqrt(tot_scal_cut_hEL_CLEAN);
  Double_t err_hEL_REAL = 1./TMath::Sqrt(tot_scal_cut_hEL_REAL);
  Double_t err_trig2 = 1./TMath::Sqrt(tot_scal_cut_TRIG2);
  Double_t err_trig3 = 1./TMath::Sqrt(tot_scal_cut_TRIG3);
  Double_t err_trig1 = 1./TMath::Sqrt(tot_scal_cut_TRIG1);
  Double_t err_trig4 = 1./TMath::Sqrt(tot_scal_cut_TRIG4);
  Double_t err_trig5 = 1./TMath::Sqrt(tot_scal_cut_TRIG5);
  Double_t err_trig6 = 1./TMath::Sqrt(tot_scal_cut_TRIG6);
  cout << " data " << endl;
  cout << nrun << " "<< charge_sum_cut/tot_scal_cut_time  << " "<< charge_sum_cut_corr/tot_scal_cut_time << " " << clt << " " << clt_err<< " " << lt<< " " << lt_err  << " " << calc_treff << " " << good_ev2/tot_scal_cut_time << " " << good_ev/charge_sum_cut << " " <<  good_ev_err/charge_sum_cut << " " << good_evTrack/charge_sum_cut << " " <<  good_evTrack_err/charge_sum_cut << " " << tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << err_hEL_CLEAN*tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << tot_scal_cut_hEL_REAL/charge_sum_cut << " " << err_hEL_REAL*tot_scal_cut_hEL_REAL/charge_sum_cut << " " <<tot_scal_cut_hEL_REAL/tot_scal_cut_time<< endl;
  cout << " Scalers " << endl;
  cout << nrun << " "<< charge_sum_cut/tot_scal_cut_time<< " "<< charge_sum_cut_corr/tot_scal_cut_time << " " << tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << err_hEL_CLEAN*tot_scal_cut_hEL_CLEAN/charge_sum_cut << " " << tot_scal_cut_hEL_REAL/charge_sum_cut << " " << err_hEL_REAL*tot_scal_cut_hEL_REAL/charge_sum_cut << " " <<tot_scal_cut_hEL_CLEAN/tot_scal_cut_time << " " <<tot_scal_cut_hEL_REAL/tot_scal_cut_time  << endl;
  cout <<  nrun << " "<<tot_scal_cut_TRIG1/tot_scal_cut_time << endl;
*/
//
//  }
//}

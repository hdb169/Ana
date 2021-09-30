//1) This macro will calculate the tracking efficiency of one or more shms coincidence runs as well as singles. But the cuts for electron selection has to be changed. For pion selcetion  pcaletotnorm>0.05 && pcaletotnorm<0.5 where as for electron selection (singles), pcaletotnorm>0.7 && pcaletotnorm<1.4
//2) For, Coin Runs, yield Y = Counts/ (Q* corrected_efficiency), where
//corrected efficiency = good counts/ [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//3) But for singles, Y =  Counts *ps1_factor / [Q(mc)* tr eff * 3/4 shms eff * cpu LT * elec_LT (all< = 1)].
//4) The tracking efficiency is printed in the txtfile.


///Note, this is all good, but acc subtraction is not done, yet htrack, ptrack ef are > 99.5 for (5367-5377)
///needs scaler analysis

#include "TH1F.h"
#include <TH2.h>
#include <TCanvas.h>
#include <TObject.h>




//no calcut





 #define NRUNS 11//500 
void tracking_Mult(){
  // gErrorIgnoreLevel= kError;
  // gROOT->SetBatch(kTRUE);//kFALSE =0, kTRUE =1, kTRUE not  will display the plot, kFALSE will .
  //Int_t runs[NRUNS] ={6065,6066, 6068, 6070, 6071, 6073, 6081, 6082, 6083, 6088, 6089, 6090, 6104, 6105, 6106, 6111, 6112, 6114, 6237, 6240, 6241, 6245, 6246,6247, 6248, 6249, 6250, 6253, 6254, 6255, 6285, 6286, 6287, 6290, 6291, 6451, 6452, 6453, 6459, 6460, 6461, 6524, 6525, 6526, 6527, 6528, 6529, 6545, 6548, 6549, 7593, 7594, 7595, 7596, 7597, 7671 , 7672, 7729, 7730, 7733, 7735, 7736, 7776, 7796, 7797};//D2 > 3Gev
  Int_t runs[NRUNS]     ={5367, 5368, 5369, 5370, 5371, 5372, 5373, 5374, 5375, 5376, 5377};  

  //Int_t runs[NRUNS] = {6200};//  { 6509, 6510, 6512, 6513, 6514, 6515, 6516, 6517, 6518, 6519, 6520, 6521, 6522, 6523, 6524, 6525, 6526, 6527, 6528, 6529, 6531, 6532, 6533, 6534, 6535, 6536, 6537, 6538, 6539, 6541, 6542, 6543, 6544, 6545, 6546, 6547, 6548, 6549, 6550, 6551, 6552};
  gStyle->SetOptStat(1000011);

  TFile *f;
  TTree *tt;
  for(Int_t i=0; i<NRUNS; i++){

//    f=new TFile(Form("/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/ROOTfiles/peter_tracking_param/coin_replay_production_%d_-1.root", runs[i]),"read");
    // f=new TFile(Form("/home/hdbhatt/ROOTfiles/coin_replay_production_%d_-1.root", runs[i]),"read");
    // f=new TFile(Form("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/alleff/coin_replay_production_%d_-1.root", runs[i]),"read");
     f=new TFile(Form("/v/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/fadc/coin_replay_production_%d_-1.root", runs[i]),"read");

    //cout<< "Opening Run Num = "<< runs[i] <<endl; 

    if ((!f) || (f->IsZombie())){
      cout << "No file found or Zombie file" << endl;
      continue;
    }

    tt=(TTree *)f->Get("T");
   

    Double_t pionMass = 0.1395701835;   

    Double_t pT2tdcMult, pcaletot,pcaletotnorm,pcaletracknorm,pbeta,hbeta,pdelta,hdelta,pcaletottracknorm,hcaletot,pcaleprtracknorm,hcalepr,paeronpe,hcernpe,phg,W,Q2,xbj,ctime,E_pi,z_had,z_had_all,pkinomega,shmsP,hmsP,hhodstarttime,phodstarttime,hdipole, pdipole,pgoodscinhit,hgoodscinhit,pbetanotrack,hbetanotrack,pdcntrack,hdcntrack,hcaletotnorm,gevnum,rawctime,rawctime1,pTRIG1_ROC2_timeraw,pTRIG4_ROC2_timeraw,   pstarttime,hstarttime ;
 
    
    TH1D *h_caletotnorm_didshms     = new TH1D("h_caletotnorm_didshms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_shouldshms  = new TH1D("h_caletotnorm_shouldshms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_didhms     = new TH1D("h_caletotnorm_didhms","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_shouldhms  = new TH1D("h_caletotnorm_shouldhms","", 100, 0.001, 2);                                      
   
    TH1D *h_caletotnorm_didshms_nodelta     = new TH1D("h_caletotnorm_didshms_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_caletotnorm_didhms_nodelta     = new TH1D("h_caletotnorm_didhms_nodelta","", 100, 0.001, 2);                                      
    TH1D *hctimeRaw= new TH1D("hctimeRaw","", 100, 20, 40);
    TH1D *h_rawct_ctcut= new TH1D("h_rawct_ctcut","", 100, 20, 40);
    TH1D *h_rawctALL= new TH1D("h_rawctALL","", 100, 20, 40);
    tt->SetBranchAddress("T.coin.pT2_tdcMultiplicity",&pT2tdcMult);

    tt->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime",&pTRIG1_ROC2_timeraw);
    tt->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTime",&pTRIG4_ROC2_timeraw);
    tt->SetBranchAddress("P.hod.starttime",&pstarttime);
    tt->SetBranchAddress("H.hod.starttime",&hstarttime);
    tt->SetBranchAddress("P.gtr.p", &shmsP); 
    tt->SetBranchAddress("H.gtr.p", &hmsP); 
    tt->SetBranchAddress("P.gtr.beta", &pbeta);                                                                       
    tt->SetBranchAddress("H.gtr.beta", &hbeta); 
    tt->SetBranchAddress("H.gtr.dp", &hdelta);                                                                            
    tt->SetBranchAddress("P.gtr.dp", &pdelta);                                                                                
    tt->SetBranchAddress("P.cal.eprtracknorm", &pcaleprtracknorm);                                                                    
    tt->SetBranchAddress("P.cal.etottracknorm", &pcaletottracknorm);                                                                  
    tt->SetBranchAddress("P.hgcer.npeSum", &phg);
    tt->SetBranchAddress("P.aero.npeSum", &paeronpe);                                          
    tt->SetBranchAddress("H.cal.eprtracknorm", &hcalepr);  
    tt->SetBranchAddress("P.cal.etracknorm", &pcaletracknorm); 
    tt->SetBranchAddress("H.cal.etottracknorm", &hcaletot);                                          
    tt->SetBranchAddress("H.cer.npeSum", &hcernpe);    
    tt->SetBranchAddress("CTime.ePiCoinTime_ROC2", &ctime);
    tt->SetBranchAddress("H.hod.goodstarttime", &hhodstarttime);
    tt->SetBranchAddress("P.hod.goodstarttime",&phodstarttime);
    tt->SetBranchAddress("P.dc.InsideDipoleExit",&pdipole);
    tt->SetBranchAddress("H.dc.InsideDipoleExit",&hdipole);
//    tt->SetBranchAddress("P.cal.etot",&pcaletot);
    tt->SetBranchAddress("P.cal.etotnorm",&pcaletotnorm);
    tt->SetBranchAddress("H.cal.etotnorm",&hcaletotnorm);
    tt->SetBranchAddress("P.hod.goodscinhit",&pgoodscinhit);
    tt->SetBranchAddress("H.hod.goodscinhit",&hgoodscinhit);
    tt->SetBranchAddress("P.dc.ntrack",&pdcntrack);
    tt->SetBranchAddress("H.dc.ntrack",&hdcntrack);
    tt->SetBranchAddress("P.hod.betanotrack",&pbetanotrack);
    tt->SetBranchAddress("H.hod.betanotrack",&hbetanotrack);
  //  tt->SetBranchAddress("CTime.CoinTime_RAW_ROC2",&rawctime);
    tt->SetBranchAddress("g.evnum",&gevnum);
    Double_t ctmin = 1.5;//1.5
    Double_t ctmax = 1.5;//1.5
    //gStyle->SetOptStat(0);

    Bool_t ctime_cut, acc_cut, accR_cut, accL_cut,data_cut,pid_cut, pion_cut,should_cutshms,did_cutshms,did_cut1,should_cut1,hms_cut,delta_cut, should_cuthms, did_cuthms, did_cuthms_nodelta, did_cutshms_nodelta,raw_cut, rawct_cut;

    Bool_t should_noct,did_shms_noct_nodelta,did_shms_noct_delta, should_ct,did_shms_ct_nodelta, did_shms_ct_delta,did_hms_noct_nodelta, did_hms_noct_delta,did_hms_ct_nodelta, did_hms_ct_delta; 

    TH1D *h_did_shms_noct_nodelta      = new TH1D("h_did_shms_noct_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_did_shms_noct_delta      = new TH1D("h_did_shms_noct_delta","", 100, 0.001, 2);                                      
    TH1D *h_should_noct      = new TH1D("h_should_noct","", 100, 0.001, 2);                                      
    TH1D *h_did_shms_ct_nodelta      = new TH1D("h_did_shms_ct_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_did_shms_ct_delta      = new TH1D("h_did_shms_ct_delta","", 100, 0.001, 2);                                      
    TH1D *h_should_ct      = new TH1D("h_should_ct","", 100, 0.001, 2);                                      
    TH1D *h_did_hms_noct_nodelta      = new TH1D("h_did_hms_noct_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_did_hms_noct_delta      = new TH1D("h_did_hms_noct_delta","", 100, 0.001, 2);                                      
    TH1D *h_did_hms_ct_nodelta      = new TH1D("h_did_hms_ct_nodelta","", 100, 0.001, 2);                                      
    TH1D *h_did_hms_ct_delta      = new TH1D("h_did_hms_ct_delta","", 100, 0.001, 2);                                      
    TH1D *h_shmsP      = new TH1D("h_shmsP","", 100, 0.1, 7);                                      


    
    
    Long64_t nentriesD = tt->GetEntries();

    //cout<<"Total Entries = "<<nentriesD<<endl;
#include "scalar_analysis.h"


    //=========================raw coin time==========START
    Int_t nscaler_reads_acc=0;

    for (int k=0; k<nentriesD;  k++){
      //---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(k);

      if (event_flag[nscaler_reads_acc]==1) {
	
	raw_cut  = paeronpe>4&&phg>0.5&&hcernpe>2;
	rawctime = (pTRIG1_ROC2_timeraw +  pstarttime) - (pTRIG4_ROC2_timeraw + hstarttime);//raw coin Time for peak finding Mark Jones

      
	if (raw_cut){
	  hctimeRaw->Fill(rawctime);
	  h_shmsP->Fill(shmsP);
	}  
	 
      }
      
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;
    }

 
    Int_t bin_max = hctimeRaw->GetMaximumBin();
    Double_t max_value = hctimeRaw->GetBinCenter(bin_max);
    double centralP =  h_shmsP->GetMean();
    // cout<<runs[i]<<"\t"<<centralP<<endl;

    // TCanvas *c = new TCanvas ("c","",1200,800);
    //h_shmsP->Draw();
    
    //==========================raw coin time =============end
    Int_t nscaler_reads=0;

    
    for (int kk=0; kk<nentriesD;  kk++)//============================================>evts
      {

	tt->GetEntry(kk);
	if (event_flag[nscaler_reads]==1) {

	 
	  rawctime1 = (pTRIG1_ROC2_timeraw +  pstarttime) - (pTRIG4_ROC2_timeraw + hstarttime);//raw coin Time for cut 
	  rawct_cut = rawctime1 > (max_value - ctmin) && rawctime1 < (max_value + ctmax);
	  hms_cut = hgoodscinhit==1 &&hcaletotnorm>0.8 && hhodstarttime==1 && hcernpe>0 &&hbetanotrack>0.5&&hbetanotrack<1.5 &&pT2tdcMult<5 ;// Mult cut
	  //should_noct =  pgoodscinhit==1 && pbetanotrack > 0.5 && pbetanotrack<1.5  &&    pcaletotnorm>0.15  && phodstarttime==1  && paeronpe>4  && hms_cut &&phg > 0.5;
      
	  if (centralP<=2.95){should_noct =  pgoodscinhit==1 && pbetanotrack > 0.5 && pbetanotrack<1.5  &&    pcaletotnorm>0.15  && phodstarttime==1  && paeronpe>4  && hms_cut;}
	  if (centralP>2.95){should_noct =  pgoodscinhit==1 && pbetanotrack > 0.5 && pbetanotrack<1.5  &&    pcaletotnorm>0.15  && phodstarttime==1 && phg > 0.5 && paeronpe>4  && hms_cut ;};
	  
	  //here we have two shoulds one without raw ct and the other with rawct
	  did_shms_noct_nodelta =  should_noct && pdcntrack>0;
	  did_shms_noct_delta =  should_noct &&pdelta>-100&&pdelta<100 &&  pdcntrack>0;

	  should_ct = should_noct &&  rawct_cut ;
	  did_shms_ct_nodelta = should_ct && pdcntrack>0;
	  did_shms_ct_delta =  should_ct &&pdelta>-100&&pdelta<100 &&  pdcntrack>0;

	  did_hms_noct_nodelta =  should_noct && hdcntrack>0;
	  did_hms_noct_delta =  should_noct &&hdelta>-100&&hdelta<100  &&  hdcntrack>0;
	  did_hms_ct_nodelta = should_ct && hdcntrack>0;
	  did_hms_ct_delta =  should_ct &&hdelta>-100&&hdelta<100 &&  hdcntrack>0;


	  if(did_hms_noct_delta && did_shms_noct_delta ){h_rawctALL->Fill(rawctime1);}//all raw time
	  if( did_hms_noct_delta && did_shms_noct_delta && rawct_cut){h_rawct_ctcut->Fill(rawctime1);}//peak of raw time
	  //Fill hist SHMS
	  if(did_shms_noct_nodelta){h_did_shms_noct_nodelta->Fill(pcaletotnorm);}//no ct no delta did
	  if(did_shms_noct_delta){h_did_shms_noct_delta->Fill(pcaletotnorm);}//no ct but delta
	  if(should_noct){h_should_noct->Fill(pcaletotnorm);}//no ct should----------------------->for hms and shms

	  if(did_shms_ct_nodelta){h_did_shms_ct_nodelta->Fill(pcaletotnorm);}// ct no delta did
	  if(did_shms_ct_delta){h_did_shms_ct_delta->Fill(pcaletotnorm);}//ct delta
	  if(should_ct){h_should_ct->Fill(pcaletotnorm);}//ct should----------------------->for hms and shms


	  //HMS 
	  if(did_hms_noct_nodelta){h_did_hms_noct_nodelta->Fill(hcaletotnorm);}//no ct no delta did
	  if(did_hms_noct_delta){h_did_hms_noct_delta->Fill(hcaletotnorm);}//no ct but delta
	  if(did_hms_ct_nodelta){h_did_hms_ct_nodelta->Fill(hcaletotnorm);}// ct no delta did
	  if(did_hms_ct_delta){h_did_hms_ct_delta->Fill(hcaletotnorm);}//ct delta
	   
	  
	  
	}//event flag
	if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;
      }//nentries

   

    TCanvas *c1 = new TCanvas("c1", "Tracking Eff",1200,800); 

    // cout<<runs[i]<<"  "<<PTRIG1_Rate<<endl;
    c1->Divide(4,3);

    c1->cd(1);
    h_did_shms_noct_nodelta->Draw();
    h_did_shms_noct_nodelta->SetLineWidth(2);
    h_did_shms_noct_nodelta->SetLineColor(kRed);
    h_did_shms_noct_nodelta->GetXaxis()->CenterTitle();
    h_did_shms_noct_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_did_shms_noct_nodelta->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_did_shms_noct_nodelta->GetYaxis()->SetTitle("Entries");
    h_did_shms_noct_nodelta->SetTitle(Form("DID SHMS NO CT CUT and  NO DELTA CUT %d",runs[i]));
    
    c1->cd(2);

    h_did_shms_noct_delta->Draw();
    h_did_shms_noct_delta->SetLineWidth(2);
    h_did_shms_noct_delta->SetLineColor(kRed);
    h_did_shms_noct_delta->GetXaxis()->CenterTitle();
    h_did_shms_noct_delta->GetXaxis()->SetTitleOffset(1.2);
    h_did_shms_noct_delta->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_did_shms_noct_delta->GetYaxis()->SetTitle("Entries");
    h_did_shms_noct_delta->SetTitle("DID SHMS NO CT CUT but DELTA CUT");


    c1->cd(3);
    h_did_shms_ct_nodelta->Draw();
    h_did_shms_ct_nodelta->SetLineWidth(2);
    h_did_shms_ct_nodelta->SetLineColor(kRed);
    h_did_shms_ct_nodelta->GetXaxis()->CenterTitle();
    h_did_shms_ct_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_did_shms_ct_nodelta->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_did_shms_ct_nodelta->GetYaxis()->SetTitle("Entries");
    h_did_shms_ct_nodelta->SetTitle("DID SHMS  CT CUT NO DELTA CUT");
    
    c1->cd(4);
    h_did_shms_ct_delta->Draw();
    h_did_shms_ct_delta->SetLineWidth(2);
    h_did_shms_ct_delta->SetLineColor(kRed);
    h_did_shms_ct_delta->GetXaxis()->CenterTitle();
    h_did_shms_ct_delta->GetXaxis()->SetTitleOffset(1.2);
    h_did_shms_ct_delta->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_did_shms_ct_delta->GetYaxis()->SetTitle("Entries");
    h_did_shms_ct_delta->SetTitle("DID SHMS CT CUT and DELTA CUT");


    c1->cd(5);
    h_did_hms_noct_nodelta->Draw();
    h_did_hms_noct_nodelta->SetLineWidth(2);
    h_did_hms_noct_nodelta->SetLineColor(kRed);
    h_did_hms_noct_nodelta->GetXaxis()->CenterTitle();
    h_did_hms_noct_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_did_hms_noct_nodelta->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_did_hms_noct_nodelta->GetYaxis()->SetTitle("Entries");
    h_did_hms_noct_nodelta->SetTitle("DID HMS NO CT CUT and  NO DELTA CUT");
    
    c1->cd(6);

    h_did_hms_noct_delta->Draw();
    h_did_hms_noct_delta->SetLineWidth(2);
    h_did_hms_noct_delta->SetLineColor(kRed);
    h_did_hms_noct_delta->GetXaxis()->CenterTitle();
    h_did_hms_noct_delta->GetXaxis()->SetTitleOffset(1.2);
    h_did_hms_noct_delta->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_did_hms_noct_delta->GetYaxis()->SetTitle("Entries");
    h_did_hms_noct_delta->SetTitle("DID HMS NO CT CUT but DELTA CUT");


    c1->cd(7);
    h_did_hms_ct_nodelta->Draw();
    h_did_hms_ct_nodelta->SetLineWidth(2);
    h_did_hms_ct_nodelta->SetLineColor(kRed);
    h_did_hms_ct_nodelta->GetXaxis()->CenterTitle();
    h_did_hms_ct_nodelta->GetXaxis()->SetTitleOffset(1.2);
    h_did_hms_ct_nodelta->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_did_hms_ct_nodelta->GetYaxis()->SetTitle("Entries");
    h_did_hms_ct_nodelta->SetTitle("DID HMS  CT CUT NO DELTA CUT");
    
    c1->cd(8);
    h_did_hms_ct_delta->Draw();
    h_did_hms_ct_delta->SetLineWidth(2);
    h_did_hms_ct_delta->SetLineColor(kRed);
    h_did_hms_ct_delta->GetXaxis()->CenterTitle();
    h_did_hms_ct_delta->GetXaxis()->SetTitleOffset(1.2);
    h_did_hms_ct_delta->GetXaxis()->SetTitle("H.cal.etotnorm");
    h_did_hms_ct_delta->GetYaxis()->SetTitle("Entries");
    h_did_hms_ct_delta->SetTitle("DID HMS CT CUT and DELTA CUT");
   


    c1->cd(9);
    h_should_noct->Draw();
    h_should_noct->SetLineWidth(2);
    h_should_noct->SetLineColor(kRed);
    h_should_noct->GetXaxis()->CenterTitle();
    h_should_noct->GetXaxis()->SetTitleOffset(1.2);
    h_should_noct->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_should_noct->GetYaxis()->SetTitle("Entries");
    h_should_noct->SetTitle("SHOULD HMS and SHMS NO  CT CUT");
    
    c1->cd(10);
    h_should_ct->Draw();
    h_should_ct->SetLineWidth(2);
    h_should_ct->SetLineColor(kRed);
    h_should_ct->GetXaxis()->CenterTitle();
    h_should_ct->GetXaxis()->SetTitleOffset(1.2);
    h_should_ct->GetXaxis()->SetTitle("P.cal.etotnorm");
    h_should_ct->GetYaxis()->SetTitle("Entries");
    h_should_ct->SetTitle("SHOULD HMS and SHMS with CT CUT");
   
  
    c1->cd(11);
    h_rawctALL->Draw("");
    h_rawctALL->SetLineWidth(2);
    h_rawct_ctcut->Draw("sames");
    h_rawct_ctcut->SetLineWidth(2);
    h_rawct_ctcut->SetLineColor(kRed);
    h_rawctALL->GetXaxis()->SetTitle("RAW COIN TIME (ns) ");
    c1->SaveAs(Form("pdf_hit35/tracking_shms_%d.pdf",runs[i]));


    // double int_did_shms_noct_nodelta = h_did_shms_noct_nodelta->Integral(h_did_shms_noct_nodelta->FindBin(0),h_did_shms_noct_nodelta->FindBin(2));//this integral=entries
    double ent_did_shms_noct_nodelta = h_did_shms_noct_nodelta->GetEntries();
    double ent_did_shms_noct_delta = h_did_shms_noct_delta->GetEntries();
    double ent_did_shms_ct_nodelta = h_did_shms_ct_nodelta->GetEntries();
    double ent_did_shms_ct_delta = h_did_shms_ct_delta->GetEntries();

    double ent_did_hms_noct_nodelta = h_did_hms_noct_nodelta->GetEntries();
    double ent_did_hms_noct_delta = h_did_hms_noct_delta->GetEntries();
    double ent_did_hms_ct_nodelta = h_did_hms_ct_nodelta->GetEntries();
    double ent_did_hms_ct_delta = h_did_hms_ct_delta->GetEntries();

    double ent_should_hms_shms_noct = h_should_noct->GetEntries();
    double ent_should_hms_shms_ct = h_should_ct->GetEntries();
    //eff shms

    double treff_shms_noct_nodelta= ent_did_shms_noct_nodelta/ent_should_hms_shms_noct; 
    double treff_shms_noct_nodelta_err= (1/ent_should_hms_shms_noct) * sqrt(ent_did_shms_noct_nodelta*(1-treff_shms_noct_nodelta));

    double treff_shms_noct_delta= ent_did_shms_noct_delta/ent_should_hms_shms_noct; 
    double treff_shms_noct_delta_err= (1/ent_should_hms_shms_noct) * sqrt(ent_did_shms_noct_delta*(1-treff_shms_noct_delta));

    double treff_shms_ct_nodelta= ent_did_shms_ct_nodelta/ent_should_hms_shms_ct; 
    double treff_shms_ct_nodelta_err= (1/ent_should_hms_shms_ct) * sqrt(ent_did_shms_ct_nodelta*(1-treff_shms_ct_nodelta));
    
    double treff_shms_ct_delta= ent_did_shms_ct_delta/ent_should_hms_shms_ct; 
    double treff_shms_ct_delta_err= (1/ent_should_hms_shms_ct) * sqrt(ent_did_shms_ct_delta*(1-treff_shms_ct_delta));

    //hms

    double treff_hms_noct_nodelta= ent_did_hms_noct_nodelta/ent_should_hms_shms_noct; 
    double treff_hms_noct_nodelta_err= (1/ent_should_hms_shms_noct) * sqrt(ent_did_hms_noct_nodelta*(1-treff_hms_noct_nodelta));

    double treff_hms_noct_delta= ent_did_hms_noct_delta/ent_should_hms_shms_noct; 
    double treff_hms_noct_delta_err= (1/ent_should_hms_shms_noct) * sqrt(ent_did_hms_noct_delta*(1-treff_hms_noct_delta));

    double treff_hms_ct_nodelta= ent_did_hms_ct_nodelta/ent_should_hms_shms_ct; 
    double treff_hms_ct_nodelta_err= (1/ent_should_hms_shms_ct) * sqrt(ent_did_hms_ct_nodelta*(1-treff_hms_ct_nodelta));
    
    double treff_hms_ct_delta= ent_did_hms_ct_delta/ent_should_hms_shms_ct; 
    double treff_hms_ct_delta_err= (1/ent_should_hms_shms_ct) * sqrt(ent_did_hms_ct_delta*(1-treff_hms_ct_delta));



    


    double curr= charge_sum_cut/tot_scal_cut_time;
    double rate=PTRIG1_Rate;
    //shms
    ofstream txtfile_shms1("txtfile_shms_pt2/treff_shms_noct_nodelta.txt",ios::app);
    txtfile_shms1<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<ent_did_shms_noct_nodelta<<"   "<<ent_should_hms_shms_noct<<"   "<<treff_shms_noct_nodelta<<"    "<<treff_shms_noct_nodelta_err<<"\t\t"<<curr<<endl;

    ofstream txtfile_shms2("txtfile_shms_pt2/treff_shms_noct_delta.txt",ios::app);
    txtfile_shms2<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<ent_did_shms_noct_delta<<"   "<<ent_should_hms_shms_noct<<"   "<<treff_shms_noct_delta<<"    "<<treff_shms_noct_delta_err<<"\t\t"<<curr<<endl;


    ofstream txtfile_shms3("txtfile_shms_pt2/treff_shms_ct_nodelta.txt",ios::app);
    txtfile_shms3<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<ent_did_shms_ct_nodelta<<"   "<<ent_should_hms_shms_ct<<"   "<<treff_shms_ct_nodelta<<"    "<<treff_shms_ct_nodelta_err<<"\t\t"<<curr<<endl;
  
    ofstream txtfile_shms4("txtfile_shms_pt2/treff_shms_ct_delta.txt",ios::app);
    txtfile_shms4<<runs[i]<<"   "<<PTRIG1_Rate<<"    "<<ent_did_shms_ct_delta<<"   "<<ent_should_hms_shms_ct<<"   "<<treff_shms_ct_delta<<"    "<<treff_shms_ct_delta_err<<"\t\t"<<curr<<endl;
 

    //hms
    ofstream txtfile_hms1("txtfile_hms_pt2/treff_hms_noct_nodelta.txt",ios::app);
    txtfile_hms1<<runs[i]<<"   "<<curr<<"    "<<ent_did_hms_noct_nodelta<<"   "<<ent_should_hms_shms_noct<<"   "<<treff_hms_noct_nodelta<<"    "<<treff_hms_noct_nodelta_err<<endl;

    ofstream txtfile_hms2("txtfile_hms_pt2/treff_hms_noct_delta.txt",ios::app);
    txtfile_hms2<<runs[i]<<"   "<<curr<<"    "<<ent_did_hms_noct_delta<<"   "<<ent_should_hms_shms_noct<<"   "<<treff_hms_noct_delta<<"    "<<treff_hms_noct_delta_err<<endl;


    ofstream txtfile_hms3("txtfile_hms_pt2/treff_hms_ct_nodelta.txt",ios::app);
    txtfile_hms3<<runs[i]<<"   "<<curr<<"    "<<ent_did_hms_ct_nodelta<<"   "<<ent_should_hms_shms_ct<<"   "<<treff_hms_ct_nodelta<<"    "<<treff_hms_ct_nodelta_err<<endl;
  
    ofstream txtfile_hms4("txtfile_hms_pt2/treff_hms_ct_delta.txt",ios::app);
    txtfile_hms4<<runs[i]<<"   "<<curr<<"    "<<ent_did_hms_ct_delta<<"   "<<ent_should_hms_shms_ct<<"   "<<treff_hms_ct_delta<<"    "<<treff_hms_ct_delta_err<<endl;
 
    //cout<<runs[i]<<"   "<<curr<<"    "<<ent_did_hms_ct_delta<<"   "<<ent_should_hms_shms_ct<<"   "<<treff_hms_ct_delta<<"    "<<treff_hms_ct_delta_err<<endl;
 


    

    
  }
    
}



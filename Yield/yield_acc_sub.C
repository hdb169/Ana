//oct 6, 2021:
///u/group/c-csv/hdbhatt/my_analysis/yield/yielddatasimc_sept2021/yield_fadc_5367.C
//prints yield for each runs, fills hcal, pcal as a good variable
#define NRUNS 1//11
void factorization_D2H2(){//has hgcer cut
 
  for(Int_t r = 0; r<NRUNS;r++){
    gROOT->SetBatch("kTRUE");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptStat(1000011);
    gStyle->SetPalette(1,0);
    // gStyle->SetOptStat(1000011);
    gStyle->SetOptFit(11);
    gStyle->SetTitleOffset(1.,"Y");
    gStyle->SetTitleOffset(.7,"X");
    gStyle->SetLabelSize(0.04,"XY");
    gStyle->SetTitleSize(0.06,"XY");
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetOptStat(1000111);
    //at the front of calorimeter
    TH2D *xvsy_at_preshower = new TH2D("xvsy_at_preshower","x vs y at shms preshower",100,-75,75,100,-75,75);
    TH2D *xvsy_at_shower = new TH2D("xvsy_at_shower","x vs y at shms shower",100,-75,75,100,-75,75);
    TH2D *xvsy_at_preshower_allcut = new TH2D("xvsy_at_preshower_allcut","x vs y at shms preshower all cuts",100,-75,75,100,-75,75);
    TH2D *xvsy_at_shower_allcut = new TH2D("xvsy_at_shower_allcut","x vs y at shms shower all cuts",100,-75,75,100,-75,75);
    //at the back of calorimeter
    TH2D *xvsy_at_preshower_back = new TH2D("xvsy_at_preshower_back","x vs y at shms preshower back",100,-75,75,100,-75,75);
    TH2D *xvsy_at_shower_back = new TH2D("xvsy_at_shower_back","x vs y at shms shower back",100,-75,75,100,-75,75);
    TH2D *xvsy_at_preshower_allcut_back = new TH2D("xvsy_at_preshower_allcut_back","x vs y at shms preshower all cuts back",100,-75,75,100,-75,75);
    TH2D *xvsy_at_shower_allcut_back = new TH2D("xvsy_at_shower_allcut_back","x vs y at shms shower all cuts back",100,-75,75,100,-75,75);

    TH1D *yield_hist = new TH1D("yield_hist","yield_hist",100,0,1);

    Int_t runs[NRUNS] ={7672};
    Double_t livetime_corr[NRUNS] ={0.98};


   TString filename  = Form("/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_%d_-1.root",runs[r]);


    TFile *f = new TFile(filename, "READ");
    TFile * f11 = new TFile(Form("root/hcal_eff_%d.root",runs[r]),"RECREATE");
    cout<< "Opening Run Num = "<< runs[r] <<endl; 
    cout<< "Opening file = "<< filename <<endl; 

    if(f->IsZombie()){
      std::cout << "Error opening file "<< std::endl;
      continue;
    }

#include "bin.h"
#include "double_good.h"

    
    
    Double_t ctmin = 2.0;
    Double_t ctmax = 2.0;
    Double_t rfmin = 0.5;
    Double_t rfmax = 1.5;
  
    Double_t pcaletotmax = 0.7;
    Double_t hcaletotmin = 0.8;
   
    Double_t rfmin_loose = 0.3;
    Double_t rfmax_loose = 1.8;

 

    Double_t aeromin =   4;
    Double_t hgcermin = 0.5;  
    Double_t hcermin = 1;
  
    Double_t hmsxptarmin  = -0.06;
    Double_t hmsxptarmax  =  0.06;
    Double_t hmsyptarmin  = -0.03;//0.025
    Double_t hmsyptarmax  =  0.03;//0.025 oct 6
    Double_t shmsxptarmin = -0.045;
    Double_t shmsxptarmax =  0.045;
    Double_t shmsyptarmin = -0.028;
    Double_t shmsyptarmax =  0.028;
    double xatshower,yatshower,xatpreshower,yatpreshower;
    double xatshowerback,yatshowerback,xatpreshowerback,yatpreshowerback;
    
   
    Bool_t all_but_nohcer, all_cut, xptaryptar_cut,  xptaryptar_pre, all_but_noaero, all_but_nohgcer,all_but_noxyptar, all_but_noW2Mx2,   position_cut;

#include "offsetrf.h"
    TTree * tt = (TTree *)f->Get("T");    
    TTree * ss = (TTree *)f->Get("TSP");
#include "define_histogram.h"
#include "branch.h"
    Long64_t nentriesD = tt->GetEntries();
#include "scaler_branch.h"
    Long64_t scal_entries = ss->GetEntries();
    //cout<< runs[r] <<" : "<<  "Entries = "<<nentriesD<<endl;
#include "scaler_analysis.h"
    Int_t nscaler_reads_acc=0;
    for (int kk=0; kk<nentriesD;  kk++){//---------------------------------------For Cointime and Acc subtraction only
      tt->GetEntry(kk);

      if (event_flag[nscaler_reads_acc]==1) {
	rf_pion_pre = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut_pre = rf_pion_pre > rfmin && rf_pion_pre < rfmax;
	Epi_cut_pre  = sqrt(pow(pionmass,2) + pow(PgtrP,2));
	zhad_cut_pre = Epi_cut_pre/dnu;
	Mx2_cut_pre  = (protonmass + dnu - zhad_cut_pre*dnu) *  (protonmass + dnu - zhad_cut_pre*dnu) - abs(dpmiss)*abs(dpmiss);
	xptaryptar_pre = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 


	pid_cut_pre  =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 &&  pdipole ==1 && eventtype > 3 &&  mod4_pioncut_pre && paero > aeromin   &&  pcaletottrack < pcaletotmax &&  hcaletottrack  > hcaletotmin /*&&  xptaryptar_pre &&  dW2 > 4 && Mx2_cut_pre > 2.0*/;

	if (pid_cut_pre){
	  hctime->Fill(ctime);
	}  
	 
      }
   
      if (gevnum == scal_event_number[nscaler_reads_acc])  nscaler_reads_acc++;

    }
  
    Int_t bin_max = hctime->GetMaximumBin();
    //Double_t max_value = hctime->GetBinCenter(bin_max);=============================================Changed==========manually
    Double_t max_value = 44;//hctime->GetBinCenter(bin_max);

    Int_t nscaler_reads=0;
    for (int s=0; s<nentriesD;  s++){
      tt->GetEntry(s);
      if (event_flag[nscaler_reads]==1) {

	xatpreshower = track_x_fp + 292.64 * (track_xp_fp);
	yatpreshower = track_y_fp + 292.64 * (track_yp_fp);

	xatshower = track_x_fp + 306.44 * (track_xp_fp);
	yatshower = track_y_fp + 306.44 * (track_yp_fp);

	xatpreshowerback = track_x_fp + 302.64 * (track_xp_fp);
	yatpreshowerback = track_y_fp + 302.64 * (track_yp_fp);

	xatshowerback = track_x_fp + 356.44 * (track_xp_fp);
	yatshowerback = track_y_fp + 356.44 * (track_yp_fp);


	position_cut =  xatshowerback>-60  &&  xatshowerback < 60  && yatshowerback>-60  && yatshowerback < 60 && xatpreshowerback  > -60 && xatpreshowerback  < 60  && yatpreshowerback >-60 && yatpreshowerback < 60;

	Epi = sqrt(pow(pionmass,2) + pow(PgtrP,2));
	zhad = Epi/dnu;
	Mx2 = (protonmass + dnu - zhad*dnu) *  (protonmass + dnu - zhad*dnu) - abs(dpmiss)*abs(dpmiss);
	accL_cut        =   ctime > (max_value - 18 ) && ctime < (max_value - 10);
	accR_cut        =   ctime > (max_value + 14 ) && ctime < (max_value + 22);
	acc_cut_only = (accR_cut || accL_cut);
	ctime_cut_only = ctime > (max_value - ctmin) && ctime < (max_value + ctmax);
	rf_pion = (fmod(-prftdctime+phodfphitstime+ offsetrf ,4.008));
	mod4_pioncut = rf_pion > rfmin && rf_pion < rfmax;
	mod4_pioncut_loose = rf_pion > rfmin_loose && rf_pion < rfmax_loose;

	xptaryptar_cut = hmsxptar > hmsxptarmin && hmsxptar < hmsxptarmax &&   hmsyptar > hmsyptarmin && hmsyptar < hmsyptarmax &&  shmsxptar > shmsxptarmin && shmsxptar < shmsxptarmax  &&  shmsyptar > shmsyptarmin && shmsyptar < shmsyptarmax; 

	shms_etottrack_cut = pcaletottrack < pcaletotmax;
	hms_etottrack_cut  = hcaletottrack >  hcaletotmin;


	base_cut          =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && xptaryptar_cut && dW2 > 4 && Mx2 > 2.0    && xatpreshower>-67 && xatpreshower < 67   && yatshower>-67 && yatshower<57;

	base_cut_looserf          =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut_loose && paero > aeromin && xptaryptar_cut && dW2 > 4 && Mx2 > 2.0    && xatpreshower>-67 && xatpreshower < 67   && yatshower>-67 && yatshower<57;

	acc_cut   =  base_cut && acc_cut_only;    
	coin_cut  =  base_cut && ctime_cut_only;

	all_but_noxyptar = ctime_cut_only &&hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1 &&  hcernpe > hcermin && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin  /* && xptaryptar_cut*/ && dW2 > 4 && Mx2 > 2.0    && xatpreshower>-67 && xatpreshower < 67   && yatshower>-67 && yatshower<57;


	all_cut        =  coin_cut && shms_etottrack_cut && hms_etottrack_cut; //all coin cuts  but no acc cuts (final coin cuts)
	all_acc_cut    =  acc_cut  && shms_etottrack_cut && hms_etottrack_cut; //all  acc cuts  but no coin cuts (final acc cuts)
	all_but_noW2Mx2 =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut_only && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin && xatpreshower>-67 && xatpreshower < 67   && yatshower>-67 && yatshower<57;

	all_but_nohcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut_only && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 1.6 && dW2 > 4 && Mx2 > 2.;/* && hgcer > hgcermin */
	all_but_noaero =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut &&/* paero > aeromin &&*/ ctime_cut_only && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin && dW2 > 4 && Mx2 > 2.;/* && hgcer > hgcermin */
	all_but_nohgcer =  hdelta> -8 && hdelta < 8 && hhodstarttime ==1 && hdipole==1  && pdelta >-10 && pdelta < 20 &&  phodstarttime == 1 && pdipole ==1 && eventtype > 3 && mod4_pioncut && paero > aeromin && ctime_cut_only && pcaletottrack < pcaletotmax  && hcaletottrack > hcaletotmin  && dW2 > 4 && Mx2 > 2.;//NOHGCER
    
 
	hmsshower = hcaletottrack-hcalepr;
	shmsshower = pcaletottrack-pcalepr;

	hcal_should_cut_acc   =  acc_cut && shms_etottrack_cut;
	hcal_did_cut_acc      =  hcal_should_cut_acc           && hms_etottrack_cut;
	pcal_should_cut_acc   =  acc_cut && hms_etottrack_cut;
	pcal_did_cut_acc      =  pcal_should_cut_acc           && shms_etottrack_cut;
	
	//	if(all_acc_cut){hctimeacc->Fill(ctime);}

      
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//Fill acc hist

	if(all_acc_cut){
	  hist_zhad_acc->Fill(zhad);///-------------------------------------------------------------yieldacc=============================================1YIELD ACC
	  hist_ctime_acc->Fill(ctime);	
	}


	//Fill coin hist
	if(all_cut){
	  hist_zhad_coin->Fill(zhad);///---------------------------------------------------------yield COIN===============================================2YIELD COIN
	  hist_ctime_coin->Fill(ctime);
	}  
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	if(hcal_did_cut_acc && pcal_did_cut_acc  && position_cut){//=changed here added pcal acc
	  hist_hcal_did_acc->Fill(hcaletottrack);///-------------------------------------------------------------yieldacc=============================================1YIELD ACC
	}
	if(hcal_should_cut_acc && position_cut){

	  hist_hcal_should_acc->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_acc->Fill(hcalepr,hmsshower);
	}
	
	if(pcal_did_cut_acc && position_cut ){
	  hist_pcal_did_acc->Fill(pcaletottrack);
	  
	}
	if(pcal_should_cut_acc&& position_cut ){
	  hist_pcal_should_acc->Fill(pcaletottrack);
	  shms_sh_vs_psh_should_acc->Fill(pcalepr,shmsshower);
	}

	//acc cut done

	//Earlier above we defined for accidental and now we are defining for the coincidence events. The only difference is taking ctime peak events///
	hcal_should_cut_coin   =  coin_cut && shms_etottrack_cut && position_cut;
	hcal_did_cut_coin      =  hcal_should_cut_coin           && hms_etottrack_cut && position_cut;
	pcal_should_cut_coin   =  coin_cut && hms_etottrack_cut&& position_cut;
	pcal_did_cut_coin      =  pcal_should_cut_coin           && shms_etottrack_cut && position_cut;
	all_coin_cut           =  coin_cut && shms_etottrack_cut && hms_etottrack_cut  && position_cut;
	
	//Fill coin hist
	if(hcal_did_cut_coin && pcal_did_cut_coin && position_cut ){///=====added pcal cut too ===============
	  hist_hcal_did_coin->Fill(hcaletottrack);///-------------------------------------------------------------yield COIN===============================================2YIELD COIN

	}   

	if(hcal_should_cut_coin){
	  hist_hcal_should_coin->Fill(hcaletottrack);
	  hms_sh_vs_psh_should_coin->Fill(hcalepr,hmsshower);

	}
	
	if(pcal_did_cut_coin){hist_pcal_did_coin->Fill(pcaletottrack);}
	if(pcal_should_cut_coin){
	  hist_pcal_should_coin->Fill(pcaletottrack);
	  shms_sh_vs_psh_should_coin->Fill(pcalepr,shmsshower);

	}
	////////////////////////========================Front======================================================>>>>>>>>>>
	if(base_cut && coin_cut){xvsy_at_preshower->Fill(xatpreshower,yatpreshower);}
	//x =( -67,67) left-right, y = (-68,58):top,bottom
	if(base_cut && coin_cut){xvsy_at_shower->Fill(xatshower,yatshower);}


	if(pcal_did_cut_coin && hcal_did_cut_coin ){xvsy_at_preshower_allcut->Fill(xatpreshower,yatpreshower);}
	//x =( -67,67) left-right, y = (-68,58):top,bottom
	if(pcal_did_cut_coin && hcal_did_cut_coin ){xvsy_at_shower_allcut->Fill(xatshower,yatshower);}
	///////////////////////////////////////////==============BACK======================================================>>>>>>
	if(base_cut && coin_cut){xvsy_at_preshower_back->Fill(xatpreshowerback,yatpreshowerback);}
	if(base_cut && coin_cut){xvsy_at_shower_back->Fill(xatshowerback,yatshowerback);}


	if(pcal_did_cut_coin && hcal_did_cut_coin ){xvsy_at_preshower_allcut_back->Fill(xatpreshowerback,yatpreshowerback);}
	if(pcal_did_cut_coin && hcal_did_cut_coin ){xvsy_at_shower_allcut_back->Fill(xatshowerback,yatshowerback);}
	///////////////////////////////////////////==============BACK DONE======================================================>>>>>>


	

	//+++++++++++++++++++++++++++++++sh vs etot, presh vs etot************************
	//	if(all_coin_cut) //with hcal, pcal cuts too 

	if(all_cut) //with hcal, pcal cuts too 
	  {
	    hms_sh_vs_psh->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh->Fill(pcalepr,shmsshower);
	    ctime_vs_rf->Fill(rf_pion, ctime);
	    etot_vs_rf->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf->Fill(rf_pion, pcalepr);
	    ctime_vs_etot->Fill(pcaletottrack, ctime);
	    ctime_vs_epr->Fill(pcalepr,ctime);
	    hctimect->Fill(ctime);
	    sh_vs_rf->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf->Fill(rf_pion,hmsshower);
	    hist_hmsp->Fill(HgtrP);//mom
	    hist_shmsp->Fill(PgtrP);

	  }

	if(all_but_nohcer){//to plot npe vs hms p
	   hcernpe_vs_hmsp->Fill(HgtrP,hcernpe);
	  // hcernpe_vs_hmsp->Fill(ctime,ctime);

	}
	if(all_but_noaero){//to plot npe vs shms p
	  aeronpe_vs_shmsp->Fill(PgtrP,paero);
	}
	if(all_but_nohgcer){//to plot npe vs shms p
	  hgcernpe_vs_shmsp->Fill(PgtrP,hgcer);
	}

	if(all_but_noxyptar){//this is all but non xptar, yptar 
	  hms_xptar_noxyptar->Fill(hmsxptar);
	  hms_yptar_noxyptar->Fill(hmsyptar);
	  shms_xptar_noxyptar->Fill(shmsxptar);
	  shms_yptar_noxyptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar_noxyptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar_noxyptar->Fill(shmsyptar,shmsxptar);
	}

	//all_cut: all pid+coin+RF aero etc
	if(all_cut){//this is for xptar, yptar peter's values (xptar,yptar)=>HMS(+/-0.06,+/-0.022) and SHMS(+/-0.045,+/-0.028)
	  hms_xptar->Fill(hmsxptar);
	  hms_yptar->Fill(hmsyptar);
	  shms_xptar->Fill(shmsxptar);
	  shms_yptar->Fill(shmsyptar);
	  hms_xptar_vs_yptar->Fill(hmsyptar,hmsxptar);//xptar along yaxis and yptar along x axis
	  shms_xptar_vs_yptar->Fill(shmsyptar,shmsxptar);
	}

	
	if(base_cut_looserf) //no any cal cut at all

	  {
	    hms_sh_vs_psh_base->Fill(hcalepr,hmsshower);
	    shms_sh_vs_psh_base->Fill(pcalepr,shmsshower);
	    ctime_vs_rf_base->Fill(rf_pion, ctime);
	    etot_vs_rf_base->Fill(rf_pion,pcaletottrack);
	    hms_etot_vs_rf_base->Fill(rf_pion,hcaletottrack);
	    epr_vs_rf_base->Fill(rf_pion, pcalepr);
	    ctime_vs_etot_base->Fill(pcaletottrack, ctime);
	    ctime_vs_epr_base->Fill(pcalepr,ctime);
	    sh_vs_rf_base->Fill(rf_pion,shmsshower);
	    hmsepr_vs_rf_base->Fill(rf_pion,hcalepr);
	    hmssh_vs_rf_base->Fill(rf_pion,hmsshower);
	  }	

	if(all_but_noW2Mx2){
	  d_W2->Fill(dW2);
	  d_Wprime2->Fill(Mx2);

	}

     



      }//eventflag
      if (gevnum == scal_event_number[nscaler_reads])  nscaler_reads++;

    }//nentries


    TCanvas * csh = new TCanvas ("csh", "2D pcal", 1200, 800);
    csh->Divide(2,2);
    csh->cd(1);gPad->SetGrid();gPad->SetLogz();
 
    xvsy_at_preshower->Draw("colz");
    xvsy_at_preshower->GetXaxis()->SetTitle(Form("X At Pre-Shower (no cal cuts: +ve) %d",runs[r]));
    xvsy_at_preshower->GetYaxis()->SetTitle("Y At Pre-Shower");

    csh->cd(2);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_shower->Draw("colz");
    xvsy_at_shower->GetXaxis()->SetTitle(Form("X At Shower (no cal cuts: +ve) %d", runs[r]));
    xvsy_at_shower->GetYaxis()->SetTitle("Y At Shower");

    csh->cd(3);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_preshower_allcut->Draw("colz");
    xvsy_at_preshower_allcut->GetXaxis()->SetTitle(Form("X At Pre-Shower (all cuts: +ve) %d",runs[r]));
    xvsy_at_preshower_allcut->GetYaxis()->SetTitle("Y At Pre-Shower");

    csh->cd(4);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_shower_allcut->Draw("colz");
    xvsy_at_shower_allcut->GetXaxis()->SetTitle(Form("X At Shower (all cuts: +ve) %d", runs[r]));
    xvsy_at_shower_allcut->GetYaxis()->SetTitle("Y At Shower ");


    csh->SaveAs(Form("pdfoct6/XvsYcalfront_%d.pdf", runs[r]));


 
    TCanvas * back = new TCanvas ("back", "2D pcal", 1200, 800);
    back->Divide(2,2);
    back->cd(1);gPad->SetGrid();gPad->SetLogz();
 
    xvsy_at_preshower_back->Draw("colz");
    xvsy_at_preshower_back->GetXaxis()->SetTitle(Form("X At Pre-Shower (no cal cuts: +ve) %d",runs[r]));
    xvsy_at_preshower_back->GetYaxis()->SetTitle("Y At Pre-Shower");

    back->cd(2);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_shower_back->Draw("colz");
    xvsy_at_shower_back->GetXaxis()->SetTitle(Form("X At Shower (no cal cuts: +ve) %d", runs[r]));
    xvsy_at_shower_back->GetYaxis()->SetTitle("Y At Shower");

    back->cd(3);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_preshower_allcut_back->Draw("colz");
    xvsy_at_preshower_allcut_back->GetXaxis()->SetTitle(Form("X At Pre-Shower (all cuts: +ve) %d",runs[r]));
    xvsy_at_preshower_allcut_back->GetYaxis()->SetTitle("Y At Pre-Shower");

    back->cd(4);gPad->SetGrid();gPad->SetLogz();
    xvsy_at_shower_allcut_back->Draw("colz");
    xvsy_at_shower_allcut_back->GetXaxis()->SetTitle(Form("X At Shower (all cuts: +ve) %d", runs[r]));
    xvsy_at_shower_allcut_back->GetYaxis()->SetTitle("Y At Shower ");


    back->SaveAs(Form("pdfoct6/XvsYcalback%d.pdf", runs[r]));



 
    TCanvas * cc4 = new TCanvas ("cc4", "W2  MX2", 1200, 800);
    cc4->Divide(2,1);

    cc4->cd(1);
    d_W2->Draw();gPad->SetGridx();gPad->SetGridy();
    d_W2->SetTitle(Form("W2 : Run %d",runs[r]));
    d_W2->SetLineWidth(3);
    cc4->cd(2);gPad->SetGridx();gPad->SetGridy();
    d_Wprime2->Draw();
    d_Wprime2->SetTitle(Form("Mx2 : Run %d",runs[r]));
    d_Wprime2->SetLineWidth(3);

    cc4->SaveAs(Form("pdfoct6/W2_Mx2_%d.pdf", runs[r]));

    
    TCanvas * cc3 = new TCanvas ("cc3", "hcer vs npe", 1200, 800);

    cc3->Divide(4,3);
    //before xptar yptar cut
    cc3->cd(1);gPad->SetGridx();gPad->SetGridy();
    hms_xptar_noxyptar->Draw();
    hms_xptar_noxyptar->GetXaxis()->SetTitle("HMS XPTAR");
    hms_xptar_noxyptar->GetXaxis()->CenterTitle();
    hms_xptar_noxyptar->SetTitle(Form("hms_xptar : Run %d",runs[r]));

    cc3->cd(2);gPad->SetGridx();gPad->SetGridy();
    hms_yptar_noxyptar->Draw();
    hms_yptar_noxyptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_yptar_noxyptar->GetXaxis()->CenterTitle();

    
    cc3->cd(3);gPad->SetGridx();gPad->SetGridy();
    shms_xptar_noxyptar->Draw();
    shms_xptar_noxyptar->GetXaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_noxyptar->GetXaxis()->CenterTitle();


    cc3->cd(4);gPad->SetGridx();gPad->SetGridy();
    shms_yptar_noxyptar->Draw();
    shms_yptar_noxyptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_yptar_noxyptar->GetXaxis()->CenterTitle();

    
    cc3->cd(5);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    hms_xptar_vs_yptar_noxyptar->Draw("colz");
    hms_xptar_vs_yptar_noxyptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_xptar_vs_yptar_noxyptar->GetYaxis()->SetTitle("HMS XPTAR");
    hms_xptar_vs_yptar_noxyptar->GetXaxis()->CenterTitle();
    hms_xptar_vs_yptar_noxyptar->GetYaxis()->CenterTitle();

    cc3->cd(6);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    shms_xptar_vs_yptar_noxyptar->Draw("colz");
    shms_xptar_vs_yptar_noxyptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_xptar_vs_yptar_noxyptar->GetYaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_vs_yptar_noxyptar->GetXaxis()->CenterTitle();
    shms_xptar_vs_yptar_noxyptar->GetYaxis()->CenterTitle();

    
    //after xptar yptar cut
    cc3->cd(7);gPad->SetGridx();gPad->SetGridy();
    hms_xptar->Draw();
    hms_xptar->GetXaxis()->SetTitle("HMS XPTAR");
    hms_xptar->GetXaxis()->CenterTitle();
    hms_xptar->SetTitle(Form("hms_xptar : Run %d",runs[r]));

    cc3->cd(8);gPad->SetGridx();gPad->SetGridy();
    hms_yptar->Draw();
    hms_yptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_yptar->GetXaxis()->CenterTitle();

    
    cc3->cd(9);gPad->SetGridx();gPad->SetGridy();
    shms_xptar->Draw();
    shms_xptar->GetXaxis()->SetTitle("SHMS XPTAR");
    shms_xptar->GetXaxis()->CenterTitle();


    cc3->cd(10);gPad->SetGridx();gPad->SetGridy();
    shms_yptar->Draw();
    shms_yptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_yptar->GetXaxis()->CenterTitle();

    
    cc3->cd(11);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    hms_xptar_vs_yptar->Draw("colz");
    hms_xptar_vs_yptar->GetXaxis()->SetTitle("HMS YPTAR");
    hms_xptar_vs_yptar->GetYaxis()->SetTitle("HMS XPTAR");
    hms_xptar_vs_yptar->GetXaxis()->CenterTitle();
    hms_xptar_vs_yptar->GetYaxis()->CenterTitle();

    cc3->cd(12);gPad->SetLogz();gPad->SetGridx();gPad->SetGridy();
    shms_xptar_vs_yptar->Draw("colz");
    shms_xptar_vs_yptar->GetXaxis()->SetTitle("SHMS YPTAR");
    shms_xptar_vs_yptar->GetYaxis()->SetTitle("SHMS XPTAR");
    shms_xptar_vs_yptar->GetXaxis()->CenterTitle();
    shms_xptar_vs_yptar->GetYaxis()->CenterTitle();

    
    
    cc3->SaveAs(Form("pdfoct6/xptar_yptar_%d.pdf", runs[r]));

    TCanvas * cc2 = new TCanvas ("cc2", "hcer vs npe", 1000, 800);
    cc2->Divide(2,2);
    cc2->cd(1);gPad->SetLogz();
    hcernpe_vs_hmsp->Draw("colz");
    hcernpe_vs_hmsp->SetTitle(Form("HCER NPE vs HMS MOM : Run: %d",runs[r]));
      
    cc2->cd(2);gPad->SetLogz();
    aeronpe_vs_shmsp->Draw("colz");

    cc2->cd(3);gPad->SetLogz();
    hgcernpe_vs_shmsp->Draw("colz");
    hcernpe_vs_hmsp->SetTitle(Form("HCER NPE vs HMS MOM : Run: %d",runs[r]));


    cc2->SaveAs(Form("pdfoct6/hcer_aero_hgcer_npe_vs_p_%d.pdf", runs[r]));
    
    // find acc only under the main ctime peak only (in 16ns..., in 1ns ..., and under main peak ~3 ns ....)
    TH1D *  hist_hcal_did_acc_1peak = (TH1D*)hist_hcal_did_acc->Clone();
    TH1D *  hist_hcal_should_acc_1peak = (TH1D*)hist_hcal_should_acc->Clone();
    TH1D *  hist_pcal_did_acc_1peak = (TH1D*)hist_pcal_did_acc->Clone();
    TH1D *  hist_pcal_should_acc_1peak = (TH1D*)hist_pcal_should_acc->Clone();
    TH1D *  hist_ctime_acc_1peak = (TH1D*)hist_ctime_acc->Clone();//copy of acc hist

    TH2D * hms_sh_vs_psh_should_acc_1peak = (TH2D*)hms_sh_vs_psh_should_acc->Clone();
    TH2D * shms_sh_vs_psh_should_acc_1peak = (TH2D*)shms_sh_vs_psh_should_acc->Clone();

    TH1D * hist_zhad_acc_1peak = (TH1D*)hist_zhad_acc->Clone();///1=======>=for yield numbering//////==========================here========================================


    ///For TEst on acc
   
    
    hist_zhad_acc_1peak->Scale((ctmin+ctmax)/16);///2

    hist_hcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_hcal_should_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_did_acc_1peak->Scale((ctmin+ctmax)/16);
    hist_pcal_should_acc_1peak->Scale((ctmin+ctmax)/16);


    hist_ctime_acc_1peak->Scale((ctmin+ctmax)/16);
    hms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);
    shms_sh_vs_psh_should_acc_1peak->Scale((ctmin+ctmax)/16);


        double onepeakacc_entries = hist_zhad_acc_1peak->GetEntries();///3

    double onepeakacc_counts = hist_zhad_acc_1peak->Integral();///3
    // cout<<runs[r]<<"  "<<"acc one peak counts = "<<onepeakacc_counts<<endl;
    if (hist_zhad_acc_1peak->GetSumw2N() == 0) hist_zhad_acc_1peak->Sumw2(kTRUE);///4

    if (hist_hcal_did_acc_1peak->GetSumw2N() == 0) hist_hcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_hcal_should_acc_1peak->GetSumw2N() == 0) hist_hcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_did_acc_1peak->GetSumw2N() == 0) hist_pcal_did_acc_1peak->Sumw2(kTRUE);
    if (hist_pcal_should_acc_1peak->GetSumw2N() == 0) hist_pcal_should_acc_1peak->Sumw2(kTRUE);
    if (hist_ctime_acc_1peak->GetSumw2N() == 0) hist_ctime_acc_1peak->Sumw2(kTRUE);

    if (hms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) hms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);
    if (shms_sh_vs_psh_should_acc_1peak->GetSumw2N() == 0) shms_sh_vs_psh_should_acc_1peak->Sumw2(kTRUE);

    ///hist_zhad_clean->Add(hist_zhad_coin,hist_zhad_acc_1peak,1.0,-1.0);///5=================================================================================+COME HERE ==========
    hist_zhad_clean->Add(hist_zhad_coin,hist_zhad_acc_1peak,1.0,-1.0);///5
    cout<<""<<endl;
    cout<<"ENT INT"<<endl;

    cout<<" Entries & Integral: acc acc, coin coin , clean clean "<<endl;
    cout<<runs[r]<<"  "<<hist_zhad_acc_1peak->GetEntries()<<"  "<<hist_zhad_acc_1peak->Integral()<<"  "<<hist_zhad_coin->GetEntries()<<"  "<<hist_zhad_coin->Integral()<<"  "<<hist_zhad_clean->GetEntries()<<"   "<<hist_zhad_clean->Integral()<<endl;
    cout<<"ENT INT"<<endl;
    cout<<""<<endl;

    hist_hcal_did_clean->Add(hist_hcal_did_coin,hist_hcal_did_acc_1peak,1.0,-1.0);
    hist_hcal_should_clean->Add(hist_hcal_should_coin,hist_hcal_should_acc_1peak,1.0,-1.0);
    hist_pcal_did_clean->Add(hist_pcal_did_coin,hist_pcal_did_acc_1peak,1.0,-1.0);
    hist_pcal_should_clean->Add(hist_pcal_should_coin,hist_pcal_should_acc_1peak,1.0,-1.0);
    hist_ctime_clean->Add(hctimect,hist_ctime_acc_1peak,1.0,-1.0);

    hms_sh_vs_psh_should_clean->Add(hms_sh_vs_psh_should_coin,hms_sh_vs_psh_should_acc_1peak,1.0,-1.0);
    shms_sh_vs_psh_should_clean->Add(shms_sh_vs_psh_should_coin,shms_sh_vs_psh_should_acc_1peak,1.0,-1.0);

    
    if (hist_zhad_clean->GetSumw2N() == 0) hist_zhad_clean->Sumw2(kTRUE);////6
    if (hist_hcal_did_clean->GetSumw2N() == 0) hist_hcal_did_clean->Sumw2(kTRUE);
    if (hist_hcal_should_clean->GetSumw2N() == 0) hist_hcal_should_clean->Sumw2(kTRUE);
    if (hist_pcal_did_clean->GetSumw2N() == 0) hist_pcal_did_clean->Sumw2(kTRUE);
    if (hist_pcal_should_clean->GetSumw2N() == 0) hist_pcal_should_clean->Sumw2(kTRUE);
    if (hist_ctime_clean->GetSumw2N() == 0) hist_ctime_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) hms_sh_vs_psh_should_clean->Sumw2(kTRUE);
    if (hms_sh_vs_psh_should_clean->GetSumw2N() == 0) shms_sh_vs_psh_should_clean->Sumw2(kTRUE);



    

    TCanvas * cc1 = new TCanvas ("cc1", "cc1", 1000, 800);
    cc1->Divide(1,1);
    cc1->cd(1);

   

    hctime->Draw("hist");//finding peak all but no ct
    hctime->SetLineWidth(1);
    hctime->SetLineColor(kBlack);



 
    hctimect->Draw("hist same");//all coincuts, main peak only
    hctimect->SetLineColor(kMagenta);
    hctimect->SetLineWidth(1);

    hist_ctime_clean->Draw("hist same");
    hist_ctime_clean->SetLineColor(kGreen);
    hist_ctime_clean->SetLineWidth(2);


 
    hctimeacc->Draw("hist sames");//acc 4 peaks only
    hctimeacc->SetLineColor(kRed);
    hctimeacc->SetLineWidth(1);

    
    hist_ctime_acc_1peak->Draw("hist sames");
    hist_ctime_acc_1peak->SetLineColor(kPink);
    hist_ctime_acc_1peak->SetLineWidth(3);

    // hist_ctime_clean->Draw("hist, sames");

   
    


    double ctime_acc_ent        = hctimeacc->Integral();
    double ctime_acc_1peak_ent  = hist_ctime_acc_1peak->Integral();
    double ctime_coin_ent       = hctimect->Integral();
    double ctime_clean_ent      = hist_ctime_clean->Integral();
    // cout<<"============================================================================"<<endl;
    // cout<<runs[r]<<"  "<<"Coin Peak, Acc,  Clean enries = "<<ctime_coin_ent<<"    "<<ctime_acc_1peak_ent<<"     "<<ctime_clean_ent<<endl;
    // cout<<"============================================================================"<<endl;

   
    cc1->SaveAs(Form("pdfoct6/ctime_bef_acc_%d.pdf", runs[r]));
    delete cc1;
   
    TCanvas * c1 = new TCanvas ("c1", "c1", 1000, 800);
    c1->Divide(3,2);
    c1->cd(1);gPad->SetLogy();gPad->SetGrid();
    hist_hcal_did_coin->Draw();
    //hist_hcal_did_acc->Draw("sames");
    hist_hcal_did_acc->SetLineColor(kPink);
    hist_hcal_did_acc_1peak->Draw("hist sames");
    hist_hcal_did_acc_1peak->SetLineColor(kRed);
    hist_hcal_did_clean->Draw("hist sames");
    hist_hcal_did_clean->SetLineColor(kGreen);
    // hist_hcal_did_clean->SetLineWidth(2);    
    hist_hcal_did_coin->SetTitle(Form("HCAL DID %d",runs[r]));

    c1->cd(2);gPad->SetLogy();gPad->SetGrid();
    hist_hcal_should_coin->Draw();
    //hist_hcal_should_acc->Draw("sames");
    hist_hcal_should_acc->SetLineColor(kPink);
    hist_hcal_should_acc_1peak->Draw("hist sames");
    hist_hcal_should_acc_1peak->SetLineColor(kRed);
    hist_hcal_should_clean->Draw("hist sames");
    hist_hcal_should_clean->SetLineColor(kGreen);
    // hist_hcal_should_clean->SetLineWidth(3);    

    c1->cd(3);gPad->SetLogz();gPad->SetGrid();
    hms_sh_vs_psh_should_clean->Draw("colz");

    c1->cd(4);gPad->SetLogy();gPad->SetGrid();
    hist_pcal_did_coin->Draw();
    //hist_pcal_did_acc->Draw("sames");
    hist_pcal_did_acc->SetLineColor(kPink);
    hist_pcal_did_acc_1peak->Draw("hist sames");
    hist_pcal_did_acc_1peak->SetLineColor(kRed);
    hist_pcal_did_clean->Draw("hist sames");
    hist_pcal_did_clean->SetLineColor(kGreen);
    //hist_pcal_did_clean->SetLineWidth(3); 

    c1->cd(5);gPad->SetLogy();gPad->SetGrid();
    hist_pcal_should_coin->Draw();
    //hist_pcal_should_acc->Draw("sames");
    hist_pcal_should_acc->SetLineColor(kPink);
    hist_pcal_should_acc_1peak->Draw("hist sames");
    hist_pcal_should_acc_1peak->SetLineColor(kRed);
    hist_pcal_should_clean->Draw("hist sames");
    hist_pcal_should_clean->SetLineColor(kGreen);
    // hist_pcal_should_clean->SetLineWidth(3);   

    c1->cd(6);gPad->SetLogz();gPad->SetGrid();
    shms_sh_vs_psh_should_clean->Draw("colz");


    // delete c1;
    
    double ent_hcaldid_coin =  hist_hcal_did_coin->Integral();
    double ent_hcaldid_acc =  hist_hcal_did_acc->Integral();
    double ent_hcaldid_acc_1peak =  hist_hcal_did_acc_1peak->Integral();
    double ent_hcaldid_clean =  hist_hcal_did_clean->Integral();











    //////This is the OLD yield////////////////////////////////////

    //hist_hcal_did_clean/////

    double charge1 = charge_sum_cut_corr/1000.;
    TH1D *  hist_yield_copy = (TH1D*)hist_hcal_did_clean->Clone();
    // hist_yield_copy->Scale(charge_sum_cut_corr*0.81/1000);//0.81 is efficiency average
    hist_yield_copy->Scale(1/charge1);//0.81 is efficiency average

    TCanvas * cyield = new TCanvas("cyield","yield",1000,800);
    cyield->Divide(1,1);
    cyield->cd(1);
    hist_yield_copy->Draw("hist");
    hist_yield_copy->SetLineWidth(2);
    hist_yield_copy->SetTitle("Data Yield Acc Sub. Eff corr.");
    hist_yield_copy->GetXaxis()->SetTitle("Zhad");
    hist_yield_copy->GetYaxis()->SetTitle("Counts/mC");
    hist_yield_copy->GetXaxis()->SetRangeUser(0,2);

    Int_t yield_entries = hist_hcal_did_clean->GetEntries();
    Int_t yield_integral = hist_hcal_did_clean->Integral();

    cout<<"hello Mr.================="<<endl;
    cout<<runs[r]<<"   "<< yield_entries << "   "<<yield_integral<<endl;
    cout<<"hello Mr."<<endl;
    double onepeakacc_integral = hist_zhad_acc_1peak->Integral();//4
    cout<<runs[r]<<"   "<< onepeakacc_entries << "   "<<onepeakacc_integral<<endl;

    cout<<"hello Mr.======================"<<endl;


    //here is final/////
    
    double yield_integral_uncorr = yield_entries/charge1;///==========1
    double yield_integral_uncorr_err = sqrt(yield_entries)/charge1;///==========1

    double yield_integral_corr_lt_boil   = yield_entries/(charge1 * boil_corr* livetime_corr[r]);//===2
    double yield_integral_corr_lt_boil_err   = sqrt(yield_entries)/(charge1 * boil_corr* livetime_corr[r]);//===2
   
    double yield_integral_corr_lt_boil_fadc   = yield_entries/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr);//===3
    double yield_integral_corr_lt_boil_fadc_err   = sqrt(yield_entries)/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr);//===3

    double yield_integral_corr_lt_boil_fadc_pid      = yield_entries/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr * 0.92);
    double yield_integral_corr_lt_boil_fadc_pid_err   = sqrt(yield_entries)/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr * 0.92);




    //double yield_integral_err = sqrt(hist_hcal_did_clean->Integral())/(charge*0.81);
    //double yield_entries_err = sqrt(hist_hcal_did_clean->GetEntries())/(charge*0.81);
    //double yield_integral_err = (sqrt(yield_entries)*boiling_corr[r])/(charge1*livetime_corr[r]);
    //double yield_entries_err = sqrt(yield_entries);

    
    cyield->SaveAs(Form("pdfoct6/Yield_final_%d.pdf", runs[r]));
    ///////////////////////////////////////////////////////////////////////////////////////////The following  is the NEWEST  yield////////////////////////////////////
    TH1D *  hist_yield_zhad_clean_copy = (TH1D*)hist_zhad_clean->Clone();////6
   
    
    


    // hist_yield_copy->Scale(charge_sum_cut_corr*0.81/1000);//0.81 is efficiency average
    hist_yield_zhad_clean_copy->Scale(1/charge1);//0.81 is efficiency average////7
   

    TCanvas * cyield_final = new TCanvas("cyield_final","yield_final",1000,800);///8
    cyield_final->Divide(3,3);
    cyield_final->cd(1);

    
    hist_yield_zhad_clean_copy-> Draw("hist");
    hist_yield_zhad_clean_copy->SetLineWidth(3);
    hist_yield_zhad_clean_copy->SetLineColor(kBlue);
    hist_yield_zhad_clean_copy->SetMarkerStyle(22);
    hist_yield_zhad_clean_copy->SetLineColor(kGreen);
    hist_yield_zhad_clean_copy->SetTitle("Yield All Corrections applied: Counts/mc)");

   

    cyield_final->cd(2);

    hist_zhad_coin-> Draw("hist");
    hist_zhad_coin->SetLineWidth(2);
    hist_zhad_coin->SetTitle(Form("Green: Clean Counts %d",runs[r]));
    hist_zhad_coin->GetXaxis()->SetTitle("Zhad");
    hist_zhad_coin->GetYaxis()->SetTitle("Counts");
    hist_zhad_coin->GetXaxis()->SetRangeUser(0,1);


    hist_zhad_clean-> Draw("hist sames");
    hist_zhad_clean->SetLineWidth(2);
    hist_zhad_clean->SetLineColor(kBlue);
    hist_zhad_clean->SetLineColor(kGreen);

    hist_zhad_acc_1peak->Draw("hist sames");
    hist_zhad_acc_1peak->SetLineWidth(2);
    hist_zhad_acc_1peak->SetLineColor(kRed);


    cyield_final->cd(3);
    hist_ctime_coin-> Draw("hist");
    hist_ctime_coin->SetLineWidth(2);
    hist_ctime_coin->SetTitle("No Acc Subtracted");
    hist_ctime_coin->GetXaxis()->SetTitle("Ctime");
    hist_ctime_coin->GetYaxis()->SetTitle("Counts");
    hist_ctime_coin->GetXaxis()->SetRangeUser(0,1);
    hist_ctime_coin->SetLineColor(kBlue);


    cyield_final->cd(4);
    hist_ctime_acc-> Draw("hist");
    hist_ctime_acc->SetLineWidth(2);
    hist_ctime_acc->SetTitle("Acc in 4 bunches");
    hist_ctime_acc->GetXaxis()->SetTitle("Ctime");
    hist_ctime_acc->GetYaxis()->SetTitle("Counts");
    hist_ctime_acc->GetXaxis()->SetRangeUser(0,1);
    hist_ctime_acc->SetLineColor(kRed);


    cyield_final->cd(5);
   
    hist_ctime_acc_1peak->Draw("hist");
    hist_ctime_acc_1peak->SetLineColor(kMagenta);
    hist_ctime_acc_1peak->SetLineWidth(2);
    hist_ctime_acc_1peak->SetTitle("Acc in 1 bunch only (Eqvt)");

    cyield_final->cd(6);

   
    hist_ctime_clean->Add(hist_ctime_coin,hist_ctime_acc_1peak,1.0,-1.0);
    hist_ctime_clean->Draw("hist");
    hist_ctime_clean->SetLineColor(kGreen);
    hist_ctime_clean->SetLineWidth(2);
    hist_ctime_clean->SetTitle("Acc Subtracted Clean)");


    cyield_final->cd(7);

    hist_ctime_coin-> Draw("hist");
    hist_ctime_coin->SetLineWidth(2);
    hist_ctime_coin->SetTitle("Before Acc Sub AND Acc in 4 bunches");
    hist_ctime_coin->GetXaxis()->SetTitle("Ctime");
    hist_ctime_coin->GetYaxis()->SetTitle("Counts");
    hist_ctime_coin->GetXaxis()->SetRangeUser(0,1);
    hist_ctime_coin->SetLineColor(kBlue);
    hist_ctime_coin->GetYaxis()->SetRangeUser(-2000,6000);

    hist_ctime_clean->Draw("hist sames");
    hist_ctime_clean->SetLineColor(kGreen);

    cout<<"HELLO"<<endl;

    cout<<runs[r]<<"   "<<hist_ctime_coin->GetEntries()<<"\t\t"<<hist_ctime_coin->Integral()<<"\t\t"<<hist_ctime_clean->GetEntries()<<"\t\t"<<hist_ctime_clean->Integral()<<endl;
    cout<<""<<endl;
    cout<<runs[r]<<"   "<<hist_ctime_acc->GetEntries()<<"\t\t"<<hist_ctime_acc->Integral()<<"\t\t"<<hist_ctime_acc_1peak->GetEntries()<<"\t\t"<<hist_ctime_acc_1peak->Integral()<<endl;
    cout<<""<<endl;



    /*
    hist_ctime_acc-> Draw("hist sames");
    hist_ctime_acc->SetLineColor(kRed);


    hist_ctime_acc_1peak-> Draw("hist sames");
    hist_ctime_acc_1peak->SetLineColor(kMagenta);
    */

   
    
    cout<<""<<endl;
    cout<<" TEST = coin acc clean  = "<<runs[r]<< "   "<<hist_zhad_coin->GetEntries()<<"  "<<hist_zhad_acc_1peak->GetEntries()<<"   "<<hist_zhad_clean->GetEntries()<<" "<<hist_yield_zhad_clean_copy->Integral()<< endl;
    cout<<""<<endl;
    cout<<""<<endl;



    ///wrong Int_t correct_yield_entries = hist_yield_zhad_clean_copy->GetEntries();///9
    
    ///Int_t correct_yield_entries = hist_zhad_clean->GetEntries();///9=======================Entries = wrong
    Int_t correct_yield_entries = hist_zhad_clean->Integral();///9

 Int_t yield_entries11 = hist_zhad_clean->GetEntries();
    Int_t yield_integral11 = hist_zhad_clean->Integral();

    cout<<"hello Mr.================="<<endl;

    cout<<runs[r]<<"   "<< yield_entries11 << "   "<<yield_integral11<<endl;
    cout<<"hello Mr."<<endl;
    cout<<runs[r]<<"   "<< onepeakacc_entries << "   "<<onepeakacc_integral<<endl;
    cout<<"hello Mr.=================="<<endl;



    double correct_yield_integral_uncorr = correct_yield_entries/charge1;///==========10
    double correct_yield_integral_uncorr_err = sqrt(correct_yield_entries)/charge1;///==========11

    double all_peter_yield = correct_yield_entries/(charge1*livetime_corr[r]);///==========10
    double all_peter_yield_err = sqrt(correct_yield_entries)/(charge1*livetime_corr[r]);///==========11


    double correct_yield_integral_corr_lt_boil   = correct_yield_entries/(charge1 * boil_corr* livetime_corr[r]);//===12
    double correct_yield_integral_corr_lt_boil_err   = sqrt(correct_yield_entries)/(charge1 * boil_corr* livetime_corr[r]);//===13
   
    double correct_yield_integral_corr_lt_boil_fadc   = correct_yield_entries/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr);//===14
    double correct_yield_integral_corr_lt_boil_fadc_err   = sqrt(correct_yield_entries)/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr);//===15

    double correct_yield_integral_corr_lt_boil_fadc_pid      = correct_yield_entries/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr * 0.86);///===16
    double correct_yield_integral_corr_lt_boil_fadc_pid_err   = sqrt(correct_yield_entries)/(charge1 * boil_corr* livetime_corr[r]* fadc_dtime_corr * 0.86);


    cyield_final->SaveAs(Form("pdfoct6/correct_yield_%d.pdf", runs[r]));

    //////////////////////////////////////////////////////////////////////////////////This is correct Yield done//////////////////////////////////


















































    double ent_hcalshould_coin =  hist_hcal_should_coin->Integral();
    double ent_hcalshould_acc =  hist_hcal_should_acc->Integral();
    double ent_hcalshould_acc_1peak =  hist_hcal_should_acc_1peak->Integral();
    double ent_hcalshould_clean =  hist_hcal_should_clean->Integral();

    //Find Bin
    // cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    double int_hcaldid_clean =  hist_hcal_did_clean->Integral(hist_hcal_did_clean->FindBin(hcaletotmin),hist_hcal_did_clean->FindBin(2));
    double int_hcalshould_clean =  hist_hcal_should_clean->Integral(hist_hcal_should_clean->FindBin(0.),hist_hcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " hcal : did FindBin / should Find Bin    =  "<<  int_hcaldid_clean<<" / "   << int_hcalshould_clean   << "  =  "<< int_hcaldid_clean/int_hcalshould_clean<<endl;
    double int_pcaldid_clean =  hist_pcal_did_clean->Integral(hist_pcal_did_clean->FindBin(0),hist_pcal_did_clean->FindBin(pcaletotmax));
    double int_pcalshould_clean =  hist_pcal_should_clean->Integral(hist_pcal_should_clean->FindBin(0),hist_pcal_should_clean->FindBin(2));
    //cout<<runs[r]<<"  "<< " pcal : did FindBin / should Find Bin    =  "<<  int_pcaldid_clean<<" / "   << int_pcalshould_clean   << "  =  "<<  int_pcaldid_clean/int_pcalshould_clean<<endl;
    // cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<<"   "<<endl;
    
    
    double ent_pcaldid_coin =  hist_pcal_did_coin->Integral();
    double ent_pcaldid_acc =  hist_pcal_did_acc->Integral();
    double ent_pcaldid_acc_1peak =  hist_pcal_did_acc_1peak->Integral();
    double ent_pcaldid_clean =  hist_pcal_did_clean->Integral();

    double ent_pcalshould_coin =  hist_pcal_should_coin->Integral();
    double ent_pcalshould_acc =  hist_pcal_should_acc->Integral();
    double ent_pcalshould_acc_1peak =  hist_pcal_should_acc_1peak->Integral();
    double ent_pcalshould_clean =  hist_pcal_should_clean->Integral();

    double hcal_eff = ent_hcaldid_clean/ent_hcalshould_clean;
    double pcal_eff = ent_pcaldid_clean/ent_pcalshould_clean;
    double hcal_eff_err = (1/ent_hcalshould_clean) * sqrt(ent_hcaldid_clean *( 1- hcal_eff ));
    double pcal_eff_err = (1/ent_pcalshould_clean) * sqrt(ent_pcaldid_clean *( 1- pcal_eff ));

    double bcm1ch = charge_sum_cut_corr/1000.0;
    double bcm1cur = charge_sum_cut_corr/tot_scal_cut_time;

    double hmsmom = hist_hmsp->GetMean();
    double shmsmom = hist_shmsp->GetMean();


    // cout<<runs[r]<<" "<<"hcal did = "<< int_hcaldid_clean<< "   "<< "pcal_did = "<<int_pcaldid_clean<<endl;
    // cout<<runs[r]<<" "<<"hcal did1 = "<< ent_hcaldid_clean<< "   "<< "pcal_did1 = "<<ent_pcaldid_clean<<endl;

    /*

      cout<<runs[r]<<"  "<< "hcal did ent    =  "<<  ent_hcaldid_coin     <<"     "<<  ent_hcaldid_acc<<    "     "<<  ent_hcaldid_acc_1peak<<    "     "<< ent_hcaldid_clean<<endl;  
      cout<<runs[r]<<"  "<< "hcal should ent =  "<<  ent_hcalshould_coin  <<"     "<<  ent_hcalshould_acc<< "     "<<  ent_hcalshould_acc_1peak<< "     "<< ent_hcalshould_clean<<endl;  
      cout<<runs[r]<<"  "<< "pcal did ent    =  "<<  ent_pcaldid_coin     <<"     "<<  ent_pcaldid_acc<<    "     "<<  ent_pcaldid_acc_1peak<<    "     "<< ent_pcaldid_clean<<endl;  
      cout<<runs[r]<<"  "<< "pcal should ent =  "<<  ent_pcalshould_coin  <<"     "<<  ent_pcalshould_acc<< "     "<<  ent_pcalshould_acc_1peak<< "     "<< ent_pcalshould_clean<<endl;  
      cout<<"  "<<endl;
      cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
      cout<<runs[r]<<"      "<<"hcal eff =  "<<ent_hcaldid_clean<<" / "<<ent_hcalshould_clean<< "     "<< hcal_eff<<endl;
      cout<<runs[r]<<"      "<<"pcal eff =  "<<ent_pcaldid_clean<<" / "<<ent_pcalshould_clean<< "     "<< pcal_eff<<endl;

      cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    */
   

    TCanvas * c2 = new TCanvas ("c2", "c2", 1000, 800);
    c2->Divide(4,3);
    c2->cd(1);gPad->SetLogz();
    hms_sh_vs_psh->Draw("colz");
    hms_sh_vs_psh->SetTitle(Form("HMS SH VS PSH %d",runs[r]));

    c2->cd(2);gPad->SetLogz();
    hms_etot_vs_rf->Draw("colz");

    c2->cd(3);gPad->SetLogz();
    shms_sh_vs_psh->Draw("colz");

    c2->cd(4);gPad->SetLogz();
    ctime_vs_rf->Draw("colz");

    c2->cd(5);gPad->SetLogz();
    etot_vs_rf->Draw("colz");

    c2->cd(6);gPad->SetLogz();
    epr_vs_rf->Draw("colz");

    c2->cd(7);gPad->SetLogz();
    ctime_vs_etot->Draw("colz");

    c2->cd(8);gPad->SetLogz();
    ctime_vs_epr->Draw("colz");

    c2->cd(9);gPad->SetLogz();
    sh_vs_rf->Draw("colz");

    c2->cd(10);gPad->SetLogz();
    hmsepr_vs_rf->Draw("colz");

    c2->cd(11);gPad->SetLogz();
    hmssh_vs_rf->Draw("colz");

    
    

    //delete c2;
    //////////////////these are base plots with no cal cut//////////////
    TCanvas * c3 = new TCanvas ("c3", "c3", 1000, 800);
    c3->Divide(4,3);
    c3->cd(1);gPad->SetLogz();
    hms_sh_vs_psh_base->Draw("colz");
    hms_sh_vs_psh_base->SetTitle(Form("HMS SH VS PSH BASE %d",runs[r]));

    c3->cd(2);gPad->SetLogz();
    hms_etot_vs_rf_base->Draw("colz");

      
    c3->cd(3);gPad->SetLogz();
    shms_sh_vs_psh_base->Draw("colz");

    c3->cd(4);gPad->SetLogz();
    ctime_vs_rf_base->Draw("colz");

    c3->cd(5);gPad->SetLogz();
    etot_vs_rf_base->Draw("colz");

    c3->cd(6);gPad->SetLogz();
    epr_vs_rf_base->Draw("colz");

    c3->cd(7);gPad->SetLogz();
    ctime_vs_etot_base->Draw("colz");

    c3->cd(8);gPad->SetLogz();
    ctime_vs_epr_base->Draw("colz");

    c3->cd(9);gPad->SetLogz();
    sh_vs_rf_base->Draw("colz");

    c3->cd(10);gPad->SetLogz();
    hmsepr_vs_rf_base->Draw("colz");

    c3->cd(11);gPad->SetLogz();
    hmssh_vs_rf_base->Draw("colz");


    c1->SaveAs(Form("pdfoct6/cal_coin_before_accsub_%d.pdf", runs[r]));
    c2->SaveAs(Form("pdfoct6/plots_2d_%d.pdf", runs[r]));
    c3->SaveAs(Form("pdfoct6/base_plots_2d_nocal_%d.pdf", runs[r]));
   
    delete c1;
    delete c2;
    delete c3;
   

    // hcernpe_vs_hmsp->Write();
    // aeronpe_vs_shmsp->Write();
    // hgcernpe_vs_shmsp->Write();

    ofstream txtfile1("txtfileoct6/hcal_xyposcut_4040_ngcer_H2.txt",ios::app);
    txtfile1<<setprecision(5)<<runs[r]<<"\t"<<PTRIG4_Rate<<"\t"<<bcm1cur<<"\t"<<bcm1ch<<"\t"<<hmsmom<<"\t"<<hcal_eff<<"\t"<<hcal_eff_err<<endl;
    ofstream txtfile2("txtfileoct6/pcal_xyposcut_4040_ngcer_H2.txt",ios::app);
    txtfile2<<setprecision(5)<<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t"<<bcm1ch<<"\t"<<shmsmom<<"\t"<<pcal_eff<<"\t"<<pcal_eff_err<<endl;
    
    //=======final
    cout<<" "<<endl;
    //////////////////////////This is printing 


    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" before sept 21 yield "<<endl;


    //cout<<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<yield_integral_uncorr<<"\t\t"<<yield_integral_corr<<"\t\t"<<yield_integral_err<<"\t\t"<<yield_entries<<"\t\t"<<yield_entries_err<<endl;//====3
    ofstream txtfile11("txtfileoct6/yield_kin13_14_allcorr.txt",ios::app);
    txtfile11<<setprecision(5)<<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<yield_integral_uncorr<<"\t\t"<<yield_integral_uncorr_err<<"\t\t"<<yield_integral_corr_lt_boil<<"\t\t"<<yield_integral_corr_lt_boil_err<<"\t\t"<<yield_integral_corr_lt_boil_fadc<<"\t\t"<<yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<yield_integral_corr_lt_boil_fadc<<"\t\t"<<yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<yield_entries<<"\t\t"<<endl;////===4

    cout <<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<yield_integral_uncorr<<"\t\t"<<yield_integral_uncorr_err<<"\t\t"<<yield_integral_corr_lt_boil<<"\t\t"<<yield_integral_corr_lt_boil_err<<"\t\t"<<yield_integral_corr_lt_boil_fadc<<"\t\t"<<yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<yield_entries<<"\t\t"<<endl;////===4
    

 
    //run rate curr charge bare_yield err yield_lt_boil err yield_lt_boil_fadc err yield_lt_boil_fadc_pid err entries



    //////////////////////////This is printing 
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<" correct latest yield sept 21 "<<endl;

    ///////////final correct yield printing/////////////17
       ofstream txtfile12("txtfileoct6/good_5367_pideff.txt",ios::app);
 txtfile12<<setprecision(5)<<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<correct_yield_integral_uncorr<<"\t\t"<<correct_yield_integral_uncorr_err<<"\t\t"<<correct_yield_integral_corr_lt_boil<<"\t\t"<<correct_yield_integral_corr_lt_boil_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;////===4

    cout <<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<correct_yield_integral_uncorr<<"\t\t"<<correct_yield_integral_uncorr_err<<"\t\t"<<correct_yield_integral_corr_lt_boil<<"\t\t"<<correct_yield_integral_corr_lt_boil_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;////===4
    
    ////Exactly Peter's correction
   ofstream txtfile22("txtfileoct6/peters_copy_corr_tightct.txt",ios::app);
    //ofstream txtfile22("txtfileYield_correct/correct_yield_newest_sept21_5367_pideff.txt",ios::app);
 txtfile22<<setprecision(5)<<runs[r]<<"\t\t"<<PTRIG1_Rate<<"\t\t"<<bcm1cur<<"\t\t"<<charge1<<"\t\t"<<correct_yield_integral_uncorr<<"\t\t"<<correct_yield_integral_uncorr_err<<"\t\t"<<all_peter_yield<<"\t\t"<<all_peter_yield_err<<"\t\t"<<endl;





    cout<<""<<endl;

    cout<<""<<endl;
    cout<<"acc *4= "<<  runs[r]<<"  "<<hist_zhad_acc->GetEntries()<<endl;
    cout<<"acc   = "<<  runs[r]<<"  "<<hist_zhad_acc->GetEntries()/4.<<endl;
    cout<<"coin   = "<<  runs[r]<<"  "<<hist_zhad_coin->GetEntries()<<endl;
    cout<<"clean counts = "<<runs[r]<<"  "<<hist_zhad_coin->GetEntries()-hist_zhad_acc->GetEntries()/4<<endl;
    cout<<"clean yield = "<<runs[r]<<"  "<<(hist_zhad_coin->GetEntries()-hist_zhad_acc->GetEntries()/4)/charge1<<endl;

    cout<<""<<endl;
    cout<<""<<endl;
    cout<<""<<endl;

    cout<<"acc *4= "<<  runs[r]<<"  "<<hist_zhad_acc->Integral()<<endl;
    cout<<"acc   = "<<  runs[r]<<"  "<<hist_zhad_acc->Integral()/4<<endl;
    cout<<"coin   = "<<  runs[r]<<"  "<<hist_zhad_coin->Integral()<<endl;

    cout<<"clean counts = "<<runs[r]<<"  "<<hist_zhad_coin->Integral()-hist_zhad_acc->Integral()/4<<endl;
    cout<<"clean yield = "<<runs[r]<<"  "<<(hist_zhad_coin->Integral()-hist_zhad_acc->Integral()/4)/charge1<<endl;

    double accidentals = hist_zhad_acc->Integral()/4;
    double coins = hist_zhad_coin->Integral();
    double cleans = coins - accidentals;
    double ratio_acc_real = accidentals/cleans;
    //double ratio_acc_real_err = (1/cleans)* sqrt(accidentals * ( 1- ratio_acc_real));
    double ratio_acc_real_err = ratio_acc_real * sqrt(1/cleans + 1/accidentals);
    double ratio_acc_coin = accidentals/coins;
    double ratio_acc_coin_err = ratio_acc_coin * sqrt(1/coins + 1/accidentals);



    cout<<""<<endl;
    cout<<"clean Int, Ent = "<<runs[r]<<"  "<<hist_yield_zhad_clean_copy->Integral()<<"   "<<hist_yield_zhad_clean_copy->GetEntries()<<endl;


    cout<<""<<endl;

    //acc/coin ratio
    ofstream txtfile13("txtfileoct6/accidentals_to_real_ratio_vs_curr_nopideff.txt",ios::app);
 cout<<runs[r]<<"\t\t"<<bcm1cur<<"\t\t"<<coins<<"\t\t"<<accidentals<<"\t\t"<<cleans<<"\t\t"<<ratio_acc_real<<"\t\t"<<ratio_acc_real_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;
 txtfile13<<runs[r]<<"\t\t"<<bcm1cur<<"\t\t"<<coins<<"\t\t"<<accidentals<<"\t\t"<<cleans<<"\t\t"<<ratio_acc_real<<"\t\t"<<ratio_acc_real_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;

ofstream txtfile14("txtfileoct6/accidentals_to_coin_and_real_ratio_vs_curr_nopideff.txt",ios::app);
// cout<<runs[r]<<"\t\t"<<bcm1cur<<"\t\t"<<coins<<"\t\t"<<accidentals<<"\t\t"<<cleans<<"\t\t"<<"\t\t"<<ratio_acc_coin<<"\t\t"<<ratio_acc_coin_err<<"\t\t"<<ratio_acc_real<<"\t\t"<<ratio_acc_real_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;
 txtfile14<<runs[r]<<"\t\t"<<bcm1cur<<"\t\t"<<coins<<"\t\t"<<accidentals<<"\t\t"<<cleans<<"\t\t"<<"\t\t"<<ratio_acc_coin<<"\t\t"<<ratio_acc_coin_err<<"\t\t"<<ratio_acc_real<<"\t\t"<<ratio_acc_real_err<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid<<"\t\t"<<correct_yield_integral_corr_lt_boil_fadc_pid_err<<"\t\t"<<correct_yield_entries<<"\t\t"<<endl;
 


 ////


    ofstream txtfiles("txtfileoct6/boiling_fadc_corr.txt",ios::app);

    txtfiles<<runs[r]<<"\t"<<currentbcm1<<"\t"<<livetime_corr[r]<<"\t\t"<< boil_corr<<"\t"<<fadc_dtime_corr<<endl;


  }//runs
  cout<<" "<<endl;

}//void



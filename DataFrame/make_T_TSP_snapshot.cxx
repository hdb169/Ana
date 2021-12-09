/*Here, you first loop over all the run groups, and then the code will look for the runs in D2, Dummy, H2; and through pos, neg, and read each runs and then perform the assigned work. db2/ratio_run_group_updated.json have run group definitions, db2/runs_info.json have the info about uns like charge, LT, and mainly offset RF, etc, and db2/all_cut.json has the cut definition file. I applied basic cuts only. 
Then, to save "T" and "TSP", first read those, and apply cuts where needed, and do a snapshot.	ROOT::RDF::RSnapshotOptions opts;
	opts.fMode = "UPDATE"; is to be done after one TTree is filled and  },opts); is required at the end of the second TTree.
*/
#include "ROOT/RDataFrame.hxx"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
#include "TCanvas.h"
#include <iostream>
#include <string>
//ROOT::EnableImplicitMT();
//more
#define ROOT_RDF_TINTERFACE   
#include "ROOT/RDataSource.hxx"

#include "ROOT/RSnapshotOptions.hxx"
// for ULong64_t
#include "TChain.h" // for checking fLoopManger->GetTree() return type
#include "TDirectory.h"
#include "TH1.h" // For Histo actions
#include "TH2.h" // For Histo actions
#include "TH3.h" // For Histo actions
#include "TProfile.h"
#include "TProfile2D.h"
#include "TStatistic.h"
//ROOT::EnableImplicitMT();
//ROOT::RDF::RSnapshotOptions opts;
//opts.fMode = "UPDATE";
//opts.fLazy = true;


//more



//first script
void make_T_TSP_snapshot(){
  json j_rungroup;
  {
    //std::ifstream ifs("db2/ratio_run_group_updated.json");
    std::ifstream ifs("db2/trash.json");
    ifs>>j_rungroup;
  }
  json j_runsinfo;
  {
    std::ifstream ifs("db2/runs_info.json");
    ifs>>j_runsinfo;
  }
  json j_cuts;
  {
    std::ifstream ifs("db2/all_cut.json");
    ifs>>j_cuts;
  }
  double H_dp_low = j_cuts["H_dp_low"].get<double>();
  double H_dp_high = j_cuts["H_dp_high"].get<double>();
  double P_dp_low = j_cuts["P_dp_low"].get<double>();
  double P_dp_high = j_cuts["P_dp_high"].get<double>();
  std::string goodTrackSHMS = "P.gtr.dp>"+std::to_string(P_dp_low)+" && P.gtr.dp<"+std::to_string(P_dp_high);
  std::string goodTrackHMS = "H.gtr.dp>"+std::to_string(H_dp_low)+" && H.gtr.dp<"+std::to_string(H_dp_high);
  std::cout<<goodTrackSHMS<<std::endl;
  std::cout<<goodTrackHMS<<std::endl;
  double SHMS_high_etottracknorm = j_cuts["P_cal_pi_etottrack_high"].get<double>();
  double SHMS_high_etracknorm = j_cuts["P_cal_pi_etrack_high"].get<double>();

  std::string piCutSHMS = (" P.cal.etottracknorm < "+std::to_string(SHMS_high_etottracknorm)+" && P.cal.etracknorm < "+ std::to_string(SHMS_high_etracknorm)).c_str();
  std::cout<<"picutSHMS "<<piCutSHMS<<std::endl;
  double P_aero = 4;
  //j_cuts["P_aero"].get<double>();
  std::string aeroCutSHMS = (" P.aero.npeSum > "+std::to_string(P_aero)).c_str();
  std::cout<<"P_aerocut "<<aeroCutSHMS<<std::endl;
  double H_cal_low = j_cuts["H_cal_low"].get<double>();
  double H_cal_high = j_cuts["H_cal_high"].get<double>();
  double H_cer = j_cuts["H_cer"].get<double>();
  std::string eCutHMS = ("H.cal.etottracknorm > "+std::to_string(H_cal_low)+" && H.cer.npeSum > "+std::to_string(H_cer)).c_str();
  std::cout<<"cCutHMS"<<eCutHMS<<std::endl;
  double H_xptar_low = j_cuts["H_xptar_low"].get<double>();
  double H_xptar_high = j_cuts["H_xptar_high"].get<double>();
  double P_xptar_low = j_cuts["P_xptar_low"].get<double>();
  double P_xptar_high = j_cuts["P_xptar_high"].get<double>();
  double H_yptar_low = j_cuts["H_yptar_low"].get<double>();
  double H_yptar_high = j_cuts["H_yptar_high"].get<double>();
  double P_yptar_low = j_cuts["P_yptar_low"].get<double>();
  double P_yptar_high = j_cuts["P_yptar_high"].get<double>();
  std::string Normal_HMS = "H.gtr.th > "+std::to_string(H_xptar_low)+" && H.gtr.th < "+std::to_string(H_xptar_high)+" && H.gtr.ph > "+std::to_string(H_yptar_low)+" && H.gtr.ph < "+std::to_string(H_yptar_high); 
  std::string Normal_SHMS = "P.gtr.th > "+std::to_string(P_xptar_low)+" && P.gtr.th < "+std::to_string(P_xptar_high)+" && P.gtr.ph > "+std::to_string(P_yptar_low)+" && P.gtr.ph < "+std::to_string(P_yptar_high); 
  std::cout<<Normal_HMS<<std::endl;
  std::cout<<Normal_SHMS<<std::endl;
  auto rf_cut = [=](double SHMS_rftime){
    double rf_pi_low,rf_pi_high; 
    rf_pi_low = 0.5;
    rf_pi_high = 1.5;
    return SHMS_rftime>rf_pi_low && SHMS_rftime<rf_pi_high;  
  };

  for(auto it = j_rungroup.begin();it!=j_rungroup.end();++it){



    int RunGroup = std::stoi(it.key());
    double SHMS_P = it.value()["shms_p"].get<double>();
    auto shms_p_calculate = [SHMS_P](double shms_dp){return SHMS_P*(1+shms_dp/100);};
    auto runjs = it.value();
    std::cout<<RunGroup<<" "<<SHMS_P<<std::endl;
    //  if(SHMS_P>3){




    ////

    std::vector<int> neg_D2,pos_D2,neg_H2,pos_H2,neg_Dummy,pos_Dummy;
    neg_D2 = runjs["neg"]["D2"].get<std::vector<int>>();
    pos_D2 = runjs["pos"]["D2"].get<std::vector<int>>();
    neg_H2 = runjs["neg"]["H2"].get<std::vector<int>>();
    pos_H2 = runjs["pos"]["H2"].get<std::vector<int>>();
    neg_Dummy = runjs["neg"]["Dummy"].get<std::vector<int>>();
    pos_Dummy = runjs["pos"]["Dummy"].get<std::vector<int>>();
    if(!neg_D2.empty() && !pos_D2.empty()){
      for(auto it = neg_D2.begin();it!=neg_D2.end();++it){
	int RunNumber = *it;
	std::cout<<RunNumber<<std::endl;
	//	std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
	//test


	std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	//found_good_file = root_file_exists(rootfile_name.c_str());
	if (!RunNumber) {
	  std::cout << "Error opening file "<< std::endl;
	  continue;
	}

	TFile file(rootfile_name.c_str());
	if(file.IsZombie()){
	  continue;
	}
	//test


	ROOT::RDataFrame d_neg_raw("T",rootfile_name);
	ROOT::RDataFrame d_neg_raw_s("TSP",rootfile_name);
	std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_neg_D2.root";

	d_neg_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
	      "P.BCM1.scalerCharge",
	      "P.BCM1.scalerChargeCut",
	      "P.1MHz.scalerTime",
	      "P.1MHz.scalerTimeCut",
	      "P.BCM1.scalerCurrent",
	      "P.1MHz.scalerTime",
	      "P.EDTM.scaler",
	      "P.pEL_CLEAN.scaler",
	      "P.pEL_REAL.scaler",
	      "P.pTRIG2.scaler",
	      "P.pTRIG3.scaler",
	      "P.pTRIG1.scaler",
	      "P.pTRIG4.scaler",
	      "P.pTRIG5.scaler",
	      "P.pTRIG6.scaler"
	      });
	ROOT::RDF::RSnapshotOptions opts;
	opts.fMode = "UPDATE";


	double offset_neg;
	offset_neg = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	auto d_neg_run = d_neg_raw
	  .Filter("g.evtyp > 3")
          .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
          .Filter(goodTrackSHMS)
          .Filter(goodTrackHMS)
          //.Filter(piCutSHMS)
          .Filter(eCutHMS)
          .Filter(aeroCutSHMS)
          .Filter(Normal_SHMS)
          .Filter(Normal_HMS)
          .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
          //.Filter([cointime_low_neg,cointime_high_neg](double cointime){return cointime>cointime_low_neg && cointime<cointime_high_neg;},{"CTime.ePiCoinTime_ROC2"})
          .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
          .Define("diff_time_mod",[offset_neg](double difftime){return std::fmod(difftime+offset_neg,4.008);},{"fptime_minus_rf"})
          .Filter(rf_cut,{"diff_time_mod"})
          .Filter("P.dc.InsideDipoleExit == 1")
          .Filter("H.dc.InsideDipoleExit == 1")
          .Filter("P.hod.goodstarttime == 1")
          .Filter("H.hod.goodstarttime == 1")
          ; 	
	d_neg_run.Snapshot("T",skim_name.c_str(),{ "P.gtr.p",
	      "H.gtr.p",
	      "P.gtr.beta",                                                                      
	      "H.gtr.beta",
	      "H.gtr.dp",                                                                        
	      "P.gtr.dp",                                                                               
	      "P.cal.eprtracknorm",                                                                    
	      "P.cal.etottracknorm",
	      "P.cal.etracknorm",
	      "P.ngcer.npeSum",
	      "P.hgcer.npeSum",
	      "P.aero.npeSum",                                       
	      "H.cal.eprtracknorm",                                 
	      "H.cal.etottracknorm",       
	      "P.cal.etotnorm",                                          
	      "H.cer.npeSum",
	      "CTime.ePiCoinTime_ROC2",
	      "H.hod.goodstarttime",
	      "P.hod.goodstarttime",
	      "P.dc.InsideDipoleExit",
	      "H.dc.InsideDipoleExit",
	      "P.hod.goodscinhit",
	      "P.hod.betanotrack",
	      "P.dc.ntrack",
	      "H.hod.goodscinhit",
	      "H.hod.betanotrack",
	      "H.dc.ntrack",
	      "T.coin.pRF_tdcTime",
	      "P.hod.fpHitsTime",             
	      "g.evtyp",
	      "H.gtr.y",
	      "P.gtr.y",
	      "T.coin.pEDTM_tdcTime",
	      "T.coin.pEDTM_tdcTimeRaw",
	      "T.coin.pEDTM_tdcTime",
	      "g.evnum",
	      "H.kin.primary.x_bj",
	      "H.kin.primary.Q2",
	      "H.kin.primary.omega",
	      "H.kin.primary.W2",
	      "P.kin.secondary.pmiss",
	      "P.kin.secondary.emiss",
	      "H.gtr.th",
	      "H.gtr.ph",
	      "P.gtr.th",
	      "P.gtr.ph",
	      "P.dc.x_fp",
	      "P.dc.y_fp",
	      "P.dc.xp_fp",
	      "P.dc.yp_fp",
	      "P.hgcer.xAtCer",
	      "P.hgcer.yAtCer",
	      "T.coin.pT2_tdcMultiplicity",
	      "T.coin.pTRIG4_ROC2_tdcTime",
	      "T.coin.pTRIG1_ROC2_tdcTime",
	      "diff_time_mod"
	      },opts);
	
      }//for neg runs done, do exactly same for posD2
      for(auto it = pos_D2.begin();it!=pos_D2.end();++it){
	int RunNumber = *it;
	std::cout<<RunNumber<<std::endl;
	//std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";
	//test

	std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	if (!RunNumber) {
	  std::cout << "Error opening file "<< std::endl;
	  continue;
	}
	//test
	TFile file(rootfile_name.c_str());
	if(file.IsZombie()){
	  continue;
	}


	ROOT::RDataFrame d_pos_raw("T",rootfile_name);
	ROOT::RDataFrame d_pos_raw_s("TSP",rootfile_name);
	std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_pos_D2.root";

	d_pos_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
	      "P.BCM1.scalerCharge",
	      "P.BCM1.scalerChargeCut",
	      "P.1MHz.scalerTime",
	      "P.1MHz.scalerTimeCut",
	      "P.BCM1.scalerCurrent",
	      "P.1MHz.scalerTime",
	      "P.EDTM.scaler",
	      "P.pEL_CLEAN.scaler",
	      "P.pEL_REAL.scaler",
	      "P.pTRIG2.scaler",
	      "P.pTRIG3.scaler",
	      "P.pTRIG1.scaler",
	      "P.pTRIG4.scaler",
	      "P.pTRIG5.scaler",
	      "P.pTRIG6.scaler"
	      });
	ROOT::RDF::RSnapshotOptions opts;
	opts.fMode = "UPDATE";

	double offset_pos;
	offset_pos = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	auto d_pos_run = d_pos_raw
	  .Filter("g.evtyp > 3")
	  .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
	  .Filter(goodTrackSHMS)
	  .Filter(goodTrackHMS)
	  //.Filter(piCutSHMS)
	  .Filter(eCutHMS)
	  .Filter(aeroCutSHMS)
	  .Filter(Normal_SHMS)
	  .Filter(Normal_HMS)
	  .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
	  //.Filter([cointime_low_pos,cointime_high_pos](double cointime){return cointime>cointime_low_pos && cointime<cointime_high_pos;},{"CTime.ePiCoinTime_ROC2"})
	  .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
	  .Define("diff_time_mod",[offset_pos](double difftime){return std::fmod(difftime+offset_pos,4.008);},{"fptime_minus_rf"})
	  .Filter(rf_cut,{"diff_time_mod"})
	  .Filter("P.dc.InsideDipoleExit == 1")
	  .Filter("H.dc.InsideDipoleExit == 1")
	  .Filter("P.hod.goodstarttime == 1")
	  .Filter("H.hod.goodstarttime == 1")
	  ; 

	
	d_pos_run.Snapshot("T",skim_name.c_str(),{"P.gtr.p",
	      "H.gtr.p",
	      "P.gtr.beta",                                                                      
	      "H.gtr.beta",
	      "H.gtr.dp",                                                                        
	      "P.gtr.dp",                                                                               
	      "P.cal.eprtracknorm",                                                                    
	      "P.cal.etottracknorm",
	      "P.cal.etracknorm",
	      "P.ngcer.npeSum",
	      "P.hgcer.npeSum",
	      "P.aero.npeSum",                                       
	      "H.cal.eprtracknorm",                                 
	      "H.cal.etottracknorm",       
	      "P.cal.etotnorm",                                          
	      "H.cer.npeSum",
	      "CTime.ePiCoinTime_ROC2",
	      "H.hod.goodstarttime",
	      "P.hod.goodstarttime",
	      "P.dc.InsideDipoleExit",
	      "H.dc.InsideDipoleExit",
	      "P.hod.goodscinhit",
	      "P.hod.betanotrack",
	      "P.dc.ntrack",
	      "H.hod.goodscinhit",
	      "H.hod.betanotrack",
	      "H.dc.ntrack",
	      "T.coin.pRF_tdcTime",
	      "P.hod.fpHitsTime",             
	      "g.evtyp",
	      "H.gtr.y",
	      "P.gtr.y",
	      "T.coin.pEDTM_tdcTime",
	      "T.coin.pEDTM_tdcTimeRaw",
	      "T.coin.pEDTM_tdcTime",
	      "g.evnum",
	      "H.kin.primary.x_bj",
	      "H.kin.primary.Q2",
	      "H.kin.primary.omega",
	      "H.kin.primary.W2",
	      "P.kin.secondary.pmiss",
	      "P.kin.secondary.emiss",
	      "H.gtr.th",
	      "H.gtr.ph",
	      "P.gtr.th",
	      "P.gtr.ph",
	      "P.dc.x_fp",
	      "P.dc.y_fp",
	      "P.dc.xp_fp",
	      "P.dc.yp_fp",
	      "P.hgcer.xAtCer",
	      "P.hgcer.yAtCer",
	      "T.coin.pT2_tdcMultiplicity",
	      "T.coin.pTRIG4_ROC2_tdcTime",
	      "T.coin.pTRIG1_ROC2_tdcTime",
	      "diff_time_mod"
	      },opts);
	

      }//for pos runs
      if(!neg_H2.empty() && !pos_H2.empty()){
	for(auto it = neg_H2.begin();it!=neg_H2.end();++it){
	  int RunNumber = *it;
	  std::cout<<RunNumber<<std::endl;
	  //std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";
	 
	  

	  std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	  if (!RunNumber) {
	    std::cout << "Error opening file "<< std::endl;
	    continue;
	  }
	  //test
	  TFile file(rootfile_name.c_str());
	  if(file.IsZombie()){
	    continue;
	  }
	  ROOT::RDataFrame d_neg_raw("T",rootfile_name);
	  ROOT::RDataFrame d_neg_raw_s("TSP",rootfile_name);
	 
	  std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_neg_H2.root";
	
	  d_neg_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
		"P.BCM1.scalerCharge",
		"P.BCM1.scalerChargeCut",
		"P.1MHz.scalerTime",
		"P.1MHz.scalerTimeCut",
		"P.BCM1.scalerCurrent",
		"P.1MHz.scalerTime",
		"P.EDTM.scaler",
		"P.pEL_CLEAN.scaler",
		"P.pEL_REAL.scaler",
		"P.pTRIG2.scaler",
		"P.pTRIG3.scaler",
		"P.pTRIG1.scaler",
		"P.pTRIG4.scaler",
		"P.pTRIG5.scaler",
		"P.pTRIG6.scaler"
		});
	  ROOT::RDF::RSnapshotOptions opts;
	  opts.fMode = "UPDATE";

	  double offset_neg;
	  offset_neg = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	  auto d_neg_run = d_neg_raw
	    .Filter("g.evtyp > 3")
	    .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
	    .Filter(goodTrackSHMS)
	    .Filter(goodTrackHMS)
	    //.Filter(piCutSHMS)
	    .Filter(eCutHMS)
	    .Filter(aeroCutSHMS)
	    .Filter(Normal_SHMS)
	    .Filter(Normal_HMS)
	    .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
	    //.Filter([cointime_low_neg,cointime_high_neg](double cointime){return cointime>cointime_low_neg && cointime<cointime_high_neg;},{"CTime.ePiCoinTime_ROC2"})
	    .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
	    .Define("diff_time_mod",[offset_neg](double difftime){return std::fmod(difftime+offset_neg,4.008);},{"fptime_minus_rf"})
	    .Filter(rf_cut,{"diff_time_mod"})
	    .Filter("P.dc.InsideDipoleExit == 1")
	    .Filter("H.dc.InsideDipoleExit == 1")
	    .Filter("P.hod.goodstarttime == 1")
	    .Filter("H.hod.goodstarttime == 1")
	    ; 
	  //d_neg_run.Snapshot("T",skim_name.c_str(),{"P.gtr.th","P.gtr.ph","P.gtr.y","P.gtr.dp","P.gtr.p","P.hgcer.xAtCer","P.hgcer.yAtCer","CTime.ePiCoinTime_ROC2","shms_p","P.cal.etottracknorm","P.cal.etracknorm","H.cal.etottracknorm","H.cal.etracknorm","P.hgcer.npeSum","diff_time_mod"});
	 
	  d_neg_run.Snapshot("T",skim_name.c_str(),{"P.gtr.p",
		"H.gtr.p",
		"P.gtr.beta",                                                                      
		"H.gtr.beta",
		"H.gtr.dp",                                                                        
		"P.gtr.dp",                                                                               
		"P.cal.eprtracknorm",                                                                    
		"P.cal.etottracknorm",
		"P.cal.etracknorm",
		"P.ngcer.npeSum",
		"P.hgcer.npeSum",
		"P.aero.npeSum",                                       
		"H.cal.eprtracknorm",                                 
		"H.cal.etottracknorm",       
		"P.cal.etotnorm",                                          
		"H.cer.npeSum",
		"CTime.ePiCoinTime_ROC2",
		"H.hod.goodstarttime",
		"P.hod.goodstarttime",
		"P.dc.InsideDipoleExit",
		"H.dc.InsideDipoleExit",
		"P.hod.goodscinhit",
		"P.hod.betanotrack",
		"P.dc.ntrack",
		"H.hod.goodscinhit",
		"H.hod.betanotrack",
		"H.dc.ntrack",
		"T.coin.pRF_tdcTime",
		"P.hod.fpHitsTime",             
		"g.evtyp",
		"H.gtr.y",
		"P.gtr.y",
		"T.coin.pEDTM_tdcTime",
		"T.coin.pEDTM_tdcTimeRaw",
		"T.coin.pEDTM_tdcTime",
		"g.evnum",
		"H.kin.primary.x_bj",
		"H.kin.primary.Q2",
		"H.kin.primary.omega",
		"H.kin.primary.W2",
		"P.kin.secondary.pmiss",
		"P.kin.secondary.emiss",
		"H.gtr.th",
		"H.gtr.ph",
		"P.gtr.th",
		"P.gtr.ph",
		"P.dc.x_fp",
		"P.dc.y_fp",
		"P.dc.xp_fp",
		"P.dc.yp_fp",
		"P.hgcer.xAtCer",
		"P.hgcer.yAtCer",
		"T.coin.pT2_tdcMultiplicity",
		"T.coin.pTRIG4_ROC2_tdcTime",
		"T.coin.pTRIG1_ROC2_tdcTime",
		"diff_time_mod"
		},opts);
	  

	}//for neg runs
	for(auto it = pos_H2.begin();it!=pos_H2.end();++it){
	  int RunNumber = *it;
	  std::cout<<RunNumber<<std::endl;
	  // std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";
	  //test
	  

	  std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	  if (!RunNumber) {
	    std::cout << "Error opening file "<< std::endl;
	    continue;
	  }
	  //test
	  TFile file(rootfile_name.c_str());
	  if(file.IsZombie()){
	    continue;
	  }
	  ROOT::RDataFrame d_pos_raw("T",rootfile_name);
	  ROOT::RDataFrame d_pos_raw_s("TSP",rootfile_name);
	  std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_pos_H2.root";
	 
	  d_pos_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
		"P.BCM1.scalerCharge",
		"P.BCM1.scalerChargeCut",
		"P.1MHz.scalerTime",
		"P.1MHz.scalerTimeCut",
		"P.BCM1.scalerCurrent",
		"P.1MHz.scalerTime",
		"P.EDTM.scaler",
		"P.pEL_CLEAN.scaler",
		"P.pEL_REAL.scaler",
		"P.pTRIG2.scaler",
		"P.pTRIG3.scaler",
		"P.pTRIG1.scaler",
		"P.pTRIG4.scaler",
		"P.pTRIG5.scaler",
		"P.pTRIG6.scaler"
		});
	  ROOT::RDF::RSnapshotOptions opts;
	  opts.fMode = "UPDATE";

	  double offset_pos;
	  offset_pos = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	  auto d_pos_run = d_pos_raw
	    .Filter("g.evtyp > 3")
	    .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
	    .Filter(goodTrackSHMS)
	    .Filter(goodTrackHMS)
	    //.Filter(piCutSHMS)
	    .Filter(eCutHMS)
	    .Filter(aeroCutSHMS)
	    .Filter(Normal_SHMS)
	    .Filter(Normal_HMS)
	    .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
	    //.Filter([cointime_low_pos,cointime_high_pos](double cointime){return cointime>cointime_low_pos && cointime<cointime_high_pos;},{"CTime.ePiCoinTime_ROC2"})
	    .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
	    .Define("diff_time_mod",[offset_pos](double difftime){return std::fmod(difftime+offset_pos,4.008);},{"fptime_minus_rf"})
	    .Filter(rf_cut,{"diff_time_mod"})
	    .Filter("P.dc.InsideDipoleExit == 1")
	    .Filter("H.dc.InsideDipoleExit == 1")
	    .Filter("P.hod.goodstarttime == 1")
	    .Filter("H.hod.goodstarttime == 1")
	    ; 
	  //d_pos_run.Snapshot("T",skim_name.c_str(),{"P.gtr.th","P.gtr.ph","P.gtr.y","P.gtr.dp","P.gtr.p","P.hgcer.xAtCer","P.hgcer.yAtCer","CTime.ePiCoinTime_ROC2","shms_p","P.cal.etottracknorm","P.cal.etracknorm","H.cal.etottracknorm","H.cal.etracknorm","P.hgcer.npeSum","diff_time_mod"});
	 
	  d_pos_run.Snapshot("T",skim_name.c_str(),{"P.gtr.p",
		"H.gtr.p",
		"P.gtr.beta",                                                                      
		"H.gtr.beta",
		"H.gtr.dp",                                                                        
		"P.gtr.dp",                                                                               
		"P.cal.eprtracknorm",                                                                    
		"P.cal.etottracknorm",
		"P.cal.etracknorm",
		"P.ngcer.npeSum",
		"P.hgcer.npeSum",
		"P.aero.npeSum",                                       
		"H.cal.eprtracknorm",                                 
		"H.cal.etottracknorm",       
		"P.cal.etotnorm",                                          
		"H.cer.npeSum",
		"CTime.ePiCoinTime_ROC2",
		"H.hod.goodstarttime",
		"P.hod.goodstarttime",
		"P.dc.InsideDipoleExit",
		"H.dc.InsideDipoleExit",
		"P.hod.goodscinhit",
		"P.hod.betanotrack",
		"P.dc.ntrack",
		"H.hod.goodscinhit",
		"H.hod.betanotrack",
		"H.dc.ntrack",
		"T.coin.pRF_tdcTime",
		"P.hod.fpHitsTime",             
		"g.evtyp",
		"H.gtr.y",
		"P.gtr.y",
		"T.coin.pEDTM_tdcTime",
		"T.coin.pEDTM_tdcTimeRaw",
		"T.coin.pEDTM_tdcTime",
		"g.evnum",
		"H.kin.primary.x_bj",
		"H.kin.primary.Q2",
		"H.kin.primary.omega",
		"H.kin.primary.W2",
		"P.kin.secondary.pmiss",
		"P.kin.secondary.emiss",
		"H.gtr.th",
		"H.gtr.ph",
		"P.gtr.th",
		"P.gtr.ph",
		"P.dc.x_fp",
		"P.dc.y_fp",
		"P.dc.xp_fp",
		"P.dc.yp_fp",
		"P.hgcer.xAtCer",
		"P.hgcer.yAtCer",
		"T.coin.pT2_tdcMultiplicity",
		"T.coin.pTRIG4_ROC2_tdcTime",
		"T.coin.pTRIG1_ROC2_tdcTime",
		"diff_time_mod"
		},opts);
	 
	}//for pos runs
      }//if h2 runs exist
      for(auto it = neg_Dummy.begin();it!=neg_Dummy.end();++it){
	int RunNumber = *it;
	std::cout<<RunNumber<<std::endl;
	//std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";


	std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	if (!RunNumber) {
	  std::cout << "Error opening file "<< std::endl;
	  continue;
	}
	//test
	TFile file(rootfile_name.c_str());
	if(file.IsZombie()){
	  continue;
	}

	ROOT::RDataFrame d_neg_raw("T",rootfile_name);
	ROOT::RDataFrame d_neg_raw_s("TSP",rootfile_name);
	std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_neg_Dummy.root";

	d_neg_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
	      "P.BCM1.scalerCharge",
	      "P.BCM1.scalerChargeCut",
	      "P.1MHz.scalerTime",
	      "P.1MHz.scalerTimeCut",
	      "P.BCM1.scalerCurrent",
	      "P.1MHz.scalerTime",
	      "P.EDTM.scaler",
	      "P.pEL_CLEAN.scaler",
	      "P.pEL_REAL.scaler",
	      "P.pTRIG2.scaler",
	      "P.pTRIG3.scaler",
	      "P.pTRIG1.scaler",
	      "P.pTRIG4.scaler",
	      "P.pTRIG5.scaler",
	      "P.pTRIG6.scaler"
	      });
	ROOT::RDF::RSnapshotOptions opts;
	opts.fMode = "UPDATE";

	double offset_neg;
	offset_neg = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	auto d_neg_run = d_neg_raw
	  .Filter("g.evtyp > 3")
	  .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
	  .Filter(goodTrackSHMS)
	  .Filter(goodTrackHMS)
	  //.Filter(piCutSHMS)
	  .Filter(eCutHMS)
	  .Filter(aeroCutSHMS)
	  .Filter(Normal_SHMS)
	  .Filter(Normal_HMS)
	  .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
	  //.Filter([cointime_low_neg,cointime_high_neg](double cointime){return cointime>cointime_low_neg && cointime<cointime_high_neg;},{"CTime.ePiCoinTime_ROC2"})
	  .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
	  .Define("diff_time_mod",[offset_neg](double difftime){return std::fmod(difftime+offset_neg,4.008);},{"fptime_minus_rf"})
	  .Filter(rf_cut,{"diff_time_mod"})
	  .Filter("P.dc.InsideDipoleExit == 1")
	  .Filter("H.dc.InsideDipoleExit == 1")
	  .Filter("P.hod.goodstarttime == 1")
	  .Filter("H.hod.goodstarttime == 1")
	  ; 


	d_neg_run.Snapshot("T",skim_name.c_str(),{"P.gtr.p",
	      "H.gtr.p",
	      "P.gtr.beta",                                                                      
	      "H.gtr.beta",
	      "H.gtr.dp",                                                                        
	      "P.gtr.dp",                                                                               
	      "P.cal.eprtracknorm",                                                                    
	      "P.cal.etottracknorm",
	      "P.cal.etracknorm",
	      "P.ngcer.npeSum",
	      "P.hgcer.npeSum",
	      "P.aero.npeSum",                                       
	      "H.cal.eprtracknorm",                                 
	      "H.cal.etottracknorm",       
	      "P.cal.etotnorm",                                          
	      "H.cer.npeSum",
	      "CTime.ePiCoinTime_ROC2",
	      "H.hod.goodstarttime",
	      "P.hod.goodstarttime",
	      "P.dc.InsideDipoleExit",
	      "H.dc.InsideDipoleExit",
	      "P.hod.goodscinhit",
	      "P.hod.betanotrack",
	      "P.dc.ntrack",
	      "H.hod.goodscinhit",
	      "H.hod.betanotrack",
	      "H.dc.ntrack",
	      "T.coin.pRF_tdcTime",
	      "P.hod.fpHitsTime",             
	      "g.evtyp",
	      "H.gtr.y",
	      "P.gtr.y",
	      "T.coin.pEDTM_tdcTime",
	      "T.coin.pEDTM_tdcTimeRaw",
	      "T.coin.pEDTM_tdcTime",
	      "g.evnum",
	      "H.kin.primary.x_bj",
	      "H.kin.primary.Q2",
	      "H.kin.primary.omega",
	      "H.kin.primary.W2",
	      "P.kin.secondary.pmiss",
	      "P.kin.secondary.emiss",
	      "H.gtr.th",
	      "H.gtr.ph",
	      "P.gtr.th",
	      "P.gtr.ph",
	      "P.dc.x_fp",
	      "P.dc.y_fp",
	      "P.dc.xp_fp",
	      "P.dc.yp_fp",
	      "P.hgcer.xAtCer",
	      "P.hgcer.yAtCer",
	      "T.coin.pT2_tdcMultiplicity",
	      "T.coin.pTRIG4_ROC2_tdcTime",
	      "T.coin.pTRIG1_ROC2_tdcTime",
	      "diff_time_mod"
	      },opts);
	
      }//for neg runs
      for(auto it = pos_Dummy.begin();it!=pos_Dummy.end();++it){
	int RunNumber = *it;
	std::cout<<RunNumber<<std::endl;
	//std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";
	//test

	std::string rootfile_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/newhcana/run_"+std::to_string(RunNumber)+"_-1.root";//input ROOTfiles
      
	if (!RunNumber) {
	  std::cout << "Error opening file "<< std::endl;
	  continue;
	}
	TFile file(rootfile_name.c_str());
	if(file.IsZombie()){
	  continue;
	}

	//test

	ROOT::RDataFrame d_pos_raw("T",rootfile_name);
	ROOT::RDataFrame d_pos_raw_s("TSP",rootfile_name);
	std::string skim_name = "/lustre19/expphy/volatile/hallc/c-csv/hdbhatt/ROOTfiles/skimROOTfiles/run_"+std::to_string(RunNumber)+"_pos_Dummy.root";

	d_pos_raw_s.Snapshot("TSP",skim_name.c_str(),{"evNumber",
	      "P.BCM1.scalerCharge",
	      "P.BCM1.scalerChargeCut",
	      "P.1MHz.scalerTime",
	      "P.1MHz.scalerTimeCut",
	      "P.BCM1.scalerCurrent",
	      "P.1MHz.scalerTime",
	      "P.EDTM.scaler",
	      "P.pEL_CLEAN.scaler",
	      "P.pEL_REAL.scaler",
	      "P.pTRIG2.scaler",
	      "P.pTRIG3.scaler",
	      "P.pTRIG1.scaler",
	      "P.pTRIG4.scaler",
	      "P.pTRIG5.scaler",
	      "P.pTRIG6.scaler"
	      });
	ROOT::RDF::RSnapshotOptions opts;
	opts.fMode = "UPDATE";

	double offset_pos;
	offset_pos = j_runsinfo[(std::to_string(RunNumber)).c_str()]["offset"].get<double>();
	auto d_pos_run = d_pos_raw
	  .Filter("g.evtyp > 3")
	  .Define("shms_p",shms_p_calculate,{"P.gtr.dp"})
	  .Filter(goodTrackSHMS)
	  .Filter(goodTrackHMS)
	  //.Filter(piCutSHMS)
	  .Filter(eCutHMS)
	  .Filter(aeroCutSHMS)
	  .Filter(Normal_SHMS)
	  .Filter(Normal_HMS)
	  .Define("fptime_minus_rf","P.hod.starttime - T.coin.pRF_tdcTime")
	  //.Filter([cointime_low_pos,cointime_high_pos](double cointime){return cointime>cointime_low_pos && cointime<cointime_high_pos;},{"CTime.ePiCoinTime_ROC2"})
	  .Define("diff_time_mod_beforeshift",[](double difftime){return std::fmod(difftime,4.008);},{"fptime_minus_rf"})
	  .Define("diff_time_mod",[offset_pos](double difftime){return std::fmod(difftime+offset_pos,4.008);},{"fptime_minus_rf"})
	  .Filter(rf_cut,{"diff_time_mod"})
	  .Filter("P.dc.InsideDipoleExit == 1")
	  .Filter("H.dc.InsideDipoleExit == 1")
	  .Filter("P.hod.goodstarttime == 1")
	  .Filter("H.hod.goodstarttime == 1")
	  ; 
	//  d_pos_run.Snapshot("T",skim_name.c_str(),{"P.gtr.th","P.gtr.ph","P.gtr.y","P.gtr.dp","P.gtr.p","P.hgcer.xAtCer","P.hgcer.yAtCer","CTime.ePiCoinTime_ROC2","shms_p","P.cal.etottracknorm","P.cal.etracknorm","H.cal.etottracknorm","H.cal.etracknorm","P.hgcer.npeSum","diff_time_mod"});
	
	d_pos_run.Snapshot("T",skim_name.c_str(),{"P.gtr.p",
	      "H.gtr.p",
	      "P.gtr.beta",                                                                      
	      "H.gtr.beta",
	      "H.gtr.dp",                                                                        
	      "P.gtr.dp",                                                                               
	      "P.cal.eprtracknorm",                                                                    
	      "P.cal.etottracknorm",
	      "P.cal.etracknorm",
	      "P.ngcer.npeSum",
	      "P.hgcer.npeSum",
	      "P.aero.npeSum",                                       
	      "H.cal.eprtracknorm",                                 
	      "H.cal.etottracknorm",       
	      "P.cal.etotnorm",                                          
	      "H.cer.npeSum",
	      "CTime.ePiCoinTime_ROC2",
	      "H.hod.goodstarttime",
	      "P.hod.goodstarttime",
	      "P.dc.InsideDipoleExit",
	      "H.dc.InsideDipoleExit",
	      "P.hod.goodscinhit",
	      "P.hod.betanotrack",
	      "P.dc.ntrack",
	      "H.hod.goodscinhit",
	      "H.hod.betanotrack",
	      "H.dc.ntrack",
	      "T.coin.pRF_tdcTime",
	      "P.hod.fpHitsTime",             
	      "g.evtyp",
	      "H.gtr.y",
	      "P.gtr.y",
	      "T.coin.pEDTM_tdcTime",
	      "T.coin.pEDTM_tdcTimeRaw",
	      "T.coin.pEDTM_tdcTime",
	      "g.evnum",
	      "H.kin.primary.x_bj",
	      "H.kin.primary.Q2",
	      "H.kin.primary.omega",
	      "H.kin.primary.W2",
	      "P.kin.secondary.pmiss",
	      "P.kin.secondary.emiss",
	      "H.gtr.th",
	      "H.gtr.ph",
	      "P.gtr.th",
	      "P.gtr.ph",
	      "P.dc.x_fp",
	      "P.dc.y_fp",
	      "P.dc.xp_fp",
	      "P.dc.yp_fp",
	      "P.hgcer.xAtCer",
	      "P.hgcer.yAtCer",
	      "T.coin.pT2_tdcMultiplicity",
	      "T.coin.pTRIG4_ROC2_tdcTime",
	      "T.coin.pTRIG1_ROC2_tdcTime",
	      "diff_time_mod"
	      },opts);  


      }//for pos runs
    } //if normal production runs      

    // }//if momentum is greater than 3
  }//loop over all rungroups
}


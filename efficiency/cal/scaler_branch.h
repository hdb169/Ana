Double_t  Scal_evNumber;
ss->SetBranchAddress("evNumber",&Scal_evNumber);
Double_t  Scal_BCM4B_charge;
ss->SetBranchAddress("P.BCM4B.scalerCharge",&Scal_BCM4B_charge);
Double_t  Scal_BCM4B_current;
ss->SetBranchAddress("P.BCM4B.scalerCurrent",&Scal_BCM4B_current);
Double_t  Scal_BCM1_charge;
ss->SetBranchAddress("P.BCM1.scalerCharge",&Scal_BCM1_charge);

/* //FOR LT start */
/* Double_t bcm1ch; */
/* ss->SetBranchAddress("P.BCM1.scalerCharge",&bcm1ch); */
/* Double_t bcm1chcut; */
/* ss->SetBranchAddress("P.BCM1.scalerChargeCut",&bcm1chcut); */
/* Double_t scalertime; */
/* ss->SetBranchAddress("P.1MHz.scalerTime", &scalertime); */
/* Double_t scalertimecut; */
/* ss->SetBranchAddress("P.1MHz.scalerTimeCut",&scalertimecut); */
/* ///////for LT done */

Double_t  Scal_BCM1_current;
ss->SetBranchAddress("P.BCM1.scalerCurrent",&Scal_BCM1_current);
Double_t  Scal_time;
ss->SetBranchAddress("P.1MHz.scalerTime",&Scal_time);
Double_t  Scal_EDTM;
ss->SetBranchAddress("P.EDTM.scaler",&Scal_EDTM);
Double_t  Scal_hEL_CLEAN;
ss->SetBranchAddress("P.pEL_CLEAN.scaler",&Scal_hEL_CLEAN);
Double_t  Scal_hEL_REAL;
ss->SetBranchAddress("P.pEL_REAL.scaler",&Scal_hEL_REAL);
Double_t  Scal_TRIG2;
ss->SetBranchAddress("P.pTRIG2.scaler",&Scal_TRIG2);
Double_t  Scal_TRIG3;
ss->SetBranchAddress("P.pTRIG3.scaler",&Scal_TRIG3);
Double_t  Scal_TRIG1;
ss->SetBranchAddress("P.pTRIG1.scaler",&Scal_TRIG1);
Double_t  Scal_TRIG4;
ss->SetBranchAddress("P.pTRIG4.scaler",&Scal_TRIG4);
Double_t  Scal_TRIG5;
ss->SetBranchAddress("P.pTRIG5.scaler",&Scal_TRIG5);
Double_t  Scal_TRIG6;
ss->SetBranchAddress("P.pTRIG6.scaler",&Scal_TRIG6);
Double_t  Scal_pHGCER;
ss->SetBranchAddress("P.HCER.scaler",&Scal_pHGCER);
Double_t  Scal_Splane[4];
ss->SetBranchAddress("P.S1X.scaler",&Scal_Splane[0]);
ss->SetBranchAddress("P.S1Y.scaler",&Scal_Splane[1]);
ss->SetBranchAddress("P.S2X.scaler",&Scal_Splane[2]);
ss->SetBranchAddress("P.S2Y.scaler",&Scal_Splane[3]);

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
Double_t event_flag[20000];
Double_t scal_event_number[20000];
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
Double_t tot_scal_pHGCER=0;
Double_t tot_scal_cut_pHGCER=0;
Double_t prev_pHGCER=0;
Double_t tot_scal_cut_TRIG6=0;
Double_t threshold_cut=5.0;
Double_t minimumcur_cut=5.0;//

//
Double_t tot_scal_Splane[4]={0,0,0,0};
Double_t prev_Splane[4]={0,0,0,0};
Double_t tot_scal_cut_Splane[4]={0,0,0,0};
//
Double_t tot_scal_time=0;
Double_t prev_time=0;

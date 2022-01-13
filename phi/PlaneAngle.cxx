//This is what I got from Harut on Jan13 for the defination of phi angle.

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"

//-------------------------------------------------------------
// functions:

// calculate angle between two planes, spanned by 3-vectors (A,B) and (C,D)
static Double_t PlaneAngle(TVector3 vA, TVector3 vB, TVector3 vC, TVector3 vD) {
  TVector3 crossAB = vA.Cross(vB); // AxB
  TVector3 crossCD = vC.Cross(vD); // CxD
  Double_t sgn = crossAB.Dot(vD); // (AxB).D
  if(fabs(sgn)<0.00001) {
    //cerr << "WARNING: Kinematics:PlaneAngle (AxB).D=0" << endl;
    return -10000;
  };
  sgn /= fabs(sgn); // sign of (AxB).D
  Double_t numer = crossAB.Dot(crossCD); // (AxB).(CxD)
  Double_t denom = crossAB.Mag() * crossCD.Mag(); // |AxB|*|CxD|
  if(fabs(denom)<0.00001) {
    //cerr << "WARNING: Kinematics:PlaneAngle denominator=0" << endl;
    return -10000;
  };
  return sgn * TMath::ACos(numer/denom);
};

// shift angle to the range [-PI,+PI]
static Double_t AdjAngle(Double_t ang) {
  while(ang>TMath::Pi()) ang-=2*TMath::Pi();
  while(ang<-TMath::Pi()) ang+=2*TMath::Pi();
  return ang;
};

//-------------------------------------------------------------
// usage:

// get 4-momentum vector `q`, which requires:
// - `TLorentzVector vecEleBeam`, the beam 4-momentum
// - `TLorentzVector vecElectron`, the scattered electron 4-momentum
// - these momenta should be in the target (ion) rest frame, or any frame 
//   that can be reached from this frame by a boost along `q` (e.g., Breit frame)
TLorentzVector vecQ = vecEleBeam - vecElectron;

// calculate phiH for a hadron with 4-momentum `vecHadron`
// - TLorentzVector::Vect() returns the 3-momentum TVector3 from a 4-vector
// - `AdjAngle` is likely not needed, but good for safety
Double_t phiH = AdjAngle(PlaneAngle(
    vecQ.Vect(), vecElectron.Vect(),
    vecQ.Vect(), vecHadron.Vect()
    ));

// calculate phiS, assuming proton target is spin up
TLorentzVector vecSpin;
vecSpin.SetXYZT(0,1,0,0); // Pauli-Lubanski pseudovector for spin up, in target rest frame
Double_t phiS = AdjAngle(PlaneAngle(
    vecQ.Vect(), vecElectron.Vect(),
    vecQ.Vect(), vecSpin.Vect()
    ));

// usage of `AdjAngle` is necessary in cases such as these, for example if you are filling histograms:
Double_t phiCollins = AdjAngle(phiH+phiS);
Double_t phiSivers  = AdjAngle(phiH-phiS);

// part of reac_calc
// author: Ulrike Hager

#include <cmath>
#include "nonresonant.h"


nonresonant::nonresonant()
  :Z0(0)
  ,Z1(0)
  ,Sfactor(-1)
  ,Sprime(-1)
  ,reduced_mass(0)
{
}

nonresonant::nonresonant(int proton1, int proton2)
  :Z0(proton1)
  ,Z1(proton2)
  ,Sfactor(-1)
  ,Sprime(-1)
  ,reduced_mass(0)
{
}

nonresonant::~nonresonant()
{
}

double
nonresonant::CalcRate(double temp)
{
  double rate = -1;
  double temp9 = temp/((double)1e9) ; // in GK
  double temp6 = temp/((double)1e6) ; // in MK
  double zza = Z0*Z0*Z1*Z1 * reduced_mass;
  
//////////
// Following Iliadis "Nuclear Physics of Stars" Eq. 3.94, but ignoring S'' //
///////////
  double SfactorM = Sfactor/1000.0;
  double C1 = 7.8324e9 * pow(zza,1.0/6.0) * SfactorM / sqrt(reduced_mass);
  double C2 = 4.2475 * pow(zza,1.0/3.0);
  double C3 = 9.81e-2 * pow(zza,-1.0/3.0);
  double C4 = 0.1220 * Sprime/SfactorM * pow(zza,1.0/3.0);
  double C5 = 8.377e-2 * Sprime/SfactorM;
  double exponent = -1 * C2 * pow(temp9,-1.0/3.0);
  //  cout << "[nonresonant::CalcRate] at " << temp9 << " basic: " << C1*pow(temp9,-2.0/3.0) * exp(exponent) << " - higher " << C3*pow(temp9,1.0/3.0) << "\t" << C4*pow(temp9,2.0/3.0) << "\t" << C5*temp9 << endl;
  rate = C1*pow(temp9,-2.0/3.0) * exp(exponent) * (1 + C3*pow(temp9,1.0/3.0) + C4*pow(temp9,2.0/3.0) + C5*temp9 );
 
  /*
//////////
// Following Longland et al. (2010) NP, DOI: 10.1016/j.nuclphysa.2010.04.008  eq. 6,7,8 (should be same as Iliadis? Needs debugging)
//////////
  double tau = 4.2487 * pow(zza/temp9,1.0/3.0);
  double E0 = 0.1220 * pow(zza*temp9*temp9,1.0/3.0);
  double mult1 = E0 + 35.0/36.0 * boltzmann * temp;
  double Seff = SfactorM * ( 1+ 5.0/(12.0*tau) + Sprime/SfactorM * mult1);
  rate = 4.339e8/(Z0*Z1) * 1/reduced_mass *Seff * exp(-tau) * tau*tau;
 */
  /*
//////////
// Following http://www2.astro.psu.edu/users/rbc/a534/lec11.pdf , but multiplied with N_A (don't use this!)
//////////
  double afactor = 42.49 * pow(zza,1.0/3.0);
  double exponent = -afactor * pow(temp6,-1.0/3.0);
  rate = 6.0221e23 * 0.72e-18 * afactor*afactor * Sfactor / (Z0*Z1*reduced_mass) * exp(exponent) / pow(temp6,2.0/3.0);
  */
  /*
//////////
// Following http://www.jinaweb.org/docs/Nuclear_Astrophysics_II.pdf (doesn't have S')
//////////
  double mult1 = Z0*Z1/(reduced_mass*temp9*temp9);
  //  double exponent = -4.2487 * pow(zza/temp9,1.0/3.0);
  //rate = 7.83e9 * pow(mult1,1.0/3.0) * Sfactor/1000.0 * exp(exponent);   
  double exponent = -4.2475 * pow(zza/temp9,1.0/3.0);                // using const factors from Iliadis
  rate = 7.8324e9 * pow(mult1,1.0/3.0) * Sfactor/1000.0 * exp(exponent);   
  */
  rate_for_temp.insert(pair<double,double>(temp, rate));
  return rate;
}

double
nonresonant::GetRate(double temp)
{
  double rateT = -1;
  map<double, double>::iterator it;
  it = rate_for_temp.find(temp);
  if (it == rate_for_temp.end()){
    cout << "Nonresonant: no rate at T= " << temp << endl;
  }
  else {
    rateT = rate_for_temp.find(temp)->second;
  }
  return rateT;
}

void
nonresonant::PrintProperties()
{
  cout << "# Proton numbers: " << Z0 << "\t" << Z1 << endl;
  cout << "# Nonresonant S-factor: S = " << Sfactor << " MeVb - S' = " << Sprime << " b" << endl;

}

int
nonresonant::SetProtons(int pro1, int pro2)
{
  Z0=pro1;
  Z1=pro2;
  return 0;
}

int
nonresonant::SetProtons(vector<int> protons)
{
  int value = -1;
  if (protons.size() != 2) {
    cout << "Needed: 2 proton numbers in configuration file. Found: " << protons.size() << endl; 
    value = 1;
  }
  else {
    Z0 = protons[0];
    Z1 = protons[1];
    value = 0;
  }
  return value;
}

void
nonresonant::SetSfactors(vector<double> s)
{
  Sfactor = s[0];
  if (s.size() > 1) Sprime = s[1];
  else Sprime = 0;
 
}

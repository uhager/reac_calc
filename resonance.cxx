// part of reac_calc
// author: Ulrike Hager


#include<iostream>
#include <cmath>
#include "resonance.h"

//---- resonance
resonance::resonance(void)
  :energy(-1)
  ,omegagamma(-1)
{
  energyMeV = energy;
}

//---- resonance(e,og)
resonance::resonance(double newE, double newOG)
  :energy(newE)
  ,omegagamma(newOG)
{
  energyMeV = energy / 1000.0;
}

//---- ~resonance
resonance::~resonance(void)
{
}

double
resonance::CalcRate(double temp, double reduced_mass)
{
//////////
// Following Iliadis "Nuclear Physics of Stars" Eq. 3.114 //
// fixed using: http://www.jinaweb.org/docs/Nuclear_Astrophysics_II.pdf
///////////
  
  double temp9 = temp/((double)1e9);
  double rate;
  double exponent = -11.605 * energyMeV / temp9;
  rate = 1.5399e11 * pow((reduced_mass * temp9), -3.0/2.0) * omegagamma/((double)1e6) * exp(exponent);
  rate_for_temp.insert(pair<double,double>(temp, rate));
  return rate;
}

double
resonance::GetRate(double temp)
{
  double rateT = -1;
  map<double, double>::iterator it;
  it = rate_for_temp.find(temp);
  if (it == rate_for_temp.end()){
    cout << "Resonance at " << energy << " no rate at T= " << temp << endl;
  }
  else {
    rateT = rate_for_temp.find(temp)->second;
  }
  return rateT;
}

//resonance::PrintProperties
void
resonance::PrintProperties()
{
  cout << "# " << energy << " - " << omegagamma << endl;
}

double
resonance::SetRate(double temp, double rate)
{
  rate_for_temp.insert(pair<double,double>(temp, rate));
}

// part of reac_calc
// author: Ulrike Hager

#ifndef NONRESONANT_H
#define NONRESONANT_H

#include <vector>
#include <map>
#include <iostream>

using namespace std;

const double boltzmann = 0.086173; // MeV/K

class nonresonant
{
 public:
  nonresonant();
  nonresonant(int Z0, int Z1);
  ~nonresonant();
  double CalcRate(double temp);
  double GetRate(double temp);
  double GetSfactor(){return Sfactor;}
  void PrintProperties();
  void SetSfactor(double s){Sfactor = s;}
  void SetSprime(double s){Sprime = s;}
  void SetSfactors(vector<double> s);
  int SetProtons(int pro1, int pro2);
  int SetProtons(vector<int> protons);
  void SetReducedMass(double a){reduced_mass = a;}
  
 private:
  int Z0;
  int Z1;
  double Sfactor;
  double Sprime;
  double reduced_mass;
  map<double,double> rate_for_temp ;
};


#endif /* NONRESONANT_H */

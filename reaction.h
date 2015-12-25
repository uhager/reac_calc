// part of reac_calc
// author: Ulrike Hager

#ifndef REACTION_H
#define REACTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "resonance.h"
#include "nonresonant.h"

using namespace std;

class reaction
{
 public:
  reaction(void);
  reaction(int mass1, int mass2);
  ~reaction(void);

  void AddResonance(double energy, double omegagamma);
  void CalcRates(double temp);
  int CalcReducedMass(vector<int> masses);
  int ParseConfig(istream& pStream);
  int ParseResonances(istream& pStream);
  void PrintProperties();
  void PrintResonanceEnergies();
  void PrintRates(double temp);
  
 private:
  double reduced_mass;
  vector<resonance*> resonances;
  nonresonant *nonres;
};


#endif /* REACTION_H */

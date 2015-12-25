// part of reac_calc
// author: Ulrike Hager

#ifndef RESONANCE_H
#define RESONANCE_H

#include <map>

using namespace std;

class resonance
{
public:                         //----- public ---------------------
  resonance(void);
  resonance (double newE, double newOG);
  ~resonance(void);
  
  double GetE() {return energy;}
  double GetOG() {return omegagamma;}
  double CalcRate(double temp, double reduced_mass);
  double GetRate(double temp);
  void PrintProperties();
  double SetRate(double temp, double rate);
  
protected:                      //----- protected ------------------
  double energy;
  double energyMeV;
  double omegagamma;
  map<double,double> rate_for_temp ;
  
private:                        //----- private --------------------
  //                                        resonance(const resonance& pToCopy);
  //resonance&                               operator = (const resonance& pToCopy);
};

#endif /* RESONANCE_H */

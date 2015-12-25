// part of reac_calc
// author: Ulrike Hager

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "reaction.h"

reaction::reaction(void)
  :reduced_mass(-1)
{
  nonres = new nonresonant();
}
reaction::reaction(int mass1, int mass2)
{
  reduced_mass = (mass1 * mass2) / (mass1 + mass2);
}

//---- ~reaction
reaction::~reaction(void)
{
}


void
reaction::AddResonance(double energy, double omegagamma)
{
  resonance *ToAdd = new resonance(energy, omegagamma);
  resonances.push_back(ToAdd);
}

void
reaction::CalcRates(double temp)
{
  for (auto res : resonances) res->CalcRate(temp,reduced_mass);
  if (nonres->GetSfactor() > 0 ) nonres->CalcRate(temp);
}

int
reaction::CalcReducedMass(vector<int> masses)
{
  int value = -1;
  if (masses.size() != 2) {
    cout << "Needed: 2 masses in configuration file. Found: " << masses.size() << endl; 
    value = 1;
  }
  else {
    reduced_mass = (masses[0] * masses[1]) / ((double)masses[0] + (double)masses[1]);
    value = 0;
  }
  nonres->SetReducedMass(reduced_mass);
  return value;
}

//reaction::ParseResonances
int
reaction::ParseResonances(istream& pStream)
{
  //  cout << "[reaction::ParseResonances]" << endl;
  string line, token;
  bool	bail = false;
  getline(pStream,line);
  while ( pStream && !bail)
    {
      istringstream stream(line.c_str());
      stream >> token;
      if ( token == "" || token[0] == '#')
	{
	  //comment or blank
	}
      else if ( token.compare("end") == 0)
	bail = true;
      else {
	double energy, omegagamma;
	istringstream ( token ) >> energy;
	stream >>  omegagamma;
	resonances.push_back(new resonance(energy,omegagamma));
      }
      if ( !bail)
	getline(pStream,line);
    }
  return 0;
}

// reaction::PrintProperties
void
reaction::PrintProperties()
{
  cout << "# ----------" << endl;
  cout << "# Reaction properties" << endl;
  cout << "# Reduced mass " << reduced_mass << endl;
  cout << "# Resonances:" << endl;
  for (auto res : resonances) res->PrintProperties();
  cout << "# number of resonances: " << resonances.size() << endl;
  cout << "# Non-resonant:" << endl;
  nonres->PrintProperties();
  cout << "# ----------" << endl;
}

// reaction::ReadConfig
int
reaction::ParseConfig(istream& pStream)
{
  //  cout << "[reaction::ReadConfig]" << endl;
  string line, token;
  bool	bail = false;
  getline(pStream,line);
  while ( pStream && !bail)
    {
      istringstream stream(line.c_str());
      stream >> token;
      //      cout << "[reaction::ReadConfig]" << "line: "<< line << " token: " << token << endl;
      if ( token == "" || token[0] == '#')
	{
	  //comment or blank
	}
      else if ( token.compare("end") == 0)
	bail = true;
      else if (token == "masses"){
	  vector<int> masses;
	  while ( !stream.eof() ) {
	    masses.push_back(0);
	    stream >> masses.back();
	  }
	  int check = CalcReducedMass(masses);
	  if (check != 0) return 1;
      }
      else if (token == "protons"){
	  vector<int> protons;
	  while ( !stream.eof() ) {
	    protons.push_back(0);
	    stream >> protons.back();
	  }
	  int check = nonres->SetProtons(protons);
	  if (check != 0) return 1;
      }
      else if (token == "sfactor")
	{
	  vector<double> sfactors;
	  while ( !stream.eof() ) {
	    sfactors.push_back(0);
	    stream >> sfactors.back();
	  }
	  nonres->SetSfactors(sfactors);
	}
      else if (token == "resonances")
        this->ParseResonances(pStream);
      
      if ( !bail)
	getline(pStream,line);
    }
  return 0;
}

// PrintRates
void
reaction::PrintRates(double temp)
{
  cout << temp ;
  double sum = 0;

  // determine total first, means I loop over resonances twice, but it makes the output more consistent if total is always in the second column
  if (nonres->GetSfactor() > 0 ){
    sum += nonres->GetRate(temp);
  }
  for (auto res : resonances) {
    sum += res->GetRate(temp);
  }
  cout << "\t" << sum;

  if (nonres->GetSfactor() > 0 ){
    cout << "\t" << nonres->GetRate(temp);
  }
  else cout << "\t0" ;
  for (auto res : resonances) {
     cout << "\t" << res->GetRate(temp);
  }
  cout << endl;
}

// PrintResonanceEnergies
void
reaction::PrintResonanceEnergies()
{
  cout << "# T";
  cout <<  "\tTotal\tDC";
  for (auto res : resonances) {
    cout << "\t" << res->GetE() << " keV";
  }
  cout << endl;

}




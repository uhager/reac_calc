// reac_calc: calculate reaction rates from resonance strengths and S-factors.
// Outputs results to stdout
// author: Ulrike Hager

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "reaction.h"

// globals
reaction *reac = new reaction();
double Tmin, Tmax;
int Tsteps;

void
CalcRates()
{
  double stepSize = (Tmax-Tmin)/(double)(Tsteps-1.0) ;
  for (int i = 0; i<Tsteps; i++) {
    double temp = Tmin + i*stepSize;
    reac->CalcRates(temp);
  }
}

int
ParseTemperatures(istream& pStream)
{
  //  cout << "[reaction::ParseTemperatures]" << endl;
  string line, token;
  bool	bail = false;
  getline(pStream,line);
  while ( pStream && !bail)
    {
      istringstream stream(line.c_str());
      stream >> token;
      //      cout << "line: "<< line << " token: " << token << endl;
      if ( token == "" || token[0] == '#')
	{
	  //comment or blank
	}
      else if ( token.compare("end") == 0)
	bail = true;
      else if (token.compare("min") == 0) stream >>  Tmin;
      else if (token.compare("max") == 0) stream >>  Tmax;
      else if (token.compare("steps") == 0) stream >>  Tsteps;   
      if ( !bail)
	getline(pStream,line);
    }
  return 0;
}


int
ParseConfig(string configFile)
{
  string line, token;
  ifstream input(configFile.c_str(),ifstream::in);
  //  cout << "Parsing configuration file " << configFile << endl;;

  getline(input,line);
  while ( input)
    {
      istringstream stream(line.c_str());
      stream >> token;
      //      cout << "line: "<< line << " token: " << token << endl;
      if ( token == "" || token[0] == '#' || token[0] == '\n')
        {
          //comment or empty
        }
      else if (token == "reaction"){
	reac->ParseConfig(input);
      }
      else if (token == "temperatures")
        ParseTemperatures(input);
      
      if ( input)
        getline(input,line);
    }
  //  cout << "reaction input parsing done.\n";
  return 0;
}

void
PrintRates()
{
  reac->PrintResonanceEnergies();
  double stepSize = (Tmax-Tmin)/(double)(Tsteps-1.0) ;
  for (int i = 0; i<Tsteps; i++) {
    double temp = Tmin + i*stepSize;
    reac->PrintRates(temp);
  }
}

int main(int argc, char *argv[])
{
  string configFile = "";
  if( argc == 2 ) {
    configFile = argv[1];
    }
    else {
      cout << "Usage: reac_calc <configFile> \n";
      return 1;
    }

  Tmin = Tmax = Tsteps = -1;
  
  ParseConfig(configFile);
  if ( Tmin < 0 || Tmax < 0 || Tsteps <0 ) {
    cout << "\n Error: invalid temperatures\n" << endl;
    return 1;
  }
  
  reac->PrintProperties();
  cout << "# Temperatures - min: " << Tmin << " max: " << Tmax << " steps: " << Tsteps << endl;
  cout << "# ----------" << endl;

  CalcRates();
  PrintRates();
  
  delete reac;
  return 0;
}

    

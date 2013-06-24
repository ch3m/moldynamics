/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef READSIMCONFIG_h
#define READSIMCONFIG_h
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "SimParams.h"

using namespace std;

template<class Tmedida,class Tn>
class ReadSimConfig{
public:
////Put Public variables

////Constructors & destructor
  ReadSimConfig(char *SimConfigFileName) {
    SimConfigFile.open(SimConfigFileName, ifstream::in);
    if(!SimConfigFile) {
      printf("Cannot open %s\n",SimConfigFileName);
      exit(60);
    }
  }
  ~ReadSimConfig(void){};

////some funtion
  void Reader(SimParams<Tmedida,Tn> &Parameters){
    string buffer;
    SimConfigFile >> Parameters.NumSteps;
    SimConfigFile >> Parameters.NumAverage;
    SimConfigFile >> Parameters.OutputFrequency;
    SimConfigFile >> Parameters.deltaT;
    SimConfigFile >> Parameters.Temperature;
    SimConfigFile >> Parameters.CutRadius;
    SimConfigFile >> Parameters.dcd_use;
    SimConfigFile >> Parameters.dcd_period;
    SimConfigFile >> Parameters.dcd_overwrite; 
    SimConfigFile >> Parameters.boxfile_name; 
  };

protected:
private:
  ifstream SimConfigFile;
};

#endif

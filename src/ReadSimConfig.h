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
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.NumAverage;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.OutputFrequency;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.deltaT;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.Temperature;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.CutRadius;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.dcd_use;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.dcd_period;
    getline(SimConfigFile, buffer);
    SimConfigFile >> Parameters.dcd_overwrite;
    getline(SimConfigFile, buffer);
  };

protected:
private:
  ifstream SimConfigFile;
};

#endif

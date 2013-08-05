/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef SIMPARAMS_h
#define SIMPARAMS_h
#include <iostream>
#include <string>
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "Potentials/Potential.h"


using namespace std;

template<class Tmedida,class Tn>
class SimParams{
public:
    //Put Public variables
    Tn NumSteps;
    Tn NumAverage;
    Tn OutputFrequency;
    Tmedida deltaT;
    Tmedida Temperature;
    Tmedida CutRadius;
    bool dcd_use;
    bool dcd_overwrite;
    Tn dcd_period;
    string boxfile_name;
    //Variable Real-Time
    Tn CurrentStep;
    string Potential_type;
    Potential<Tmedida,Tn> *Pot;

    //Constructors & destructor
    SimParams() {
      NumSteps = 0;
      NumAverage = 0;
      OutputFrequency = 0;
      deltaT = 0.0;
      Temperature = 0.0;
      CutRadius = 0.0;
      dcd_use = false;
      dcd_period = 1;
      dcd_overwrite = true;
      boxfile_name = "caja";
      Potential_type = "new";
    }
    ~SimParams(){};

    //some funtion
    inline void NextStep() {CurrentStep++;};
    inline void InitStep() {CurrentStep=1;};
    inline int EndStep() {return (CurrentStep<=NumSteps) ? (1) : (0) ;} ;
    inline int Average() {if ( CurrentStep % NumAverage == 0 ) {return 1;} else {return 0;};};
    inline int Output() {if ( CurrentStep % OutputFrequency == 0 ) {return 1;} else {return 0;};};
    inline int DCD() {if ( (CurrentStep % dcd_period == 0) && dcd_use) {return 1;} else {return 0;};};
    void Print() {
      cout<<boolalpha;
      cout << "++++++++++++++++++++++++++++++++++++" << endl;
      cout << "\tSimulation Parameters" << endl;
      cout << "\t\tTotal number of steps:\t" << NumSteps << endl;
      cout << "\t\tSteps per Average:\t" << NumAverage << endl;
      cout << "\t\tOutput Frequency:\t" << OutputFrequency << endl;
      cout << "\t\tDeltaT:\t\t\t" << deltaT << endl;
      cout << "\t\tSystem Teperature:\t" << Temperature << endl;
      cout << "\t\tCut Radius:\t" << CutRadius  << endl;
      cout << "\t\tDCD using:\t" << dcd_use  << endl;
      cout << "\t\tDCD period:\t" << dcd_period   << endl;
      cout << "\t\tDCD overwrite:\t" << dcd_overwrite   << endl;
      cout << "\t\tBoxfile name:\t" << boxfile_name   << endl;
      cout << "\t\tPotential type:\t" <<  Potential_type  << endl;
      cout << "------------------------------------" << endl;
    }

protected:
private:
};

#endif

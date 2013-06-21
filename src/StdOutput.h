/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef STDOUTPUT_h
#define STDOUTPUT_h
#include <iostream>
#include "Box.h"
#include "SimParams.h"

using namespace std;

template<class Tmedida,class Tn>
class StdOutput{
public:
////Put Public variables

////Constructors & destructor
  StdOutput() {
    print = 0;
  }
  ~StdOutput() {}

////some funtion
  void PrintCurrentProperties(const Box<Tmedida,Tn> &pBox){
    if(!print)//Print label
      cout << "Steps | Total Energy | Kinetic Energy | Potential Energy | InstantTemperature" << endl;
      cout.precision(6);
      cout << pBox.SimulationParams.CurrentStep << "\t"
        << (pBox.PotentialEnergy+pBox.KineticEnergy)/pBox.TotalParticles << "\t"
        << pBox.KineticEnergy/pBox.TotalParticles << "\t"
        << pBox.PotentialEnergy/pBox.TotalParticles << "\t"
        << pBox.TemperatureInstant << endl;
    print++;
  }
  void PrintAllProperties(Box<Tmedida,Tn> &pBox){
    pBox.SimulationParams.Print();
    pBox.PrintProperties();
  }

protected:
private:
    unsigned int print;
};

#endif

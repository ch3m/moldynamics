#include <cstdio>  
#include <cstdlib>
#include <iostream>
#include "Box.h"
#include "ReadBoxConfig.h"
#include "ReadSimConfig.h"
#include "ReadSimConfigXML.h"
#include "Integrator.h"
#include "WriterXYZ.h"
#include "WriterBOX.h"
#include "WriterDCD.h"
#include "DensityProfile.h"
#include "StdOutput.h"
#include "Timer.h"
//#include "boost/function.hpp"
//#include "boost/bind.hpp"
#include "Potentials.h"

#ifndef MEDIDA_TYPE
#define MEDIDA_TYPE double
#endif

#ifndef N_TYPE 
#define N_TYPE long int
#endif

using namespace std;

// main routine that executes on the host  
int main(void){
//  typedef boost::function<MEDIDA_TYPE(MEDIDA_TYPE)> Function_t;
//    Function_t myFunc1 = boost::bind(&LJ_pot_energy<MEDIDA_TYPE>, _1, 4.3);
//    Function_t myFunc2 = boost::bind(&MyFunc2, _1);
//
//    myFunc1(5.2);
//    myFunc1(7.8);
//    myFunc2(6);
  //SimParams Params; //Create object with parameters simulation(Steps,average...)
//  Potential<MEDIDA_TYPE,N_TYPE>  Pot(1);
//  Potential  Pot(1);
  Box<MEDIDA_TYPE,N_TYPE> boxset;
  StdOutput<MEDIDA_TYPE,N_TYPE> Salida;
  string str = "./config.xml";
  ReadSimConfigXML<MEDIDA_TYPE,N_TYPE> SimXMLConf(str);
  SimXMLConf.Reader(boxset.SimulationParams);
  ReadBoxConfig<MEDIDA_TYPE,N_TYPE> BoxFromFile(boxset.SimulationParams.boxfile_name);
  WriterXYZ<MEDIDA_TYPE,N_TYPE>  fileXYZ("./movie.xyz");
  WriterBOX<MEDIDA_TYPE,N_TYPE> Boxfile("./box.config");
  Timer T;
  T.PrintDate();
  BoxFromFile.Reader(boxset); //Llena la estructura de la caja
  //Para escribir el DCD es necesaria la estructura de la caja
  WriterDCD<MEDIDA_TYPE,N_TYPE> fileDCD;
  if(boxset.SimulationParams.dcd_use)fileDCD.Create_DCD_Mol2("./output.dcd",false,boxset);
  Salida.PrintAllProperties(boxset);
////Start Simulation
  DensityProfile<MEDIDA_TYPE,N_TYPE> DensProfile("PerfilesDensidad",boxset);
  Integrator<MEDIDA_TYPE,N_TYPE> Integrate(boxset);//set deltaT, temperature, Calculo las primeras fuerza
  boxset.BoxPressure.PromeTensorZero();
//  //for(int step=1; step <= boxset.SimulationParams.NumSteps; step++){
  boxset.SimulationParams.InitStep(); 
  T.StartTimer1();
  while( boxset.SimulationParams.EndStep()  ){
      Integrate.VelocityVerletNVT(boxset);
      if( boxset.SimulationParams.Output() ){
          Salida.PrintCurrentProperties(boxset);
      }
      if( boxset.SimulationParams.Average() ){
          DensProfile.Calculate(boxset); 
          boxset.BoxPressure.RecordMeasure(boxset.TotalParticles,boxset.TemperatureInstant);
          //boxset.BoxPressure.PrintInstant(boxset.TotalParticles,boxset.TemperatureInstant);   
      }
      if(boxset.SimulationParams.DCD())fileDCD.write(boxset.SimulationParams.CurrentStep);
      boxset.SimulationParams.NextStep();
  };
  T.EndTimer1(SECONDS);
  boxset.BoxPressure.PrintProme(boxset.SimulationParams.NumAverage,boxset.SimulationParams.NumSteps);
  T.PrintT1();
  fileXYZ.write(boxset);//Escribe la caja en xyz
  DensProfile.Write(boxset); 
  Boxfile.write(boxset);
  T.PrintDate();
  return 0;
}

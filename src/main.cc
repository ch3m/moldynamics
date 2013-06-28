#include <cstdio>  
#include <cstdlib>
#include <iostream>
#include "Box.h"
#include "ReadBoxConfig.h"
#include "ReadSimConfig.h"
#include "Integrator.h"
#include "WriterXYZ.h"
#include "WriterBOX.h"
#include "WriterDCD.h"
#include "DensityProfile.h"
#include "StdOutput.h"
#include "Timer.h"

using namespace std;

// main routine that executes on the host  
int main(void){  
  //SimParams Params; //Create object with parameters simulation(Steps,average...)
  Box<double,unsigned int> boxset;
  StdOutput<double,unsigned int> Salida;
  ReadSimConfig<double,unsigned int> SimConf("./config.txt");
  SimConf.Reader(boxset.SimulationParams);
  //boxset.SimulationParams.Print();
  ReadBoxConfig<double,unsigned int> BoxFromFile(boxset.SimulationParams.boxfile_name);
  WriterXYZ<double,unsigned int>  fileXYZ("./movie.xyz");
  WriterBOX<double,unsigned int> Boxfile("./box.config");
  Timer T;
  T.PrintDate();
  BoxFromFile.Reader(boxset); //Llena la estructura de la caja
  //Salida.PrintSimProperties(boxset);
  //Para escribir el DCD es necesaria la estructura de la caja
  WriterDCD<double,unsigned int> fileDCD;
  if(boxset.SimulationParams.dcd_use)fileDCD.Create_DCD_Mol2("./output.dcd",false,boxset);
  Salida.PrintAllProperties(boxset);
////Start Simulation
  DensityProfile<double,unsigned int> DensProfile("PerfilesDensidad",boxset);
  Integrator<double,unsigned int> Integrate(boxset);//set deltaT, temperature, Calculo las primeras fuerza
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

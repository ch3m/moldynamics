/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef INTEGRATOR_h
#define INTEGRATOR_h
#include "Box.h"
#include "Forces.h"
#include "SimParams.h"
#include <cmath>

using namespace std;

template<class Tmedida,class Tn>
class Integrator{
public:
    //Put Public variables

    //Constructors & destructor
    /**
     * @bug Validar numero de particulas en El constructor con tamano de la caja
     */
    Integrator(Box<Tmedida,Tn> & pBox) {
        DeltaT = pBox.SimulationParams.deltaT;
        Temperature=pBox.SimulationParams.Temperature;
        force.SetCutRadius(pBox.SimulationParams.CutRadius);
        force.RunCPU(pBox);
    }
    ~Integrator(void) {};

    //some funtion
    void VelocityVerletNVT(Box<Tmedida,Tn> & pBox) {
      //force.Suma(pBox);
      for(int i=0; i < pBox.TotalParticles; i++ ){
          pBox.VelX[i] = pBox.VelX[i] + pBox.ForceX[i]*0.5*DeltaT;
          pBox.VelY[i] = pBox.VelY[i] + pBox.ForceY[i]*0.5*DeltaT;
          pBox.VelZ[i] = pBox.VelZ[i] + pBox.ForceZ[i]*0.5*DeltaT;

          pBox.PosX[i] = pBox.PosX[i] + pBox.VelX[i]*DeltaT;
          pBox.PosY[i] = pBox.PosY[i] + pBox.VelY[i]*DeltaT;
          pBox.PosZ[i] = pBox.PosZ[i] + pBox.VelZ[i]*DeltaT;

          if(pBox.PosX[i] > pBox.SizeX){
            pBox.PosX[i]=pBox.PosX[i] - pBox.SizeX;
          }else if(pBox.PosX[i] < 0.0){
            pBox.PosX[i]=pBox.PosX[i] + pBox.SizeX;
          }
          if(pBox.PosY[i] > pBox.SizeY){
            pBox.PosY[i]=pBox.PosY[i] - pBox.SizeY;
          }else if(pBox.PosY[i] < 0.0){
            pBox.PosY[i]=pBox.PosY[i] + pBox.SizeY;
          }
          if(pBox.PosZ[i] > pBox.SizeZ){
            pBox.PosZ[i]=pBox.PosZ[i] - pBox.SizeZ;
          }else if(pBox.PosZ[i] < 0.0){
            pBox.PosZ[i]=pBox.PosZ[i] + pBox.SizeZ;
          }
      }

      force.RunCPU(pBox);

      pBox.KineticEnergy = 0.0;
      for(int i=0; i < pBox.TotalParticles; i++ ){
          pBox.VelX[i] = pBox.VelX[i] + pBox.ForceX[i]*0.5*DeltaT;
          pBox.VelY[i] = pBox.VelY[i] + pBox.ForceY[i]*0.5*DeltaT;
          pBox.VelZ[i] = pBox.VelZ[i] + pBox.ForceZ[i]*0.5*DeltaT;

          pBox.KineticEnergy = pBox.KineticEnergy +  pBox.VelX[i]*pBox.VelX[i] +
                      pBox.VelY[i]*pBox.VelY[i] +  pBox.VelZ[i]*pBox.VelZ[i] ;
      }

      pBox.KineticEnergy = 0.5*pBox.KineticEnergy;
      pBox.TemperatureInstant = (2.0*pBox.KineticEnergy) / (3.0*(pBox.TotalParticles-3));
      scale = sqrt((double)(Temperature/pBox.TemperatureInstant));

      double rxx,ryy,rzz;

      for(int i=0; i < pBox.TotalParticles; i++ ){
          pBox.VelX[i] = scale*pBox.VelX[i];
          pBox.VelY[i] = scale*pBox.VelY[i];
          pBox.VelZ[i] = scale*pBox.VelZ[i];
          /*rxx = pBox.PosX[i] + 0.5*pBox.SizeX;
          ryy = pBox.PosY[i] + 0.5*pBox.SizeY;
          rzz = pBox.PosZ[i] + 0.5*pBox.SizeZ;
          rxx  = rxx - round(rxx*1/pBox.SizeX)*pBox.SizeX;
          ryy  = ryy - round(ryy*1/pBox.SizeY)*pBox.SizeY;
          rzz  = rzz - round(rzz*1/pBox.SizeZ)*pBox.SizeZ;
          pBox.PosX[i] = rxx + 0.5*pBox.SizeX;
          pBox.PosY[i] = ryy + 0.5*pBox.SizeY;
          pBox.PosZ[i] = rzz + 0.5*pBox.SizeZ; */
      }
    }
protected:
private:
  double *PosX_before, *PosY_before, *PosZ_before;
  double *PosX_after, *PosY_after, *PosZ_after;
  double DeltaT;
  double scale;
  double Temperature;
  Forces<Tmedida,Tn> force;
};

#endif

/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef FORCES_h
#define FORCES_h
#include "Box.h"

using namespace std;

template<class Tmedida,class Tn>
class Forces{
public:
    //Put Public variables

    //Constructors & destructor
    Forces() {};
    ~Forces(void) {};

    //some funtion
    void RunCPU(Box<Tmedida,Tn> & pBox) {
      int N=pBox.TotalParticles;
      double dx,dy,dz,Fij,rij2,invrij,rij6;

      pBox.ForceZero();
      pBox.PotentialEnergy = 0.0;
      pBox.BoxPressure.TensorZero();

      for (int i=0; i < pBox.TotalParticles-1; i++){
        for(int j=i+1; j < pBox.TotalParticles;j++){
          dx=pBox.PosX[i]-pBox.PosX[j];
          dy=pBox.PosY[i]-pBox.PosY[j];
          dz=pBox.PosZ[i]-pBox.PosZ[j];

          if (dx > (pBox.SizeX/2.0)) dx = dx - pBox.SizeX;
          else if (dx < -1.0*(pBox.SizeX/2.0) ) dx = dx + pBox.SizeX;

          if (dy > (pBox.SizeY/2.0)) dy = dy - pBox.SizeY;
          else if (dy < -1.0*(pBox.SizeY/2.0) ) dy = dy + pBox.SizeY;

          if (dz > (pBox.SizeZ/2.0)) dz = dz - pBox.SizeZ;
          else if (dz < -1.0*(pBox.SizeZ/2.0) ) dz = dz + pBox.SizeZ;

          rij2=dx*dx+dy*dy+dz*dz;
          if(rij2 < rcut*rcut){
            //working: ESTO ES LO QUE SE DESEA
//            pBox.pot_energy();
//            pBox.forces();
            
            invrij = 1.0/rij2;
//            rij6 = invrij*invrij*invrij;
//            pBox.PotentialEnergy = pBox.PotentialEnergy + 4.0*rij6*(rij6 - 1.0);
//            pBox.PotentialEnergy = pBox.PotentialEnergy 
//                    + pBox.SimulationParams.Pot->calc_pot(invrij);
            pBox.PotentialEnergy = pBox.PotentialEnergy 
                    + pBox.SimulationParams.myFunc1(invrij);
//            Fij=24.0*( 2.0*rij6 - 1.0 )*rij6;
//            Fij = pBox.SimulationParams.Pot->calc_force(invrij);
            Fij=pBox.SimulationParams.myFunc2(invrij);
            pBox.ForceX[i]=pBox.ForceX[i]+Fij*dx*invrij;
            pBox.ForceY[i]=pBox.ForceY[i]+Fij*dy*invrij;
            pBox.ForceZ[i]=pBox.ForceZ[i]+Fij*dz*invrij;
            pBox.ForceX[j]=pBox.ForceX[j]-Fij*dx*invrij;
            pBox.ForceY[j]=pBox.ForceY[j]-Fij*dy*invrij;
            pBox.ForceZ[j]=pBox.ForceZ[j]-Fij*dz*invrij;
            double pgbr = Fij*invrij;
            if(pBox.SimulationParams.Average())pBox.BoxPressure.Add(pgbr,dx,dy,dz);
          }
        }
      }
    };
    void Suma(Box<Tmedida,Tn> & pBox){
      double sumaX, sumaY, sumaZ;
      sumaX=0.0;
      sumaY=0.0;
      sumaZ=0.0;
      for(int i=0; i < pBox.TotalParticles; i++){
        sumaX = sumaX + pBox.ForceX[i];
        sumaY = sumaY + pBox.ForceY[i];
        sumaZ = sumaZ + pBox.ForceZ[i];
      }
      cout.precision(10);
      cout << sumaX << "  " << sumaY << "  " << sumaZ <<endl;
    };
    void SetCutRadius(double & prcut){
      rcut = prcut;
    };
protected:
private:
  double rcut;
};

#endif

/**
 * A detailed description of the class.
 *
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef BOX_h
#define BOX_h

#include <iostream>
#include "Pressure.h"
#include "SimParams.h"

using namespace std;

template<class Tmedida,class Tn>
class Box{
public:
    unsigned int TotalParticles;
    Tmedida *PosX, *PosY, *PosZ;
    Tmedida *VelX, *VelY, *VelZ;
    Tmedida *ForceX, *ForceY, *ForceZ;
    Tmedida SizeX, SizeY, SizeZ;
    Tmedida PotentialEnergy, KineticEnergy;
    Tmedida TemperatureInstant;
    Tmedida scale;
    Pressure<Tmedida,Tn> BoxPressure;
    SimParams<Tmedida,Tn> SimulationParams;

////Constructor and Destructor
  Box() {
    TotalParticles = 2;
    SizeX=1.0;
    SizeY=1.0;
    SizeZ=1.0;
    Malloc_Particules(TotalParticles);
  }

  Box(const unsigned int & pTotalParticles,const double & pSizeX,const double & pSizeY,const double & pSizeZ) {
    TotalParticles = pTotalParticles;
    SizeX = pSizeX;
    SizeY = pSizeY;
    SizeZ = pSizeZ;
    Malloc_Particules(TotalParticles);
  }

  ~Box() {
    Delete_Box();
  }

////Memebers function
  void Reallocate_Box(const unsigned int & pTotalParticles,const double & pSizeX,const double & pSizeY,const double & pSizeZ) {
    Delete_Box();
    TotalParticles = pTotalParticles;
    SizeX = pSizeX;
    SizeY = pSizeY;
    SizeZ = pSizeZ;
    Malloc_Particules(TotalParticles);
  }

////Reallocate memory using value of TotalParticles now
  void Reallocate_Box() {
    Malloc_Particules(TotalParticles);
  }
  void PrintProperties(){
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(15);
    cout << "++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\tBox Properties" << endl;
    cout << "\t\tNumber of Particles:\t" << TotalParticles << endl;
    cout << "\t\tSize X (Lx):\t" << SizeX << endl;
    cout << "\t\tSize Y (Ly):\t" << SizeY << endl;
    cout << "\t\tSize Z (Lz):\t" << SizeZ << endl;
    cout << "\t\tDensity:\t" << TotalParticles/(SizeX*SizeY*SizeZ) << endl;
    cout << "------------------------------------" << endl;
  }
  void ForceZero(){
    for(int i=0;i<TotalParticles;i++){
      ForceX[i]=0.0;
      ForceY[i]=0.0;
      ForceZ[i]=0.0;
    }
  }
  void PrintFirstValues(){
    cout << "++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\tPosiciones" << endl;
    cout << "\t\tX:\t" << PosX[0] << endl;
    cout << "\t\tY\t" << PosY[0] << endl;
    cout << "\t\tZ:\t" << PosZ[0] << endl;
    cout << "\t\tVX:\t" << VelX[0] << endl;
    cout << "\t\tVY:\t" << VelY[0] << endl;
    cout << "\t\tVZ:\t" << VelZ[0] << endl;
    cout << "------------------------------------" << endl;
  }

protected:
private:
  //Aqui es donde se debe cambiar los arreglos para el MIC
  void Malloc_Particules(unsigned int & N){
    PosX = new double[N];
    PosY = new double[N];
    PosZ = new double[N];
    VelX = new double[N];
    VelY = new double[N];
    VelZ = new double[N];
    ForceX = new double[N];
    ForceY = new double[N];
    ForceZ = new double[N];
//Inicia el volumen de la caja para las presiones
    BoxPressure.VolumenBox=SizeX*SizeY*SizeZ;
  }
  void Delete_Box() {
    delete [] PosX;
    delete [] PosY;
    delete [] PosZ;
    delete [] VelX;
    delete [] VelY;
    delete [] VelZ;
    delete [] ForceX;
    delete [] ForceY;
    delete [] ForceZ;
  }
};

#endif  // XX_h

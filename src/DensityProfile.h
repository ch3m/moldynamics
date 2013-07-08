#ifndef DENSITYPROFILE_h
#define DENSITYPROFILE_h
#include <iostream>
#include <fstream>
#include <climits>
#include <string.h>
#include <stdlib.h>
#include "Box.h"

#define MAX(a,b)         ((a < b) ?  (b) : (a))
#define BIGGEST(a,b,c)   ((MAX(a,b) < c) ?  (c) : (MAX(a,b)))
//#define X 0 
//#define Y 0 
//#define Z 0 

using namespace std;

template<class Tmedida,class Tn>
class DensityProfile{
public:
    //Put Public variables

    //Constructors & destructor
    DensityProfile(char *DP_filename,const Box <Tmedida,Tn> &pBox) {
      strcpy(filename,DP_filename);
      delta_binX = 0.01;
      delta_binY = 0.01;
      delta_binZ = 0.01;
      VolX = delta_binX * pBox.SizeY * pBox.SizeZ;
      VolY = pBox.SizeX * delta_binY * pBox.SizeZ;
      VolZ = pBox.SizeX * pBox.SizeY * delta_binZ;
      nbinX = pBox.SizeX/delta_binX + 1;
      nbinY = pBox.SizeY/delta_binY + 1;
      nbinZ = pBox.SizeZ/delta_binZ + 1;
      DensityPerBinX = new double[nbinX];
      DensityPerBinY = new double[nbinY];
      DensityPerBinZ = new double[nbinZ];
      for(int i=0; i<nbinX; i++)DensityPerBinX[i]=0.0;
      for(int i=0; i<nbinY; i++)DensityPerBinY[i]=0.0;
      for(int i=0; i<nbinZ; i++)DensityPerBinZ[i]=0.0;
      MaxBin = BIGGEST(nbinX,nbinY,nbinZ);
    }
    //DensityProfile();
    ~DensityProfile(void){};

    //some funtion
    void Calculate(const Box<Tmedida,Tn> &pBox) {
      ParticlePerBinX = new int[nbinX];
      ParticlePerBinY = new int[nbinY];
      ParticlePerBinZ = new int[nbinZ];
      for(int i=0; i<nbinX; i++)ParticlePerBinX[i]=0;
      for(int i=0; i<nbinY; i++)ParticlePerBinY[i]=0;
      for(int i=0; i<nbinZ; i++)ParticlePerBinZ[i]=0;

      for(int i=0; i<pBox.TotalParticles; i++){
        int bin = pBox.PosX[i]/delta_binX;
        ParticlePerBinX[bin]++;
        if(bin>=nbinX)cout << "ERROR: Particle out of bin_array"  << pBox.PosX[i] << " "  << i << endl;
        if(ParticlePerBinX[bin] == INT_MAX)cout << "ERROR: overflow in bin " << bin << endl;
    //  cout << "particle " << bin << " " << pBox.PosX[i]/delta_binX << endl;

        bin = pBox.PosY[i]/delta_binY;
        ParticlePerBinY[bin]++;
        if(bin>=nbinY)cout << "ERROR: Particle out of bin_array"  << pBox.PosY[i] << " "  << i << endl;
        if(ParticlePerBinY[bin] == INT_MAX)cout << "ERROR: overflow in bin " << bin << endl;

        bin = pBox.PosZ[i]/delta_binZ;
        ParticlePerBinZ[bin]++;
        if(bin>=nbinZ)cout << "ERROR: Particle out of bin_array"  << pBox.PosZ[i] << " "  << i << endl;
        if(ParticlePerBinZ[bin] == INT_MAX)cout << "ERROR: overflow in bin " << bin << endl;
      }
      for(int i=0; i<MaxBin; i++){
        if(i<nbinX) DensityPerBinX[i] = ParticlePerBinX[i]/VolX + DensityPerBinX[i];
        if(i<nbinY) DensityPerBinY[i] = ParticlePerBinY[i]/VolY + DensityPerBinY[i];
        if(i<nbinZ) DensityPerBinZ[i] = ParticlePerBinZ[i]/VolZ + DensityPerBinZ[i];
      }
      delete [] ParticlePerBinX;
      delete [] ParticlePerBinY;
      delete [] ParticlePerBinZ;
    }
    
    void Write(const Box <Tmedida,Tn> &pBox) {
      double cociente = (double) pBox.SimulationParams.NumAverage / pBox.SimulationParams.NumSteps;
      DensityProfileFile.open(filename, ifstream::out); // Open file for density profiles
      if(!DensityProfileFile) {
        cout << "Cannot open test.txt file.\n";
        exit(1);
      }
      for(int i=0; i<MaxBin; i++){
        DensityProfileFile << i*delta_binX << "\t\t"; //Calcular el deta bin maximo
        if(i>nbinX) DensityProfileFile << 0.00;
        else  DensityProfileFile << DensityPerBinX[i]*cociente;
        DensityProfileFile << "\t\t";
        if(i>nbinY) DensityProfileFile << 0.00;
        else  DensityProfileFile << DensityPerBinY[i]*cociente;
        DensityProfileFile << "\t\t";
        if(i>nbinZ) DensityProfileFile << 0.00;
        else  DensityProfileFile << DensityPerBinZ[i]*cociente;
        DensityProfileFile << "\n";
      }
      DensityProfileFile.close(); // close file for density Profiles
    }

protected:
private:
  char filename[50];
  ofstream DensityProfileFile;
  int *ParticlePerBinX;
  int *ParticlePerBinY;
  int *ParticlePerBinZ;
  double *DensityPerBinX;
  double *DensityPerBinY;
  double *DensityPerBinZ;
  double delta_binX;
  double delta_binY;
  double delta_binZ;
  double VolX;
  double VolY;
  double VolZ;
  int nbinX;
  int nbinY;
  int nbinZ;
  int MaxBin;
  

};

#endif

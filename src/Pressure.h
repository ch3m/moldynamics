/**      
 * Esta clase mide la cantidad de la presion en na simulacion
 * 
 * @short Esta clase mantiene las estadisticas de la cantidad de presion en la simulacion
 * @author Jose Maria Zamora Fuentes
 * @version 1.0
 * @since 2011
 */

#ifndef PRESSURE_h
#define PRESSURE_h

#include <iostream>

using namespace std;

template<class Tmedida, class Tn>
class Pressure{
public:
    //Put Public variables
    Tmedida VolumenBox;
    Tmedida press;
    Tmedida pressxx,pressxy,pressxz;
    Tmedida pressyx,pressyy,pressyz;
    Tmedida presszx,presszy,presszz;
    Tmedida pressa;
    Tmedida pressxxa,pressxya,pressxza;
    Tmedida pressyxa,pressyya,pressyza;
    Tmedida presszxa,presszya,presszza;

  //Constructors & destructor
  Pressure() {
    TensorZero();
  }
    
  ~Pressure() {}
//    Pressure(const Pressure& from);
//
    //some funtion
  void TensorZero() {
    press=0.0;
    pressxx=pressxy=pressxz=0.0;
    pressyx=pressyy=pressyz=0.0;
    presszx=presszy=presszz=0.0;
  }
  void PromeTensorZero() {
    pressa=0.0;
    pressxxa=pressxya=pressxza=0.0;
    pressyxa=pressyya=pressyza=0.0;
    presszxa=presszya=presszza=0.0;
  }
  void Add(Tmedida &pgbr,Tmedida &dx, Tmedida &dy, Tmedida &dz) {
    Tmedida fxi = pgbr*dx;
    Tmedida fyi = pgbr*dy;
    Tmedida fzi = pgbr*dz;
    press = press  + fxi*dx + fyi*dy + fzi*dz;
    //revisar optimizacion
    pressxx = pressxx + fxi*dx;
    pressxy = pressxy + fxi*dy;
    pressxz = pressxz + fxi*dz;
    pressyx = pressyx + fyi*dx;
    pressyy = pressyy + fyi*dy;
    pressyz = pressyz + fyi*dz;
    presszx = presszx + fzi*dx;
    presszy = presszy + fzi*dy;
    presszz = presszz + fzi*dz;
  }
  void RecordMeasure(const Tn &N,Tmedida &tempi) {
    Tmedida p_ideal = ((Tmedida) N)/VolumenBox*tempi;
    pressa = press/(3.0*VolumenBox) + p_ideal + pressa;
    pressxxa = pressxx/VolumenBox + pressxxa;
    pressxya = pressxy/VolumenBox + pressxya;
    pressxza = pressxz/VolumenBox + pressxza;
    pressyxa = pressyx/VolumenBox + pressyxa;
    pressyya = pressyy/VolumenBox + pressyya;
    pressyza = pressyz/VolumenBox + pressyza;
    presszxa = presszx/VolumenBox + presszxa;
    presszya = presszy/VolumenBox + presszya;
    presszza = presszz/VolumenBox + presszza;
  }
  void PrintInstant(const Tn &N, Tmedida &tempi) {
    Tmedida p_ideal = ((Tmedida) N)/VolumenBox*tempi;
    cout << "Pression(trace,xx,yy,zz):\t" << press/(3.0*VolumenBox) + 
      p_ideal  << " " << pressxx/VolumenBox << " " << pressyy/VolumenBox 
      << " " << presszz/VolumenBox <<  endl;
  } 
  void PrintProme( Tn &Nprome,Tn &NSteps) {
    cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\tAverage trace of Pression:\t\t" << pressa/NSteps*Nprome << endl;
    cout << "\tTensor component X" << endl;
    cout << "\t\tAverage Pression XX\t\t" << pressxxa/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression XY\t\t" << pressxya/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression XZ\t\t" << pressxza/NSteps*Nprome << endl;
    cout << "\tTensor component Y" << endl;
    cout << "\t\tAverage Pression YX\t\t" << pressyxa/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression YY\t\t" << pressyya/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression YZ\t\t" << pressyza/NSteps*Nprome << endl;
    cout << "\tTensor component Z" << endl;
    cout << "\t\tAverage Pression ZX\t\t" << presszxa/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression ZY\t\t" << presszya/NSteps*Nprome << endl;
    cout << "\t\tAverage Pression ZZ\t\t" << presszza/NSteps*Nprome << endl;
    cout << "------------------------------------------" << endl;
  }
//    void PrintProme( int &Nprome,int &NSteps);
protected:
private:
};
#endif

/**
 * Esta clase crea una instancia de tipo potencial
 *
 * @short Esta clase maneja el Potential que se selecciona y lo 
 *    apunta a un  functor. 1. Instanciar el constructor, y despues usar 
 *    hacer el set
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef LJ_POT_h
#define LJ_POT_h

#include <iostream>
#include "Potential.h"

using namespace std;

template<class Tmedida,class Tn> 
class LJ: public Potential<Tmedida,Tn> {
public:
    Tmedida sigma;
    Tmedida epsilon;
    //Put Public variables   
    
    //Constructors & destructor
    LJ(Tmedida s, Tmedida e){
//      cout << "constructor Potential parameters "<< sigma << " , " << epsilon << endl;
      sigma = s;
      epsilon = e;
    }
    ~LJ () {};
    //some funtion
    Tmedida set_pot(Tmedida s, Tmedida e){
//      cout << "setting Potential parameters "<< s << " , " << e << endl;
      sigma = s;
      epsilon  = e;
    }
    Tmedida calc_pot(Tmedida invrij){ //invrij = 1/rij_2
//      cout << "calc_pot Potential parameters " << sigma << " , " << epsilon << endl;
//      cout << "HOLA (rij2)"<< rij_2<<endl;
      return (4.0*invrij*invrij*invrij*(invrij*invrij*invrij - 1.0));
    }
    
    Tmedida calc_force(Tmedida invrij){ //invrij = 1/rij_2
//      cout << "calc_pot Potential parameters " << sigma << " , " << epsilon << endl;
//      cout << "HOLA (rij2)"<< rij_2<<endl;
      return (24.0*( 2.0*invrij*invrij*invrij - 1.0 )*invrij*invrij*invrij);
    }

protected:
private:
};




#endif  // XX_h

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

#ifndef LJ_h
#define LJ_h

#include <iostream>
#include "Potential.h"

using namespace std;

template<class Tmedida,class Tn> 
class LJ: public Potential<Tmedida,Tn> {
public:
    //Put Public variables 
    Tmedida sigma6;
    Tmedida sigma12;
    Tmedida epsilon;
    Tmedida invrij2;
    Tmedida invrij6;
    
    //Constructors & destructor
    LJ(Tmedida s, Tmedida e){
      cout << "Generating potential parameters: sigma=" << s << " ,espilon=" << e << endl;
      set_pot(s,e);
    }
    ~LJ () {};
    //some funtion
    Tmedida set_pot(Tmedida s, Tmedida e){
      cout << "Setting Potential parameters: sigma=" << s << " ,espilon=" << e << endl;
      sigma6 = s*s*s*s*s*s;
      sigma12 = sigma6*sigma6;
      epsilon = e;
    }
    void calc_pot(Tmedida rij2, Tmedida &force, Tmedida &pot ){
      invrij2 = 1.0 / rij2;
      invrij6 = invrij2*invrij2*invrij2;
      pot = 4.0*epsilon*invrij6*(invrij6*sigma12 - sigma6);
      /** @bug invrij2 no deberia ser invrij*/
      force = 24.0*invrij6*( 2.0*invrij6*sigma12 - sigma6 )*invrij2; 
    }

protected:
private:
};




#endif  // XX_h

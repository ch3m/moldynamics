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

#ifndef LJ_std_h
#define LJ_std_h

#include <iostream>
#include "Potential.h"

using namespace std;

template<class Tmedida,class Tn> 
class LJ_std: public Potential<Tmedida,Tn> {
public:
    //Put Public variables   
    Tmedida invrij2;
    Tmedida invrij6;
    
    //Constructors & destructor
    LJ_std(){
      cout << "Generating standard Lennard Jones" << endl;
    }
    ~LJ_std () {};
    //some funtion
    void calc_pot(Tmedida rij2,Tmedida & force, Tmedida & pot){
      invrij2 = 1.0 / rij2;
      invrij6 = invrij2*invrij2*invrij2;
      pot = 4.0*invrij6*(invrij6 - 1.0);
      /** @bug invrij2 no deberia ser invrij*/
      force = 24.0*invrij6*( 2.0*invrij6 - 1.0 )*invrij2;
    }
protected:
private:
};




#endif  // XX_h

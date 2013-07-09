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

#ifndef POTENTIAL_h
#define POTENTIAL_h

#include <iostream>
//#include "boost/function.hpp"
//#include "boost/bind.hpp"
#include "SimParams.h"

template<class Tmedida,class Tn>
class Potential{
public:
    //Put Public variables   
    
    //Constructors & destructor
    Potential() {
    };
    ~Potential(){};

    //some funtion
    void set_pot(){};
    virtual Tmedida calc_pot(Tmedida invrij){cout<< "HOLA" << endl; return 0;};
    virtual Tmedida calc_force(Tmedida invrij){cout<< "HOLA" << endl; return 0;};

protected:
private:
};

#endif  // XX_h

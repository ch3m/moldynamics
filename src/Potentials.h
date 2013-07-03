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

#ifndef POTENTIALS_h
#define POTENTIALS_h

#include <iostream>
#include "boost/function.hpp"
#include "boost/bind.hpp"
    
template<class Tmedida> Tmedida LJ_pot_energy_std(Tmedida rij2){
    std::cout << "MyFunc2: " << rij2 << std::endl;
    Tmedida invrij, rij6;
    invrij = 1.0/rij2;
    rij6 = invrij*invrij*invrij;
    return 4.0*rij6*(rij6 - 1.0);
}

template<class Tmedida> Tmedida LJ_pot_energy_std(Tmedida rij2, Tmedida sigma, Tmedida epsilon){
    Tmedida invrij, rij6;
    invrij = 1.0/rij2;
    rij6 = invrij*invrij*invrij;
    return 4.0*rij6*(rij6 - 1.0);
}

int MyFunc2(int i)
{
    std::cout << "MyFunc2: " << i << std::endl;
    return i;
}



#endif  // XX_h

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
    virtual void  calc_pot(Tmedida rij2, Tmedida & force, Tmedida & pot ){cout<< "HOLA" << endl;};
    
protected:
private:
};

#endif  // XX_h

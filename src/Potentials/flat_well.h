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

#ifndef FLAT_WELL_h
#define FLAT_WELL_h

#include <iostream>
#include <cmath> 
#include "Potential.h"

using namespace std;

template<class Tmedida,class Tn> 
class FlatWell: public Potential<Tmedida,Tn> {
public:
    //Put Public variables 
    Tmedida sigma;
    Tmedida epsilon;
    Tmedida m;
    Tmedida n;
    Tmedida alpha;
    
    //Constructors & destructor
    FlatWell(Tmedida s, Tmedida e, Tmedida m, Tmedida n, Tmedida alpha){
      cout << "Generating potential parameters: sigma=" << s << " epsilon=" << e 
              << " m=" << m << " n=" << n << " alpha=" << alpha << endl;
      set_pot(s,e,m,n,alpha);
    }
    ~FlatWell () {};
    //some funtion
    Tmedida set_pot(Tmedida s, Tmedida e, Tmedida m, Tmedida n, Tmedida alpha){
      cout << "Setting potential parameters: sigma=" << s << " epsilon=" << e 
              << " m=" << m << " n=" << n << " alpha=" << alpha << endl;
      this->sigma = 2*s;
      this->epsilon = e;
      this->m = m;
      this->n = n;
      this->alpha = alpha;
    }
    
    void calc_pot(Tmedida rij2, Tmedida &force, Tmedida &pot ){
      Tmedida rij = sqrt(rij2);
      //operaciones previas
      //sigma=2*sigma del constructor
      Tmedida pot_atrac=epsilon*pow((sigma/rij),m); 
      Tmedida pot_repul_n=pow(((sigma-rij)/alpha),n);
      Tmedida pot_repul = epsilon * exp (pot_repul_n);
      //calculate potential
      //pot = pot_atrac - pot_repul;
      pot = pot_repul;
      //Calculate Force
      /** @bug invrij2 no deberia ser invrij*/
      Tmedida force_atrac = m*pot_atrac/rij;
      Tmedida force_repul = (n /alpha) * ( pot_repul_n / ((sigma-rij)/alpha) ) * pot_repul;
      force = force_atrac - force_repul; 
    }

protected:
private:
};




#endif  // XX_h

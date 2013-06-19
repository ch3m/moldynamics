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

using namespace std;

template<typename T>
class Box{
public:
    unsigned int TotalParticles;
    T *PosX, *PosY, *PosZ;
    T *VelX, *VelY, *VelZ;
    T *ForceX, *ForceY, *ForceZ;
    T SizeX, SizeY, SizeZ;
    T PotentialEnergy, KineticEnergy;
    T TemperatureInstant;
    T scale;
    
    Box(){
      TotalParticles = 2;
      SizeX=1.0;
      SizeY=1.0;
      SizeZ=1.0;
    };
};

#endif  // XX_h

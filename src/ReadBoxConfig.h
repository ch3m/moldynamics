/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef READCONFIG_h
#define READCONFIG_h
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Box.h"

using namespace std;

template<class Tmedida,class Tn>
class ReadBoxConfig{
  
public:

  ReadBoxConfig(string BoxConfigFileName) {
    BoxConfigFile.open(BoxConfigFileName.c_str(), ifstream::in); // input
    if(!BoxConfigFile) {
      printf("Cannot open Box Config file: %s\n",BoxConfigFileName.c_str());
      exit(15);
    }
  }
  ~ReadBoxConfig(void){
    
  }; //Close file
  void Reader( Box<Tmedida,Tn> & pBox ){ //Reader
    BoxConfigFile >> pBox.TotalParticles;
    BoxConfigFile >> pBox.SizeX;
    BoxConfigFile >> pBox.SizeY;
    BoxConfigFile >> pBox.SizeZ;
    pBox.Reallocate_Box();
    for( int i = 0; i < pBox.TotalParticles; i++ ){
      BoxConfigFile >> pBox.PosX[i];
      BoxConfigFile >> pBox.PosY[i];
      BoxConfigFile >> pBox.PosZ[i];
      BoxConfigFile >> pBox.VelX[i];
      BoxConfigFile >> pBox.VelY[i];
      BoxConfigFile >> pBox.VelZ[i];
    }
    BoxConfigFile.close();
  }
protected:
private:
    ifstream BoxConfigFile; 
};

#endif  // 

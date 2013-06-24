/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef WRITERXYZ_h
#define WRITERXYZ_h
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Box.h"

using namespace std;

template<class Tmedida,class Tn>
class WriterXYZ{
public:
    //Put Public variables

    //Constructors & destructor
  WriterXYZ(char *XYZ_filename) {
    XYZfile.open(XYZ_filename, ifstream::out); // input
    if(!XYZfile) {
      cout << "Cannot open test.txt file.\n";
      exit(1);
    }
  }

  ~WriterXYZ() {
    XYZfile.close();
  }
  //some funtion
  void write(const Box<Tmedida,Tn> &pBox) {
    XYZfile << pBox.TotalParticles << endl;
    XYZfile << "LenardJones" << "\t" << pBox.SizeX << "\t" << pBox.SizeY << "\t" << pBox.SizeZ <<endl;
    for( int i = 0; i < pBox.TotalParticles; i++ ){
      XYZfile << "Si " << pBox.PosX[i] << " " << pBox.PosY[i] << " " << pBox.PosZ[i] << endl;
    }
  }

protected:
private:
  ofstream XYZfile;
};

#endif

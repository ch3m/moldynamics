/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef WRITERBOX_h
#define WRITERBOX_h
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Box.h"

using namespace std;

template<class Tmedida,class Tn>
class WriterBOX{
public:
    //Put Public variables

    //Constructors & destructor
    WriterBOX(char *XYZ_filename) {
      BOXfile.open(XYZ_filename, ifstream::out);
      if(!BOXfile) {
        cout << "Cannot open test.txt file.\n";
        exit(1);
      }
      BOXfile.setf(ios::fixed, ios::floatfield);
      BOXfile.setf(ios::showpoint);
      BOXfile.precision(15);
    }
    ~WriterBOX() {
      BOXfile.close();
    }

    //some funtion
    void write(const Box<Tmedida,Tn> &pBox) {
      BOXfile << pBox.TotalParticles << "\t\t"
          << pBox.SizeX << "\t"
          << pBox.SizeY << "\t"
          << pBox.SizeZ << "\t" << endl;
      for( int i = 0; i < pBox.TotalParticles; i++ ){
      BOXfile << pBox.PosX[i] << " " << pBox.PosY[i] << " " << pBox.PosZ[i] << endl;
      BOXfile << pBox.VelX[i] << " " << pBox.VelY[i] << " " << pBox.VelZ[i] << endl;
    }
}

protected:
private:
    ofstream BOXfile;
};

#endif

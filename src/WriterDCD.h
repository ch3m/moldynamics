/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef WRITERDCD_h
#define WRITERDCD_h

#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Box.h"
using namespace boost::filesystem;
using namespace std;

class WriterDCD{
public:
    //Put Public variables

    //Constructors & destructor
    WriterDCD();
    WriterDCD(const WriterDCD& from);
    ~WriterDCD(void);

    //some funtion
    void Create_DCD_Mol2(const string &fname,bool overwrite,Box &p_Box);
    void write(unsigned int timestep );

protected:
private:
  Box *m_Box;
  string m_fname;
  unsigned int m_num_frames_written;
  unsigned int m_start_timestep;
  unsigned int m_period;
  unsigned int m_last_written_step;
  unsigned int n_particles;
  bool m_appending;
  float *m_staging_buffer;

  void write_frame_header(std::fstream &file);  
  void write_file_header(std::fstream &file);
  void write_frame_data(std::fstream &file);
  void write_updated_header(std::fstream &file, unsigned int timestep);
  void write_mol2_file();
};

#endif

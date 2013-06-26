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

//! File position of NFILE in DCD header
#define NFILE_POS 8L
//! File position of NSTEP in DCD header
#define NSTEP_POS 20L

#include "../../boost-install/include/boost/filesystem/operations.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Box.h"
using namespace boost::filesystem;
using namespace std;

template<class Tmedida,class Tn>
class WriterDCD{
public:
    //Put Public variables

    //Constructors & destructor
    WriterDCD(){}
    WriterDCD(const WriterDCD& from);
    ~WriterDCD(void){};

    //some funtion
    void Create_DCD_Mol2(const string &fname,bool overwrite,Box<Tmedida,Tn> &p_Box){
    //:m_fname(fname), m_last_written_step(0),m_start_timestep(0),m_num_frames_written(0),m_appending(false)  
      m_fname = fname;
      m_last_written_step =0;
      m_start_timestep = 0;
      m_num_frames_written = 0;
      m_appending = false;
      //Initilize variable
      n_particles = p_Box.TotalParticles;
      m_period = p_Box.SimulationParams.NumAverage;
      m_Box = &p_Box;
      write_mol2_file();
      cout << "Notice: DCD particles:  " << n_particles << endl;
      if (!overwrite && exists(fname)){

        cout << "Notice: Appending to existing DCD file \"" << fname  << "\"" << endl;
        // open the file and get data from the header
        fstream file;        
        file.open(m_fname.c_str(), ios::ate | ios::in | ios::out | ios::binary);
        file.seekp(NFILE_POS);
        m_num_frames_written = read_int(file);
        m_start_timestep = read_int(file);
        unsigned int file_period = read_int(file);
        //cout << "num_frames_written= " << num_frames_written << endl;
        //cout << "start_timestep= " << m_start_timestep << endl;
        //cout << "file_period= " << file_period << endl;

        // warn the user if we are now dumping at a different period
        if (file_period != m_period)
          cout << "***Warning! DCDwriter is appending to a file that has period " << fname << "that is not the same as the requested period of " << m_period << endl;
        m_last_written_step = read_int(file);

        // check for errors
        if (!file.good()){
          cerr << endl << "***Error! Error reading DCD header data" << endl << endl;
          throw runtime_error("Error appending to DCD file");
        }
        m_appending = true;
      }
      //cout << "Periodo" << m_period << endl;
    }
    /*! \param timestep Current time step of the simulation
    The very first call to analyze() will result in the creation (or overwriting) of the
    file fname and the writing of the current timestep snapshot. After that, each call to analyze
    will add a new snapshot to the end of the file.
    */
    void write(unsigned int timestep) {
      // the file object
      fstream file;
      timestep += m_last_written_step;//Continuar escribiendo el timestep
      // initialize the file on the first frame written
      if (m_num_frames_written == 0){
        // open the file and truncate it
        file.open(m_fname.c_str(), ios::trunc | ios::out | ios::binary);

        // write the file header
        m_start_timestep = timestep;
        write_file_header(file);
      }else{
        if (m_appending && timestep <= m_last_written_step)
          cerr << "***Warning! DCDwriter is not writing output at timestep " << timestep << " because the file reports that it already has data up to step " << m_last_written_step << endl;
            // open the file and move the file pointer to the end
        file.open(m_fname.c_str(), ios::ate | ios::in | ios::out | ios::binary);
            // verify the period on subsequent frames
        if ( (timestep - m_start_timestep) % m_period != 0)
                cout << "***Warning! DCDwriter is writing time step " << timestep << " which is not specified in the period of the DCD file: " << m_start_timestep << " + i * " << m_period << endl;
      }
      // write the data for the current time step
      write_frame_header(file);
      write_frame_data(file);

      // update the header with the number of frames written
      m_num_frames_written++;
      //cout << "timestep: "  << timestep << endl; 
      write_updated_header(file, timestep);
      file.close();
    }

protected:
private:
  Box<Tmedida,Tn> *m_Box;
  string m_fname;
  unsigned int m_num_frames_written;
  unsigned int m_start_timestep;
  unsigned int m_period;
  unsigned int m_last_written_step;
  unsigned int n_particles;
  bool m_appending;
  float *m_staging_buffer;

    //! simple helper function to write an integer
    /*! \param file file to write to
        \param val integer to write
    */
    static void write_int(fstream &file, unsigned int val){
    file.write((char *)&val, sizeof(unsigned int));
    }

    //! simple helper function to read in integer
    /*! \param file file to read from
        \returns integer read
    */
    static unsigned int read_int(fstream &file){
    unsigned int val;
    file.read((char *)&val, sizeof(unsigned int));
    return val;
    }
  
  /*! \param file File to write to
    Writes the header that precedes each snapshot in the file. This header
    includes information on the box size of the simulation.
  */
    void write_frame_header(std::fstream &file){
        double unitcell[6];
        // set box dimensions
        unitcell[0] = (*m_Box).SizeX;
        unitcell[2] = (*m_Box).SizeY; 
        unitcell[5] = (*m_Box).SizeZ;
        // box angles are 90 degrees
        unitcell[1] = 0.0f;
        unitcell[3] = 0.0f;
        unitcell[4] = 0.0f;

        write_int(file, 48);
        file.write((char *)unitcell, 48);
        write_int(file, 48);

        // check for errors
        if (!file.good())
            {
            cerr << endl << "***Error! Error writing DCD frame header" << endl << endl;
            throw runtime_error("Error writing DCD file");
            }
    }

    /*! \param file File to write to
    Writes the initial DCD header to the beginning of the file. This must be
    called on a newly created (or truncated file).
    */
    void write_file_header(std::fstream &file){
        // the first 4 bytes in the file must be 84
        write_int(file, 84);

        // the next 4 bytes in the file must be "CORD"
        char cord_data[] = "CORD";
        file.write(cord_data, 4);
        write_int(file, 0);      // Number of frames in file, none written yet
        write_int(file, m_start_timestep); // Starting timestep
        write_int(file, m_period);  // Timesteps between frames written to the file
        write_int(file, 0);      // Number of timesteps in simulation
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);         // timestep (unused)
        write_int(file, 1);         // include unit cell
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 0);
        write_int(file, 24);    // Pretend to be CHARMM version 24
        write_int(file, 84);
        write_int(file, 164);
        write_int(file, 2);

        char title_string[81];
        memset(title_string, 0, 81);
        char remarks[] = "Created by MOLDYNAMICS";
        strncpy(title_string, remarks, 80);
        title_string[79] = '\0';
        file.write(title_string, 80);

        char time_str[81];
        memset(time_str, 0, 81);
        time_t cur_time = time(NULL);
        tm *tmbuf=localtime(&cur_time);
        strftime(time_str, 80, "REMARKS Created  %d %B, %Y at %H:%M", tmbuf);
        file.write(time_str, 80);

        write_int(file, 164);
        write_int(file, 4);
        write_int(file, n_particles);
        write_int(file, 4);

        // check for errors
        if (!file.good())
            {
            cerr << endl << "***Error! Error writing DCD header" << endl << endl;
            throw runtime_error("Error writing DCD file");
            }
    }
    
    void write_frame_data(std::fstream &file){
      // we need to unsort the positions and write in tag order
      m_staging_buffer = new float[n_particles];
      assert(m_staging_buffer);
      double Lx = (*m_Box).SizeX;
      double Ly = (*m_Box).SizeY;
      double Lz = (*m_Box).SizeZ;

      // prepare x coords for writing, looping in tag order
      for (unsigned int i = 0; i < n_particles; i++)m_staging_buffer[i] = float((*m_Box).PosX[i]);

      // write x coords
      write_int(file, n_particles * sizeof(float));
      file.write((char *)m_staging_buffer, n_particles * sizeof(float));
      write_int(file, n_particles * sizeof(float));

      // prepare y coords for writing, looping in tag order
      for (unsigned int i = 0; i < n_particles; i++)m_staging_buffer[i] = float((*m_Box).PosY[i]);
      // write y coords
      write_int(file, n_particles * sizeof(float));
      file.write((char *)m_staging_buffer, n_particles * sizeof(float));
      write_int(file, n_particles * sizeof(float));

      // prepare z coords for writing, looping in tag order
      for (unsigned int i = 0; i < n_particles; i++)m_staging_buffer[i] = float((*m_Box).PosZ[i]);
      // write z coords
      write_int(file, n_particles * sizeof(float));
      file.write((char *)m_staging_buffer, n_particles * sizeof(float));
      write_int(file, n_particles * sizeof(float));


      // check for errors
      if (!file.good()){
            cerr << endl << "***Error! Error writing DCD frame data" << endl << endl;
            throw runtime_error("Error writing DCD file");
      }
    }
    
    void write_updated_header(std::fstream &file, unsigned int timestep) {
        file.seekp(NFILE_POS);
        write_int(file, m_num_frames_written);

        file.seekp(NSTEP_POS);
        write_int(file, timestep);
    }
    
    void write_mol2_file() {
      size_t found=m_fname.find_last_of(".");
      string newnamefile = m_fname.substr(0,found);
      newnamefile.append(".mol2");
      if(!exists(newnamefile)){
        cout << "Writing Mol2 name file: " << newnamefile << endl;
        fstream mol2file;
        mol2file.open(newnamefile.c_str(), ios::trunc | ios::out);  
        mol2file << "@<TRIPOS>MOLECULE"<< endl;
        mol2file << "MOLDYNAMICS "
              << (*m_Box).SizeX << "\t"
              << (*m_Box).SizeY << "\t"
              << (*m_Box).SizeZ << "\t" << endl;
        mol2file << n_particles << " 1" << endl;
        mol2file << "NO_CHARGES" << endl;
        mol2file << "@<TRIPOS>ATOM" << endl;
        for( int i = 1; i <= n_particles; i++ ){
          mol2file << i << " A " 
                << (*m_Box).PosX[i] << " " 
                << (*m_Box).PosY[i] << " " 
                << (*m_Box).PosZ[i] << endl;
        }
        mol2file << "@<TRIPOS>BOND" << endl; 
        mol2file << "1 1 2 1" << endl; 
        mol2file.close();
      }
    }
};

#endif

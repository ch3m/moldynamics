#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE moldynamics
#include "boost/test/unit_test.hpp"
#include "../src/Box.h"
#include "../src/ReadSimConfigXML.h"
#include "../src/ReadBoxConfig.h"
#include "../src/Integrator.h"
#include "../src/StdOutput.h"
#include "boost/test/floating_point_comparison.hpp"
 
#ifndef MEDIDA_TYPE
#define MEDIDA_TYPE double
#endif

#ifndef N_TYPE 
#define N_TYPE long int
#endif
 
//Pruebas de precision
BOOST_AUTO_TEST_SUITE(Precision)

BOOST_AUTO_TEST_CASE(PotentialEnergy)
{
    Box<MEDIDA_TYPE,N_TYPE> boxset;
    string str = "./config_test.xml";
    ReadSimConfigXML<MEDIDA_TYPE,N_TYPE> SimXMLConf(str);
    SimXMLConf.Reader(boxset.SimulationParams);
    ReadBoxConfig<MEDIDA_TYPE,N_TYPE> BoxFromFile(boxset.SimulationParams.boxfile_name);
    BoxFromFile.Reader(boxset);
    Integrator<MEDIDA_TYPE,N_TYPE> Integrate(boxset);
    StdOutput<MEDIDA_TYPE,N_TYPE> Salida;
//    Salida.PrintAllProperties(boxset);
    boxset.SimulationParams.InitStep();
    while( boxset.SimulationParams.EndStep()  ){
      Integrate.VelocityVerletNVT(boxset);
      boxset.SimulationParams.NextStep();
    };
//    Salida.PrintCurrentProperties(boxset);
    BOOST_CHECK_CLOSE(boxset.PotentialEnergy/boxset.TotalParticles
        , -3.7, 1.94);
}

BOOST_AUTO_TEST_SUITE_END()
  

//Pruebas para la lectura de archivos
BOOST_AUTO_TEST_SUITE(ReadFiles)
 
BOOST_AUTO_TEST_CASE(testxml)
{
  BOOST_TEST_MESSAGE("Probando posibles lecturas en lectura de XML");
}
 
BOOST_AUTO_TEST_SUITE_END()
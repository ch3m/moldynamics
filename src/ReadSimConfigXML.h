/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef READSIMCONFIGXML_h
#define READSIMCONFIGXML_h
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "SimParams.h"
#include "Potential.h"
#include "LJ_pot.h"

using boost::property_tree::ptree;
using namespace boost::property_tree::xml_parser;
using namespace std;

template<class Tmedida,class Tn>
class ReadSimConfigXML{
public:
    //Put Public variables

    //Constructors & destructor
    ReadSimConfigXML(std::string& filename ){
      read_xml(filename, pt);      
    };
    ReadSimConfigXML(const ReadSimConfigXML& from){};
    ~ReadSimConfigXML(void){};

    //some funtion
    void Reader(SimParams<Tmedida,Tn> &param){
      //Steps
      param.NumSteps = pt.get<Tn>("moldynamics.configuration.steps.<xmlattr>.total");
      param.NumAverage = pt.get<Tn>("moldynamics.configuration.steps.<xmlattr>.average_period");
      param.OutputFrequency = pt.get<Tn>("moldynamics.configuration.steps.<xmlattr>.output_period");
      //settings
      param.deltaT = pt.get<Tmedida>("moldynamics.configuration.settings.<xmlattr>.deltaT");
      param.Temperature = pt.get<Tmedida>("moldynamics.configuration.settings.<xmlattr>.temperature");
      param.CutRadius = pt.get<Tmedida>("moldynamics.configuration.settings.<xmlattr>.cut_radio");
      //DCD
      param.dcd_use = pt.get<bool>("moldynamics.configuration.DCD.<xmlattr>.using");
      param.dcd_period = pt.get<Tn>("moldynamics.configuration.DCD.<xmlattr>.period");
      param.dcd_overwrite = pt.get<bool>("moldynamics.configuration.DCD.<xmlattr>.overwrite");
      //Boxfile
      param.boxfile_name = pt.get<string>("moldynamics.configuration.boxfile.<xmlattr>.name");
      //Potential
      param.Potential_type = pt.get<string>("moldynamics.configuration.potential.<xmlattr>.type");
      if(!param.Potential_type.compare("LJ")){
        Tmedida s = pt.get<Tmedida>("moldynamics.configuration.potential.<xmlattr>.sigma");
        Tmedida e = pt.get<Tmedida>("moldynamics.configuration.potential.<xmlattr>.epsilon");
        param.Pot = new LJ<Tmedida,Tn>(s,e);
        param.set_Potential(s,e);
      }else{
        cout << "Invalid potential type in XML file" << endl;
        exit(15);
      }
    };
    

protected:
private:
    ptree pt;
};

#endif

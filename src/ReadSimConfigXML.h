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
    };
    

protected:
private:
    ptree pt;
};

#endif

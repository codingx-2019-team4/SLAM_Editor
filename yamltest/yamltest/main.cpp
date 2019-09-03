#include <iostream>
#include <fstream>

#include<vector>
#include <stdio.h>

#include<yaml-cpp/yaml.h>
#include <iomanip>

#include<json.hpp>
using json = nlohmann::json;

using namespace std;
//using namespace YAML;



int main( int argc, char** argv )
{
    YAML::Node config;
    YAML::Emitter out;



    if (argc-2==0) {
        cout<<"Error path to yaml file."<<endl;
        return 0;
    }else{
        cout<<"Reading file :"<< argv[1] <<endl;
        config = YAML::LoadFile(argv[1]);
        //Don't use "YAML::LoadFile", because it only can read file


    }
    //////////////////////////////////////////////////
    string image = config["image"].as<string>();
    double resolution = config["resolution"].as<double>();

    int negate = config["negate"].as<int>();
    double occupied_thresh = config["occupied_thresh"].as<double>();
    double free_thresh = config["free_thresh"].as<double>();

    vector<double> origin;
    origin = config["origin"].as<vector<double>>();

    cout << "image:" << image << endl;
    cout << "resolution:" << resolution << endl;

    cout<<"origin: [";
    for (std::vector<double>::const_iterator i = origin.begin(); i != origin.end(); ++i){
        cout << *i << ' ';
    }
    cout<<"]"<<endl;

    cout << "negate:" << negate  << endl;
    cout << "occupied_thresh:" << occupied_thresh << endl;
    cout << "free_thresh:" << free_thresh << endl;

    json data2save;

    data2save["image"] = image;
    data2save["resolution"] = resolution;
    data2save["origin"] = origin;
    data2save["negate"] = negate;
    data2save["occupied_thresh"] = occupied_thresh;
    data2save["free_thresh"] = free_thresh;

    string savePath = string(argv[2])+"output.json";
    std::ofstream o(savePath);
    o << std::setw(4) << data2save << std::endl;




    return 0;
}

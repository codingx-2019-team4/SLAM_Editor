#include <iostream>
#include <fstream>
#include <stdio.h>

#include<yaml-cpp/yaml.h>

using namespace std;
//using namespace YAML;



int main( int argc, char** argv )
{
    YAML::Node config;
    YAML::Emitter out;



    if (argc-1==0) {
        cout<<"Error path to yaml file."<<endl;
        //return 0;
    }else{
        cout<<"Reading file :"<< argv[1] <<endl;
        config = YAML::LoadFile(argv[1]);
        //Don't use "YAML::LoadFile", because it only can read file


    }

    cout << "name:" << config["name"].as<string>() << endl;
    cout << "sex:" << config["sex"].as<string>() << endl;
    cout << "age:" << config["age"].as<int>() << endl;


    cout << "skills c++:" << config["skills"]["c++"].as<int>() << endl;
    cout << "skills java:" << config["skills"]["java"].as<int>() << endl;
    cout << "skills android:" << config["skills"]["android"].as<int>() << endl;
    cout << "skills python:" << config["skills"]["python"].as<int>() << endl;


    out << YAML::BeginMap;
    //out << config;
    out << YAML::Key << "name";
    out << YAML::Value << "Ryan Braun";
    out << YAML::Key << "position";
    out << YAML::Value << "LF";
    out << YAML::EndMap;



    std::ofstream fout(argv[1]);
    config["score"]=99;
    fout << config;
    fout.close();

    //std::ofstream fout(argv[1]);


    return 0;
}

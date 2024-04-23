#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    //TODO
    if (argc < 6 || argc > 6){
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Airline> <Query_Start_Age> <Query_End_Age>" << endl;
    }
    ifstream inStream; 
    inStream.open(argv[1]);
    string line;
    int arrayCapacity = 10;
    int recordIdx = 0;
    int *doubleCounter = new int;
    *doubleCounter = 0;
    AirlinePassenger *passengerArray = new AirlinePassenger[arrayCapacity];
    string parameters[4];
    parameters[0] = argv[2];
    parameters[1] = argv[3];
    parameters[2] = argv[4];
    parameters[3] = argv[5];
    parseFile(inStream, parameters, passengerArray, arrayCapacity, recordIdx, *doubleCounter);
    cout << "Array doubled: " << *doubleCounter << endl;
    cout << "Total number of passengers returned after the query: " << recordIdx << endl;
    printQueriedPassengers(passengerArray, recordIdx);
    inStream.close();
    return 0;
}

#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    //TODO
    string line;
    while (getline(input, line)){
        string name;
        string airline;
        string city;
        string age;
        stringstream ss(line);
        getline(ss,name,',');
        getline(ss,airline,',');
        getline(ss,city,',');
        getline(ss,age);
        int ageint = stoi(age);    
        AirlinePassenger passenger;
        passenger.age = ageint;
        passenger.airline = airline;
        passenger.location = city;
        passenger.name = name;
        bool add = false;
        add = isPassengerQueried(passenger, queryParams[0]/*city */, queryParams[1]/*airline */, stoi(queryParams[2])/*agemin */, stoi(queryParams[3])/*agemax */);
        if (add == true){
            addPassenger(passengers, passenger, arrCapacity, recordIdx, doublingCounter);
        }
    } 
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
    //TODO
    if ((passenger.location == queryLocation) && (passenger.airline == queryAirline) && (passenger.age >=startAge && passenger.age <= endAge)){
        return true;
    } else {
        return false;
    }
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
   //TODO
   *arraySize = *arraySize*2;
   AirlinePassenger *newArray = new AirlinePassenger[*arraySize];
   for (int i = 0; i < (*arraySize)/2; i++){
        newArray[i] = passengers[i];
   }
   delete[] passengers;
   passengers = newArray;
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
   //TODO
   if (recordIdx == arrCapacity){
    resizeArr(passengers,&arrCapacity);
    doublingCounter +=1;
   }
    passengers[recordIdx] = airlinePassenger;
    recordIdx++;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {
    AirlinePassenger tempArray[length];
    for (int j = 0; j < length; j++){
        int max = 0;
        int index = 0;
        for (int i =0; i < length;i++){
            if (passengers[i].age > max){
                max = passengers[i].age;
                index = i;
            } else if (passengers[i].age == max){
                int charindex;
                for (int k = 0; k < passengers[i].name.size();k++){
                    if (passengers[i].name[k] != passengers[index].name[k]){
                        charindex = i;
                        k = passengers[i].name.size();
                    }
                }
                if(int(passengers[i].name[0] == int(passengers[index].name[0]))){
                     if(int(passengers[i].name[charindex] < int(passengers[index].name[charindex]))){
                    index = i;
                }
                } else if(int(passengers[i].name[0] < int(passengers[index].name[0]))){
                    index = i;
                }
                //Else index == index
            }
        }
        tempArray[j] = passengers[index];
        passengers[index].age = -1;
    }
    for (int x = 0; x < length; x++){
        passengers[x] = tempArray[x];
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    sortPassengers(passengers, numOfRecords);
    
    cout << "Queried Passengers\n---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; i++){
        cout << passengers[i].name<< " " << passengers[i].age << endl;
    }
}

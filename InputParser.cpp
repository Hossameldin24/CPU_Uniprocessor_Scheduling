#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "./Process.cpp"

using namespace std;

class InputParser {
    private:
        string outputType;
        vector<string> algorithmsList;
        int endTime;
        int numProcesses;
        vector<Process> Processes;

        vector<string> splitByDelim(string line, char delim) {
            vector<string> result;
            stringstream ss(line);
            string value;

            while (getline(ss, value, delim)) {
                result.push_back(value);
            }

            return result;
        }

    public:
        InputParser(){

        }

        bool readFile(string fileName) {
            ifstream file(fileName);
            if (!file.is_open()) {
                cerr << "Unable to open file " << fileName << endl;
                return false;
            }

            string line;

            getline(file, line);
            outputType = line;

            getline(file, line);
            algorithmsList = splitByDelim(line, ',');

            getline(file, line);
            endTime = stoi(line);

            getline(file, line);
            numProcesses = stoi(line);

            for(int i = 0; i < numProcesses; i++){
                getline(file, line);
                vector<string> processConfig = splitByDelim(line, ',');

                Process process = Process(processConfig[0][0], stoi(processConfig[1]), stoi(processConfig[2]));
                Processes.push_back(process);
            }

            file.close();
            return true;
        }

        string getOutputType(){
            return outputType;
        }

        vector<string> getAlgorithmsList(){
            return algorithmsList;
        }

        int getEndTime(){
            return endTime;
        }

        int getNumProcesses(){
            return numProcesses;
        }

        vector<Process> getProcesses(){
            return Processes;
        }
};
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

        bool readFile() {

            string line;

            getline(cin, line);
            outputType = line;

            getline(cin, line);
            algorithmsList = splitByDelim(line, ',');

            getline(cin, line);
            endTime = stoi(line);

            getline(cin, line);
            numProcesses = stoi(line);

            for(int i = 0; i < numProcesses; i++){
                getline(cin, line);
                vector<string> processConfig = splitByDelim(line, ',');

                Process process = Process(processConfig[0][0], stoi(processConfig[1]), stoi(processConfig[2]));
                Processes.push_back(process);
            }

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
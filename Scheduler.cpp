#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "./InputParser.cpp"
#include "./Process.cpp"

using namespace std;

class Scheduler {
    private:
        InputParser parser;
        string filePath;

    public:
        Scheduler(string filePath){
            parser = InputParser();
            this->filePath = filePath;
        }

        void runSchedule(){
            parser.readFile(this->filePath);
            vector<string> algorithms = parser.getAlgorithmsList();
            vector<Process> processes = parser.getProcesses();
            int numProcess = parser.getNumProcesses();
            int endTime = parser.getEndTime();

            if(parser.getOutputType() == "stats"){
                for(string algorithm : algorithms){
                    vector<vector<string>> output;


                    printStatsOutput(output);
                }
            }
        }

        void printTraceOutput(){

        }

        void printStatsOutput(vector<vector<string>> inputVectors){
            std::ofstream file(filePath);

            if (!file) {
                std::cerr << "Error opening file: " << filePath << std::endl;
                return;
            }

            for (int i = 0; i < inputVectors[0].size(); i++) {
                file << std::setw(10) << inputVectors[0][i] << " |  ";
            }
            file << "\n";

            file << "Process    |  Arrival    |  Service    |  Finish    |  Turnaround    |  NormTurn    |\n";

            for (int i = 1; i < inputVectors.size(); i++) {
                for (int j = 0; j < inputVectors[i].size(); j++) {
                    file << std::setw(10) << inputVectors[i][j] << " |  ";
                }
                file << "\n";
            }

            double sumTurnaround = 0, sumNormTurn = 0;
            int n = inputVectors[4].size();

            for (int i = 0; i < n; ++i) {
                sumTurnaround += std::stod(inputVectors[4][i]);
                sumNormTurn += std::stod(inputVectors[5][i]);
            }

            double meanTurnaround = sumTurnaround / n;
            double meanNormTurn = sumNormTurn / n;

            file << "Mean |  " << fixed << setprecision(2) << meanTurnaround << " |  "
                << fixed << setprecision(2) << meanNormTurn << " |\n";

            file.close();
        }

};
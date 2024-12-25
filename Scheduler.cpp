#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "./InputParser.cpp"

using namespace std;

class Scheduler {
    private:
        InputParser parser;
        string inputFilePath;
        string outputFilePath;
        vector<Process> processes;
        int numProcesses;
        int endTime;
        vector<string> algorithms;
        string outputType;

    public:
        Scheduler(string inputFilePath, string outputFilePath){
            parser = InputParser();
            this->inputFilePath = inputFilePath;
            this->outputFilePath = outputFilePath;
        }

        void runSchedule(){
            parser.readFile(this->inputFilePath);
            algorithms = parser.getAlgorithmsList();
            processes = parser.getProcesses();
            numProcesses = parser.getNumProcesses();
            endTime = parser.getEndTime();
            outputType = parser.getOutputType();

            cout << outputType << endl;

            if(outputType == "stats"){
                for(string algorithm : algorithms){
                    vector<vector<string>> output;
                    
                    if(algorithm == "FCFS"){
                        // output = FCFS(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "RR"){
                        // output = RR(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "SPN"){
                        // output = SPN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "SRT"){
                        // output = SRT(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "HRRN"){
                        // output = HRRN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "FB-1"){
                        // output = FB-1(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "FB-2i"){
                        // output = FB-2i(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "Aging"){
                        // output = Aging(); - UNCOMMENT WHEN IMPLEMENTED
                    }else{
                        cerr << "Incorrect algorithm name" << endl;
                    }

                    printStatsOutput(algorithm, output);
                }
            }else if(parser.getOutputType() == "trace"){
                for(string algorithm : algorithms){
                    vector<vector<string>> output;

                    if(algorithm == "FCFS"){
                        // output = FCFS(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "RR"){
                        // output = RR(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "SPN"){
                        // output = SPN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "SRT"){
                        // output = SRT(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "HRRN"){
                        // output = HRRN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "FB-1"){
                        // output = FB-1(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "FB-2i"){
                        // output = FB-2i(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "Aging"){
                        // output = Aging(); - UNCOMMENT WHEN IMPLEMENTED
                    }else{
                        cerr << "Incorrect algorithm name" << endl;
                    }

                    printTraceOutput(algorithm, output);
                }
            }else{
                cerr << "Invalid Output Type in input file" << endl;
            }
        }

        void printTraceOutput(string algorithm, vector<vector<string>> inputVectors){

        }

        void printStatsOutput(string algorithm, vector<vector<string>> inputVectors){
            ofstream file(outputFilePath);

            if (!file) {
                cerr << "Error opening file: " << outputFilePath << endl;
                return;
            }

            file << algorithm << "\n";

            file << "Process     |";
            for (int j = 0; j < inputVectors[0].size(); j++) {
                file << setw(10) << inputVectors[0][j] << " |  ";
            }
            file << "\n";

            double sumTurnaround = 0, sumNormTurn = 0;
            int n = inputVectors[4].size();

            for (int i = 0; i < n; ++i) {
                sumTurnaround += stod(inputVectors[4][i]);
                sumNormTurn += stod(inputVectors[5][i]);
            }

            double meanTurnaround = sumTurnaround / n;
            double meanNormTurn = sumNormTurn / n;

            file << "Mean |  " << fixed << setprecision(2) << meanTurnaround << " |  "
                << fixed << setprecision(2) << meanNormTurn << " |\n";

            file.close();
        }

};

int main() {
    Scheduler scheduler = Scheduler("./testcases/01b-input.txt", "./output.txt");
    scheduler.runSchedule();

}
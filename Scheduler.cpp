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

            if(outputType == "stats"){
                for(string algorithm : algorithms){
                    vector<vector<string>> output;
                    
                    if(algorithm == "1"){
                        // output = FCFS(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm[0] == '2'){
                        char q = algorithm[2];
                        // output = RR(q); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "3"){
                        // output = SPN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "4"){
                        // output = SRT(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "5"){
                        // output = HRRN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "6"){
                        // output = FB-1(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "7"){
                        // output = FB-2i(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm[0] == '8'){
                        char q = algorithm[2];
                        // output = Aging(q); - UNCOMMENT WHEN IMPLEMENTED
                    }else{
                        cerr << "Incorrect algorithm name" << endl;
                    }

                    output = {{"A", "B", "C", "D", "E"}, {"0","2","4","6","8"}, {"3","6","4","5","2"},{"3", "9", "13", "18", "20"}, {"3", "7", "9", "12", "12"}, {"1.00", "1.17", "2.25", "2.40", "6.00"}};

                    printStatsOutput(algorithm, output);
                }
            }else if(parser.getOutputType() == "trace"){
                for(string algorithm : algorithms){
                    vector<vector<string>> output;

                    if(algorithm == "1"){
                        // output = FCFS(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm[0] == '2'){
                        char q = algorithm[2];
                        // output = RR(q); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "3"){
                        // output = SPN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "4"){
                        // output = SRT(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "5"){
                        // output = HRRN(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "6"){
                        // output = FB-1(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm == "7"){
                        // output = FB-2i(); - UNCOMMENT WHEN IMPLEMENTED
                    }else if(algorithm[0] == '8'){
                        char q = algorithm[2];
                        // output = Aging(q); - UNCOMMENT WHEN IMPLEMENTED
                    }else{
                        cerr << "Incorrect algorithm name" << endl;
                    }

                    output = {{"A", "B", "C", "D", "E"}, {"0","2","4","6","8"}, {"3","6","4","5","2"},{"3", "9", "13", "18", "20"}, {"3", "7", "9", "12", "12"}, {"1.00", "1.17", "2.25", "2.40", "6.00"}};

                    printTraceOutput(algorithm, output);
                }
            }else{
                cerr << "Invalid Output Type in input file" << endl;
            }
        }

        void printTraceOutput(string algorithm, vector<vector<string>> inputVectors){
            ofstream file(outputFilePath);

            if (!file) {
                cerr << "Error opening file: " << outputFilePath << endl;
                return;
            }
            
            if(algorithm == "1"){
                algorithm = "FCFS";
            }else if(algorithm == "2"){
                algorithm = "RR";
            }else if(algorithm == "3"){
                algorithm = "SPN";
            }else if(algorithm == "4"){
                algorithm = "SRT";
            }else if(algorithm == "5"){
                algorithm = "HRRN";
            }else if(algorithm == "6"){
                algorithm = "FB-1";
            }else if(algorithm == "7"){
                algorithm = "FB-2i";
            }else if(algorithm == "8"){
                algorithm = "Aging";
            }

            file << left << setw(6) << algorithm;
            
            for(int i = 0; i < endTime; i++){
                file << i % 10 << " ";
            }

            file << "|\n";

        }

        void printStatsOutput(string algorithm, vector<vector<string>> inputVectors){
            ofstream file(outputFilePath);

            if (!file) {
                cerr << "Error opening file: " << outputFilePath << endl;
                return;
            }

            if(algorithm == "1"){
                algorithm = "FCFS";
            }else if(algorithm == "2"){
                algorithm = "RR";
            }else if(algorithm == "3"){
                algorithm = "SPN";
            }else if(algorithm == "4"){
                algorithm = "SRT";
            }else if(algorithm == "5"){
                algorithm = "HRRN";
            }else if(algorithm == "6"){
                algorithm = "FB-1";
            }else if(algorithm == "7"){
                algorithm = "FB-2i";
            }else if(algorithm == "8"){
                algorithm = "Aging";
            }

            file << algorithm << "\n";

            file << "Process        |";
            for (int j = 0; j < inputVectors[0].size(); j++) {
                file << setw(10) << inputVectors[0][j] << " |  ";
            }
            file << "\n";

            file << "Arrival        |";
            for (int j = 0; j < inputVectors[1].size(); j++) {
                file << setw(10) << inputVectors[1][j] << " |  ";
            }
            file << "\n";

            file << "Service        |";
            for (int j = 0; j < inputVectors[2].size(); j++) {
                file << setw(10) << inputVectors[2][j] << " |  ";
            }
            file << " Mean" << " |\n";

            file << "Finish         |";
            for (int j = 0; j < inputVectors[3].size(); j++) {
                file << setw(10) << inputVectors[3][j] << " |  ";
            }
            file << " -----" << "|\n";


            double sumTurnaround = 0, sumNormTurn = 0;
            int n = inputVectors[4].size();

            for (int i = 0; i < n; ++i) {
                sumTurnaround += stoi(inputVectors[4][i]);
                sumNormTurn += stoi(inputVectors[5][i]);
            }

            double meanTurnaround = sumTurnaround / n;
            double meanNormTurn = sumNormTurn / n;


            file << "Turnaround     |";
            for (int j = 0; j < inputVectors[4].size(); j++) {
                file << setw(10) << inputVectors[4][j] << " |  ";
            }
            file << setw(5) << meanTurnaround << " |\n";

            file << "NormTurn       |";
            for (int j = 0; j < inputVectors[5].size(); j++) {
                file << setw(10) << inputVectors[5][j] << " |  ";
            }
            file << setw(5) << meanNormTurn << " |\n";
            

            // file << "Mean |  " << fixed << setprecision(2) << meanTurnaround << " |  "
            //     << fixed << setprecision(2) << meanNormTurn << " |\n";

            file.close();
        }

};

int main() {
    Scheduler scheduler = Scheduler("./testcases/01a-input.txt", "./output2.txt");
    scheduler.runSchedule();

}
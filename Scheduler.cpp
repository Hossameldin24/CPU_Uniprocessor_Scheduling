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
                    
                    resetFinishTime();

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
                        output = HRRN();
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

                    printStatsOutput(algorithm, output);
                }
            }else if(parser.getOutputType() == "trace"){
                for(string algorithm : algorithms){

                    resetFinishTime();

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
                        output = HRRN();
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

            for(int i = 0; i < endTime + 1; i++){
                file << i % 10 << " ";
            }
            file << "\n";

            file << "------";
            for(int i = 0; i < endTime; i++){
                file << "--";
            }
            file << "-\n";

            for(int j = 0; j < numProcesses; j++){
                file << inputVectors[0][j] << "     |";

                int arrivalTime = stoi(inputVectors[1][j]);
                int finishTime = stoi(inputVectors[3][j]);
                int serviceTime = stoi(inputVectors[2][j]);
                int startTime = finishTime - serviceTime;

                for(int i = 0; i < arrivalTime; i++){
                    file << " |";
                }


                for(int i = arrivalTime; i < startTime; i++){
                    file << ".|";
                }

                for(int i = startTime; i < finishTime; i++){
                    file << "*|";
                }

                for(int i = finishTime; i < endTime; i++){
                    file << " |";
                }

                file << "\n";
            }

            file << "------";
            for(int i = 0; i < endTime; i++){
                file << "--";
            }
            file << "-\n";
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
                sumNormTurn += stod(inputVectors[5][i]);
            }

            double meanTurnaround = sumTurnaround / n;
            double meanNormTurn = sumNormTurn / n;


            file << "Turnaround     |";
            for (int j = 0; j < inputVectors[4].size(); j++) {
                file << setw(10) << inputVectors[4][j] << " |  ";
            }
            file << setw(5) <<  fixed << setprecision(2) << meanTurnaround << " |\n";

            file << "NormTurn       |";
            for (int j = 0; j < inputVectors[5].size(); j++) {
                file << setw(10)  << fixed << setprecision(2) << stod(inputVectors[5][j]) << " |  ";
            }
            file << setw(5) << fixed << setprecision(2) << meanNormTurn << " |\n";

            file.close();
        }

        vector<vector<string>> getProcessesStats(){
            vector<vector<string>> pStats(6);

            for(int i = 0 ; i < numProcesses ; i++){
                string str(1, processes[i].getName());
                pStats[0].push_back(str);
                pStats[1].push_back(to_string(processes[i].getArrivalTime()));
                pStats[2].push_back(to_string(processes[i].getServiceTime()));
                pStats[3].push_back(to_string(processes[i].getFinishTime()));
                pStats[4].push_back(to_string(processes[i].getTurnaround()));
                pStats[5].push_back(to_string(processes[i].getNormTurn()));

            }

            return pStats;
        }

        void resetFinishTime(){
            for(int i =  0 ; i < numProcesses ; i++){
                processes[i].setFinishTime(-1);
            }
        }

        double calculateRatio(int idx, int t){
            double waitingTime = t - processes[idx].getArrivalTime();
            double serviceTime = processes[idx].getServiceTime();

            double ratio = (waitingTime + serviceTime)/serviceTime;

            return ratio;
        }

        vector<vector<string>> HRRN(){
            
            int t = 0;

            while(t != endTime){
                
                int hrri = 1;
                double hrr = -1;

                for(int i = 0 ; i < numProcesses ; i++){

                    if(processes[i].getArrivalTime() <= t && processes[i].getFinishTime() == -1){

                        double ratio = calculateRatio(i, t);

                        if(ratio > hrr){
                            hrri = i;
                            hrr = ratio;
                        }
                    }
                }

                if(hrr == -1) {         //no ready processes in the current time
                    t+=1;
                    continue;
                }

                t += processes[hrri].getServiceTime();
                processes[hrri].setFinishTime(t);

            }

            return getProcessesStats();
        }

};

int main() {
    Scheduler scheduler = Scheduler("./testcases/06c-input.txt", "./output2.txt");
    scheduler.runSchedule();

}
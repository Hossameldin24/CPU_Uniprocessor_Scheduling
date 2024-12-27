#include<bits/stdc++.h>

using namespace std;

class Process {
    private:
        char processName;
        int processArrivalTime;
        int processServiceTime;
        int processFinishTime;
        int processProgressTime;

        set<int> processProgressTimes;

    public:
        Process(char name, int arrivalTime, int serviceTime){
            processName = name;
            processArrivalTime = arrivalTime;
            processServiceTime = serviceTime;
            processProgressTime = 0;
        }

        char getName(){
            return processName;
        }

        int getArrivalTime(){
            return processArrivalTime;
        }

        int getServiceTime(){
            return processServiceTime;
        }

        int getFinishTime(){
            return processFinishTime;
        }

        int getTurnaround(){
            return processFinishTime - processArrivalTime;
        }

        int getProgressTime(){
            return processProgressTime;
        }

        void incrementProgressTime(int progressTime){
            processProgressTime += progressTime;
        }

        set<int> getProgressTimes(){
            return processProgressTimes;
        }

        void appendProgressTimes(int progressTime){
            processProgressTimes.insert(progressTime);
        }
        
        double getNormTurn(){
            return (1.0*getTurnaround())/processServiceTime;
        }
        
        void setFinishTime(int finishTime){
            processFinishTime = finishTime;
        }
};
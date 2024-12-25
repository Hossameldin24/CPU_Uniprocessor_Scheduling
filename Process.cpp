class Process {
    private:
        char processName;
        int processArrivalTime;
        int processServiceTime;
    
    public:
        Process(char name, int arrivalTime, int serviceTime){
            processName = name;
            processArrivalTime = arrivalTime;
            processServiceTime = serviceTime;
        }

        char getProcessName(){
            return processName;
        }

        int getProcessArrivalTime(){
            return processArrivalTime;
        }

        int getProcessServiceTime(){
            return processServiceTime;
        }
};
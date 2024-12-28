#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <bits/stdc++.h>
#include "./InputParser.cpp"
#include <queue>

using namespace std;

class Scheduler
{
private:
    InputParser parser;
    string inputFilePath;
    vector<Process> processes;
    int numProcesses;
    int endTime;
    vector<string> algorithms;
    string outputType;

    void resetProcesses()
    {
        for (int i = 0; i < numProcesses; i++)
        {
            processes[i].resetProgressTimes();
            processes[i].resetProgressTime();
            processes[i].setFinishTime(-1);
        }
    }

public:
    Scheduler(string inputFilePath)
    {
        parser = InputParser();
        this->inputFilePath = inputFilePath;
    }

    void runSchedule()
    {
        parser.readFile(this->inputFilePath);
        algorithms = parser.getAlgorithmsList();
        processes = parser.getProcesses();
        sort(processes.begin(), processes.end(), [](Process a, Process b)
             { return a.getArrivalTime() < b.getArrivalTime(); });
        numProcesses = parser.getNumProcesses();
        endTime = parser.getEndTime();
        outputType = parser.getOutputType();
        if (outputType == "stats")
        {
            for (string algorithm : algorithms)
            {
                resetProcesses();
                vector<vector<string>> output;

                if (algorithm == "1")
                {
                    output = FCFS();
                }
                else if (algorithm[0] == '2')
                {
                    char q = algorithm[2];
                    output = RR(q - '0');
                }
                else if (algorithm == "3")
                {
                    output = SPN();
                }
                else if (algorithm == "4")
                {
                    output = SRT();
                }
                else if (algorithm == "5")
                {
                    output = HRRN();
                }
                else if (algorithm == "6")
                {
                    output = FB1();
                }
                else if (algorithm == "7")
                {
                    output = FB2();
                }
                else if (algorithm[0] == '8')
                {
                    char q = algorithm[2];
                    output = Aging(q - '0');
                }
                else
                {
                    cerr << "Incorrect algorithm name" << endl;
                }
                printStatsOutput(algorithm, output);
            }
        }
        else if (parser.getOutputType() == "trace")
        {
            for (string algorithm : algorithms)
            {
                resetProcesses();

                vector<vector<string>> output;
                if (algorithm == "1")
                {
                    output = FCFS();
                }
                else if (algorithm[0] == '2')
                {
                    char q = algorithm[2];
                    output = RR(q - '0');
                }
                else if (algorithm == "3")
                {
                    output = SPN();
                }
                else if (algorithm == "4")
                {
                    output = SRT();
                }
                else if (algorithm == "5")
                {
                    output = HRRN();
                }
                else if (algorithm == "6")
                {
                    output = FB1();
                }
                else if (algorithm == "7")
                {
                    output = FB2();
                }
                else if (algorithm[0] == '8')
                {
                    char q = algorithm[2];
                    output = Aging(q - '0');
                }
                else
                {
                    cerr << "Incorrect algorithm name" << endl;
                }
                printTraceOutput(algorithm);
            }
        }
        else
        {
            cerr << "Invalid Output Type in input file" << endl;
        }
    }

    void printTraceOutput(string algorithm)
    {

        if (algorithm == "1")
        {
            algorithm = "FCFS";
        }
        else if (algorithm[0] == '2')
        {
            char q = algorithm[2];
            algorithm = "RR";
            algorithm += "-";
            algorithm += q;
        }
        else if (algorithm == "3")
        {
            algorithm = "SPN";
        }
        else if (algorithm == "4")
        {
            algorithm = "SRT";
        }
        else if (algorithm == "5")
        {
            algorithm = "HRRN";
        }
        else if (algorithm == "6")
        {
            algorithm = "FB-1";
        }
        else if (algorithm == "7")
        {
            algorithm = "FB-2i";
        }
        else if (algorithm[0] == '8')
        {
            algorithm = "Aging";
        }

        cout << left << setw(6) << algorithm;

        for (int i = 0; i < endTime + 1; i++)
        {
            cout << i % 10 << " ";
        }
        cout << "\n";

        cout << "------";
        for (int i = 0; i < endTime; i++)
        {
            cout << "--";
        }
        cout << "--\n";

        if (algorithm[0] == 'R' || algorithm == "FB-1" || algorithm == "FB-2i" || algorithm == "SRT" || algorithm == "Aging")
        { // if algorithm policy is preemptive

            for (int j = 0; j < numProcesses; j++)
            {
                cout << processes[j].getName() << "     |";

                set<int> progressTimes = processes[j].getProgressTimes();

                int arrivalTime = processes[j].getArrivalTime();
                int startTime = endTime;
                if (!progressTimes.empty())
                {
                    startTime = *(progressTimes.begin());
                }

                int finishTime = endTime - 1;

                if (!progressTimes.empty())
                {
                    finishTime = min(endTime-1, *prev(progressTimes.end()));
                }

                for (int i = 0; i < arrivalTime; i++)
                {
                    cout << " |";
                }

                for (int i = arrivalTime; i < startTime; i++)
                {
                    cout << ".|";
                }

                for (int i = startTime; i <= finishTime; i++)
                {
                    if (progressTimes.find(i) != progressTimes.end())
                    {
                        cout << "*|";
                    }
                    else
                    {
                        cout << ".|";
                    }
                }

                for (int i = finishTime + 1; i < endTime; i++)
                {
                    cout << " |";
                }

                cout << " \n";
            }
        }

        else
        {
            for (int j = 0; j < numProcesses; j++)
            {

                cout << processes[j].getName() << "     |";

                int arrivalTime = processes[j].getArrivalTime();
                int finishTime = processes[j].getFinishTime();
                int serviceTime = processes[j].getServiceTime();
                int startTime = finishTime - serviceTime;

                for (int i = 0; i < arrivalTime; i++)
                {
                    cout << " |";
                }

                for (int i = arrivalTime; i < startTime; i++)
                {
                    cout << ".|";
                }

                for (int i = startTime; i < finishTime; i++)
                {
                    cout << "*|";
                }

                for (int i = finishTime; i < endTime; i++)
                {
                    cout << " |";
                }
                cout << " \n";
            }
        }

        cout << "------";
        for (int i = 0; i < endTime; i++)
        {
            cout << "--";
        }
        cout << "--\n\n";
    }

    void printStatsOutput(string algorithm, vector<vector<string>> inputVectors)
    {
        if (algorithm == "1")
        {
            algorithm = "FCFS";
        }
        else if (algorithm[0] == '2')
        {
            char q = algorithm[2];
            algorithm = "RR";
            algorithm += "-";
            algorithm += q;
        }
        else if (algorithm == "3")
        {
            algorithm = "SPN";
        }
        else if (algorithm == "4")
        {
            algorithm = "SRT";
        }
        else if (algorithm == "5")
        {
            algorithm = "HRRN";
        }
        else if (algorithm == "6")
        {
            algorithm = "FB-1";
        }
        else if (algorithm == "7")
        {
            algorithm = "FB-2i";
        }
        else if (algorithm[0] == '8')
        {
            algorithm = "Aging";
        }

        cout << algorithm << "\n";

        cout << "Process    |";
        for (int j = 0; j < inputVectors[0].size(); j++)
        {
            cout << "  " << inputVectors[0][j] << "  |";
        }
        cout << "\n";

        cout << "Arrival    |";
        for (int j = 0; j < inputVectors[1].size(); j++)
        {
            cout << setw(3) << inputVectors[1][j] << "  |";
        }
        cout << "\n";

        cout << "Service    |";
        for (int j = 0; j < inputVectors[2].size(); j++)
        {
            cout << setw(3) << inputVectors[2][j] << "  |";
        }
        cout << " Mean|\n";

        cout << "Finish     |";
        for (int j = 0; j < inputVectors[3].size(); j++)
        {
            cout << setw(3) << inputVectors[3][j] << "  |";
        }
        cout << "-----|\n";

        double sumTurnaround = 0, sumNormTurn = 0;
        int n = inputVectors[4].size();

        for (int i = 0; i < n; ++i)
        {
            sumTurnaround += stoi(inputVectors[4][i]);
            sumNormTurn += stod(inputVectors[5][i]);
        }

        double meanTurnaround = sumTurnaround / n;
        double meanNormTurn = sumNormTurn / n;

        cout << "Turnaround |";
        for (int j = 0; j < inputVectors[4].size(); j++)
        {
            cout << setw(3) << inputVectors[4][j] << "  |";
        }
        cout << setw(5) << fixed << setprecision(2) << meanTurnaround << "|\n";

        cout << "NormTurn   |";
        for (int j = 0; j < inputVectors[5].size(); j++)
        {
            cout << setw(5) << fixed << setprecision(2) << stod(inputVectors[5][j]) << "|";
        }
        cout << setw(5) << fixed << setprecision(2) << meanNormTurn << "|\n";
        cout << "\n";
    }

    vector<vector<string>> getProcessesStats()
    {
        vector<vector<string>> pStats(6);

        for (int i = 0; i < numProcesses; i++)
        {
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


    double calculateRatio(int idx, int t)
    {
        double waitingTime = t - processes[idx].getArrivalTime();
        double serviceTime = processes[idx].getServiceTime();

        double ratio = (waitingTime + serviceTime) / serviceTime;

        return ratio;
    }

    vector<vector<string>> FCFS()
    {

        int currTime = 0;
        int i = 0;
        while (currTime < endTime)
        {
            Process *nextProcess = &processes[i];
            int arrivalTime = nextProcess->getArrivalTime();
            int serviceTime = nextProcess->getServiceTime();

            if (arrivalTime > currTime)
            {
                currTime = arrivalTime;
            }

            currTime += serviceTime;
            nextProcess->setFinishTime(currTime);

            i++;
        }

        return getProcessesStats();
    }

    vector<vector<string>> RR(int quantum)
    {
        queue<Process *> processQueue;
        vector<Process *> notArrived;

        for (int i = 0; i < processes.size(); i++)
        {
            notArrived.push_back(&processes[i]);
        }

        int currTime = notArrived[0]->getArrivalTime();

        while (!notArrived.empty() && notArrived.front()->getArrivalTime() == currTime)
        {
            processQueue.push(notArrived.front());
            notArrived.erase(notArrived.begin());
        }

        while ((!processQueue.empty() || !notArrived.empty()) && currTime < endTime)
        {

            while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
            {
                processQueue.push(notArrived.front());
                notArrived.erase(notArrived.begin());
            }

            Process *currProcess = processQueue.front();
            processQueue.pop();

            int compTime = currProcess->getProgressTime();
            int remTime = currProcess->getServiceTime() - compTime;

            int runTime = min(quantum, remTime);

            for(int i = 0 ; i < runTime ; i++){
                currProcess->appendProgressTimes(currTime+i);
            }

            currTime += runTime;
            currProcess->incrementProgressTime(runTime);

            if (currProcess->getProgressTime() < currProcess->getServiceTime())
            {
                while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
                {
                    processQueue.push(notArrived.front());
                    notArrived.erase(notArrived.begin());
                }
                processQueue.push(currProcess);
            }
            else
            {
                currProcess->setFinishTime(currTime);
            }
        }
        return getProcessesStats();
    }

    struct CompareProcessTime
    {
        bool operator()(Process *a, Process *b)
        {
            if (a->getServiceTime() == b->getServiceTime())
                return a->getArrivalTime() > b->getArrivalTime();
            return a->getServiceTime() > b->getServiceTime();
        }
    };

    struct CompareRemainingTime
    {
        bool operator()(Process *a, Process *b)
        {
            int remainingA = a->getServiceTime() - a->getProgressTime();
            int remainingB = b->getServiceTime() - b->getProgressTime();

            if (remainingA == remainingB)
                return a->getArrivalTime() > b->getArrivalTime();
            return remainingA > remainingB;
        }
    };

    vector<vector<string>> SPN()
    {
        priority_queue<Process *, vector<Process *>, CompareProcessTime> readyQueue;

        vector<Process *> notArrived;
        for (int i = 0; i < numProcesses; i++)
        {
            notArrived.push_back(&processes[i]);
        }

        int currTime = 0;

        while ((!readyQueue.empty() || !notArrived.empty()) && currTime < endTime)
        {
            while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
            {
                readyQueue.push(notArrived.front());
                notArrived.erase(notArrived.begin());
            }

            if (readyQueue.empty() && !notArrived.empty())
            {
                currTime = notArrived.front()->getArrivalTime();
                continue;
            }

            if (readyQueue.empty())
                break;

            Process *currentProcess = readyQueue.top();
            readyQueue.pop();

            int serviceTime = currentProcess->getServiceTime();
            currTime += serviceTime;

            currentProcess->setFinishTime(currTime);
        }

        return getProcessesStats();
    }

    vector<vector<string>> SRT()
    {
        priority_queue<Process *, vector<Process *>, CompareRemainingTime> readyQueue;

        vector<Process *> notArrived;
        for (int i = 0; i < numProcesses; i++)
        {
            notArrived.push_back(&processes[i]);
        }

        int currTime = 0;

        while ((!notArrived.empty() || !readyQueue.empty()) && currTime < endTime)
        {
            while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
            {
                readyQueue.push(notArrived.front());
                notArrived.erase(notArrived.begin());
            }

            if (readyQueue.empty() && !notArrived.empty())
            {
                currTime = notArrived.front()->getArrivalTime();
                continue;
            }

            if (readyQueue.empty())
                break;

            Process *nextProcess = readyQueue.top();
            readyQueue.pop();
            int nextArrivalTime = notArrived.empty() ? INT_MAX : notArrived.front()->getArrivalTime() - currTime;
            int remTime = nextProcess->getServiceTime() - nextProcess->getProgressTime();
            int runTime = min(remTime, nextArrivalTime);

            for(int i = 0 ; i < runTime ; i++){
                nextProcess->appendProgressTimes(currTime+i);
            }

            currTime += runTime;
            nextProcess->incrementProgressTime(runTime);
            if (nextProcess->getProgressTime() >= nextProcess->getServiceTime())
            {
                nextProcess->setFinishTime(currTime);
            }
            else
            {
                readyQueue.push(nextProcess);
            }
        }

        return getProcessesStats();
    }

    vector<vector<string>> HRRN()
    {

        int t = 0;

        while (t <= endTime)
        {

            int hrri = 1;
            double hrr = -1;

            for (int i = 0; i < numProcesses; i++)
            {

                if (processes[i].getArrivalTime() <= t && processes[i].getFinishTime() == -1)
                {

                    double ratio = calculateRatio(i, t);

                    if (ratio > hrr)
                    {
                        hrri = i;
                        hrr = ratio;
                    }
                }
            }

            if (hrr == -1)
            { // no ready processes in the current time
                t += 1;
                continue;
            }

            t += processes[hrri].getServiceTime();
            processes[hrri].setFinishTime(t);
        }

        return getProcessesStats();
    }

    vector<vector<string>> FB1()
    {

        int t = 0;

        vector<queue<pair<Process *, int>>> qn(1);

        while (t <= endTime)
        {

            int lastEnti = 0;

            for (int i = 0; i < numProcesses; i++)
            {

                if (processes[i].getArrivalTime() == t && processes[i].getFinishTime() == -1)
                {
                    qn[0].push({&processes[i], i});
                }
            }

            int iq = -1;

            int pcount = 0;

            for (int i = 0; i < qn.size(); i++)
            {

                if (!qn[i].empty())
                {
                    if (iq == -1)
                    {
                        iq = i;
                        lastEnti = qn[i].front().second;
                    }

                    pcount += qn[i].size();
                }
            }

            if (iq == -1)
            { // all queues are empty
                t++;
                continue;
            }

            if (pcount == 1 && ((lastEnti + 1 < numProcesses && processes[lastEnti + 1].getArrivalTime() != t + 1) || lastEnti == numProcesses - 1))
            {
                // The only process in all queues at the current time
                qn[iq].front().first->appendProgressTimes(t);

                t++;
                qn[iq].front().first->incrementProgressTime(1);

                if (qn[iq].front().first->getProgressTime() == qn[iq].front().first->getServiceTime())
                {
                    qn[iq].front().first->setFinishTime(t);
                    qn[iq].pop();
                }
                continue;
            }

            pair<Process *, int> popped = qn[iq].front();
            qn[iq].pop();
            popped.first->incrementProgressTime(1);
            popped.first->appendProgressTimes(t);

            t++;

            if (popped.first->getServiceTime() == popped.first->getProgressTime())
            {
                popped.first->setFinishTime(t);
            }

            else if (qn.size() - 1 > iq)
            { // there exist a following queue
                qn[iq + 1].push(popped);
            }

            else
            {
                queue<pair<Process *, int>> newQ;
                newQ.push(popped);
                qn.push_back(newQ);
            }
        }

        return getProcessesStats();
    }

    vector<vector<string>> FB2()
    {

        int t = 0, tPrev = -1;

        vector<queue<pair<Process *, int>>> qn(1);

        vector<int> quanta(numProcesses, 1);

        while (t <= endTime)
        {

            int lastEnti = 0;

            for (int i = 0; i < numProcesses; i++)
            {

                if (processes[i].getArrivalTime() == t)
                {
                    qn[0].push({&processes[i], i});
                }
            }

            if (t <= tPrev)
            { // there is a running process within the current time slice
                t++;
                continue;
            }

            int iq = -1, pcount = 0;

            for (int i = 0; i < qn.size(); i++)
            {

                if (!qn[i].empty())
                {
                    if (iq == -1)
                    {
                        iq = i;
                        lastEnti = qn[i].front().second;
                    }

                    pcount += qn[i].size();
                }
            }

            if (iq == -1) // all queues are empty
            {
                t++;
                continue;
            }

            bool stayInQueue = true;

            for (int i = 0; i <= quanta[lastEnti]; i++)
            {
                if (lastEnti + 1 < numProcesses && processes[lastEnti + 1].getArrivalTime() == t + i)
                {
                    stayInQueue = false;
                    break;
                }
            }

            if (pcount == 1 && stayInQueue) // The only process in all queues at the current time
            {
                int progressTime = qn[iq].front().first->getProgressTime();

                for (int i = 0; i < quanta[lastEnti]; i++)
                {

                    progressTime += 1;

                    qn[iq].front().first->incrementProgressTime(1);
                    qn[iq].front().first->appendProgressTimes(t + i);

                    if (progressTime == qn[iq].front().first->getServiceTime())
                    {
                        qn[iq].front().first->setFinishTime(t + i + 1);
                        qn[iq].pop();

                        break;
                    }
                }

                t += quanta[lastEnti];
                continue;
            }

            pair<Process *, int> popped = qn[iq].front();
            qn[iq].pop();

            int endInterval = min(quanta[lastEnti], popped.first->getServiceTime() - popped.first->getProgressTime());

            popped.first->incrementProgressTime(endInterval);

            for (int i = 0; i < endInterval; i++)
            {

                popped.first->appendProgressTimes(t + i);
                tPrev = t + i;
            }

            if (popped.first->getServiceTime() == popped.first->getProgressTime())
            {
                popped.first->setFinishTime(t + endInterval);
            }

            else if (qn.size() - 1 > iq) // there exist a following queue
            {
                qn[iq + 1].push(popped);
                quanta[lastEnti] *= 2;
            }

            else
            {
                queue<pair<Process *, int>> newQ;
                newQ.push(popped);
                qn.push_back(newQ);
                quanta[lastEnti] *= 2;
            }
            t++;
        }
        return getProcessesStats();
    }

    
    vector<vector<string>> Aging(int quantum)
    {
        deque<Process *> processQueue;
        vector<Process *> notArrived;

        for (int i = 0; i < processes.size(); i++)
        {
            //no service time for any process
            processes[i].setFinishTime(endTime);
            processes[i].appendProgressTimes(endTime+1);
            notArrived.push_back(&processes[i]);
        }

        int currTime = notArrived[0]->getArrivalTime();

        while (!notArrived.empty() && notArrived.front()->getArrivalTime() == currTime)
        {
            processQueue.push_back(notArrived.front());
            notArrived.erase(notArrived.begin());
        }

        while ((!processQueue.empty() || !notArrived.empty()) && currTime < endTime)
        {

            while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
            {
                processQueue.push_back(notArrived.front());
                notArrived.erase(notArrived.begin());
            }

            Process *currProcess = processQueue.front();

            int currIdx = 0;

            for(int i = 0 ; i < processQueue.size() ;i++){
                if(currProcess->getPriority() < processQueue[i]->getPriority()){
                    currProcess = processQueue[i];
                    currIdx = i;
                }
            }

            processQueue.erase(processQueue.begin() + currIdx);

            int runTime = quantum;

            for(int i = 0 ; i < runTime ; i++){
                currProcess->appendProgressTimes(currTime+i);
            }

            currTime += runTime;

            while (!notArrived.empty() && notArrived.front()->getArrivalTime() <= currTime)
            {
                processQueue.push_back(notArrived.front());
                notArrived.erase(notArrived.begin());
            }


            currProcess->resetPriority();
            for(int i = 0 ; i < processQueue.size() ;i++){
                processQueue[i]->incrementPriority();
            }

            processQueue.push_back(currProcess);
        }

        return getProcessesStats();

    }


};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file_path>" << endl;
        return 1;
    }

    string inputFilePath = argv[1];

    Scheduler scheduler(inputFilePath);
    scheduler.runSchedule();

    return 0;
}
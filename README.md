# CPU Uniprocessor Scheduling

This project implements various CPU scheduling algorithms for a uniprocessor system. The implemented algorithms include:

- First-Come, First-Served (FCFS)
- Round Robin (RR)
- Shortest Process Next (SPN)
- Shortest Remaining Time (SRT)
- Highest Response Ratio Next (HRRN)
- Feedback (FB1, FB2)
- Aging

## Project Structure

- `Scheduler.cpp`: Contains the main scheduling logic and implementation of different scheduling algorithms.
- `Process.cpp`: Defines the `Process` class, which represents a process in the scheduling system.
- `InputParser.cpp`: Handles input parsing and initialization of processes and scheduling parameters.
- `Dockerfile`: Docker configuration for building and running the project in a containerized environment.
- `.gitignore`: Specifies files and directories to be ignored by Git.

## Building the Project

To build the project, you can use the provided Dockerfile. Ensure you have Docker installed on your system.

1. Build the Docker image:
    ```sh
    docker build -t cpu_uniprocessor_scheduling .
    ```

2. Run the Docker container:
    ```sh
    docker run -it cpu_uniprocessor_scheduling
    ```

## Running the Project

The project reads input from standard input. The input format is as follows:

1. Output type (`stats` or `trace`)
2. List of algorithms (comma-separated)
3. End time
4. Number of processes
5. Process details (one per line, format: `name,arrival_time,service_time`)

Example input:
```
stats
1,2-3,3
100
3
A,0,10
B,2,5
C,4,7
```
# Code Path Mortality Tracker

## Overview
The Code Path Mortality Tracker is a simple C-based simulation program designed to analyze software reliability by tracking the execution outcomes of different code paths.

It records how many times a path executes and how many failures occur, then calculates the mortality rate of that path.

This concept can help developers understand which parts of a system are more prone to failure.

## Features
- Track execution of different code paths
- Count successful and failed executions
- Calculate mortality rate
- Log events to a log file
- Simple reliability simulation

## Technologies Used
- C Programming Language
- Standard C Libraries
- File Logging

## How It Works

1. Two code paths are defined:
   - Authentication Path
   - Transaction Path

2. Each execution is simulated using the `simulatePath()` function.

3. If the path fails, the failure counter increases and the event is logged.

4. The system calculates a mortality rate using the formula:

Mortality Rate = (Failures / Executions) * 100

5. Statistics are printed for each path.

## Example Output
Path: Authentication Path
Executions: 2
Failures: 1
Mortality Rate: 50.00%

Path: Transaction Path
Executions: 2
Failures: 0
Mortality Rate: 0.00%
## Learning Purpose
This project demonstrates:
- Basic data structures in C
- File handling
- Logging mechanisms
- Simple reliability analysis concepts

## Author
Jisan

Elevator Simulation (C++)
A multi-file object-oriented C++ simulation of a building elevator system, developed as a final project for a Computer Science course. Models real elevator behavior including passenger arrivals, boarding, disembarking, door timing, and multi-elevator coordination across multiple floors.

Overview
The simulation runs on a time-step loop where each tick represents one second. Riders arrive randomly on floors using a Poisson distribution to approximate real-world arrival rates. Three elevators serve five floors, each independently deciding whether to open doors, board riders, wait, or move — based on a priority-ordered action system.

Features

Multi-elevator coordination across 5 floors
Poisson distribution for realistic random rider arrivals
Priority-based action system per elevator per time step:

Open door to disembark a rider
Disembark rider at destination floor
Board a waiting rider
Wait for additional riders (countdown timer)
Close door and move


Elevator panel button system (lit/unlit per floor)
Direction state machine (IDLE / UP / DOWN)
Per-floor up/down rider queues
Capacity limits and door timer logic
Console output displaying elevator and floor state each time step


Concepts Demonstrated

Object-oriented design with multiple cooperating classes
Operator overloading (<<, int(), =)
STL containers: std::vector, std::queue
Static class members and constants
Header guards and .h / .cpp file separation
Poisson distribution using exp() and rand()
State machine logic for elevator behavior


Project Structure
elevator-simulation/
├── ElevatorV5.cpp    # Main entry point and simulation loop
├── Building.h/.cpp   # Manages floors, elevators, and per-tick actions
├── Elevator.h/.cpp   # Elevator state, movement, boarding, door logic
├── Floor.h/.cpp      # Floor state, rider queues, panel buttons
├── Panel.h/.cpp      # Button panel (lit/unlit) for elevators and floors
├── Rider.h/.cpp      # Rider data (origin, destination, direction)

How to Run
Online (easiest)
Paste all .cpp files into onlinegdb.com, set language to C++, and hit Run. Make sure all files are added as separate tabs.
Local (requires g++)
bashg++ -o elevator ElevatorV5.cpp Building.cpp Elevator.cpp Floor.cpp Panel.cpp Rider.cpp
./elevator
Press Enter to advance each time step.

Sample Output
-----------------------------------------------
-- Time 0 ---------------------------
Elevator at     0"       IDLE  0 riders
Elevator at     0"       IDLE  0 riders
Elevator at     0"       IDLE  0 riders
   1      First Floor at     0" Up/Down:   2/0    Button: [Up]
   2     Second Floor at   100" Up/Down:   0/1    Button: [Down]

Notes

Arrival rate is configurable via myArrivalRate in ElevatorV5.cpp (default: 1 rider/second)
After 300 time steps, new arrivals stop and the simulation drains remaining riders
Developed incrementally across multiple lab assignments, each adding a new layer of functionality

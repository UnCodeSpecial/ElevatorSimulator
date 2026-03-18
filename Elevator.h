#ifndef Elevator_h
#define Elevator_h

#include "Rider.h"
#include "Floor.h"
#include "Panel.h"
#include "Building.h"

#include <vector>
using namespace std;


class Elevator
{
  static const int IDLE = 0; 
  static const int UP = 1;
  static const int DOWN = -1;
  

  // elevator metrics
  int location; // inches above ground level
  int direction; // equal to IDLE, UP, DOWN
  int atFloorIndex;
  int timer;

  vector<Rider> riders;
  
  public:
  Elevator(unsigned int, int, int);
  operator int() const {return location;}

  Panel panel;
  
  const int speed; // inches per second, up or down
  const unsigned int CAPACITY; 

  // count-down timer before closing door
  void resetTimer() {timer = 3;}
  void tickTimer() {timer--;}
  bool timedOut() const {return timer == 0;}
  
  bool isOpen() const {return atFloorIndex >= 0;}
  void openDoorTo(int);
  void board(const Rider&);
  
  bool hasRiderForFloor() const;
  void removeRider();
  bool isFull() const {return CAPACITY == riders.size();}
  bool goingUp() const {return direction == UP;}
  bool goingDown() const {return direction == DOWN;}
  int getFloorIndex() const {return atFloorIndex;}
  unsigned int getNumberOfRiders() const {return riders.size();}
  bool isIdle() const { return direction == 0 ? true : false;}
  bool closeDoor();
  bool move();
  void goIdle() {direction = IDLE; closeDoor();}
  void setDirectionUp() {direction = UP;}
  void setDirectionDown() {direction = DOWN;}
  


 
  // friend function
  friend ostream& operator<<(ostream&, const Elevator&); 
};

#endif
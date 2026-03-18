#include "Building.h"
#include "Elevator.h"
#include "Panel.h"
#include "Rider.h"

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include <cstdlib>

//constructor
Elevator::Elevator(unsigned int capacity, int speed, int start)
: speed(speed), CAPACITY(capacity), location(Building::floors[start])
{
  start = Building::floors[start];
  direction = IDLE;
  atFloorIndex = -1;
  timer = 0;

  for(int i = 0; i < Building::FLOORS; i++)
  {
    panel.addButton(Building::floors[i].label);
  }
}

//friend function
ostream& operator<<(ostream& out, const Elevator& lift) 
{
  out << "Elevator at ";
  out << right << setw(5) << lift.location << " ";
  
  
  if (lift.direction == Elevator::IDLE) out << right << setw(10) << "IDLE";
  
  else if (lift.direction == Elevator::UP) out << right << setw(10) << "going UP";
  
  else if (lift.direction == Elevator::DOWN) out << right << setw(10) << "going DOWN";
  
  
  out << right << setw(3) << lift.riders.size();
  out << " riders ";
  
  if (lift.isOpen()) out << right << setw(15) << "door is OPEN|" << lift.timer;
  
  else out << right << setw(15) << " ";
  
  out << " " << lift.panel;

  return out;
}


void Elevator::openDoorTo(int floorindex)
{
  this->panel.clear(Building::floors[floorindex].label);
  this->atFloorIndex = floorindex;
  this->resetTimer();
}


void Elevator::board(const Rider& rider)
{
  this->riders.push_back(rider); // add rider

  this->panel.press(Building::floors[rider.to].label); 
  // set direction of elevator
  if(rider.goingUp) this->direction = this->UP;
  
  else if(rider.goingDown) this->direction = this->DOWN;
  
  else throw "BOARD ERROR!";

  this->resetTimer(); // reset close door timer
}

bool Elevator::hasRiderForFloor() const
{//return true is rider is at floor
  if(atFloorIndex == -1) 
    return false;

  for(int i = 0; i < riders.size(); i++)
    if(riders[i].to == atFloorIndex)
      return true; 

  return false; 
}

void Elevator::removeRider()
{
  vector<Rider>:: iterator all;
  for(all = riders.begin(); all != riders.end(); all++)
  {
    if(all->to == atFloorIndex)
    {    this->panel.clear(Building::floors[all->to].label);
      all = this->riders.erase(all);
      this->resetTimer();
      break;
    }
  }
}

bool Elevator::closeDoor()
{
  if(atFloorIndex == -1) return false;
  else
  {
    if(this->goingUp() && !Building::floors[atFloorIndex].hasUpRider())
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].UP);
    else if(this->goingDown() && !Building::floors[atFloorIndex].hasDownRider())
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].DOWN);
  }
  this->atFloorIndex = -1;
  return true;
}

bool Elevator::move()
{
  if(this->direction == this->UP)
  {
    for(int i = 0; i < Building::FLOORS; i++)
    {
      if(Building::floors[i].elevation < this->location || Building::floors[i].elevation > this->location + speed) continue;
      else if((Building::floors[i].panel.isLit(Floor::UP) || Building::floors[i].panel.isLit(Building::floors[i].label)) && this->location != Building::floors[i].elevation)
      {
        this->location = Building::floors[i].elevation;
        this->openDoorTo(i);
        return true;
      }
    } 

    if(Building::floors[Building::FLOORS - 1].elevation <= this->location + speed)
    {
      this->location = Building::floors[Building::FLOORS - 1].elevation;
      this->atFloorIndex = Building::FLOORS - 1;
      return false;
    }
    else
    {
      this->location += speed;
      return true;
    }
  }
  else if(this->direction == this->DOWN)
  {
    for(int i = 0; i < Building::FLOORS; i++)
    {
      if(Building::floors[i].elevation > this->location || Building::floors[i].elevation < this->location - speed) continue;
      else if((Building::floors[i].panel.isLit(Floor::DOWN) || Building::floors[i].panel.isLit((Building::floors[i].label))) && this->location != Building::floors[i].elevation)
      {
        this->location = Building::floors[i].elevation;
        this->openDoorTo(i);
        return true;
      }
    }
    
    if(Building::floors[0].elevation >= this->location - speed)
    {
      this->location = Building::floors[0].elevation;
      this->atFloorIndex = 0;
      return false;
    }
    else
    {
      this->location -= speed;
      return true;
    }
  }
  return false;
}
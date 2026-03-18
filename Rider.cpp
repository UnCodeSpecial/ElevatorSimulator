#include "Rider.h"
#include "Building.h"

//rider constructor 
Rider::Rider(int from, int to)
:from(from), to(to), goingUp(Building::floors[to] > Building::floors[from] ? true : false), goingDown(Building::floors[to] < Building::floors[from] ? true : false)
{}

//assignment operator
Rider& Rider::operator=(const Rider& original)
{
  if (this != &original) 
  {
    const_cast<int&>(this->from) = original.from; 
    const_cast<int&>(this->to) = original.to;
    const_cast<bool&>(this->goingUp) = original.goingUp;
    const_cast<bool&>(this->goingDown) = original.goingDown;
  }

  return *this; 
}
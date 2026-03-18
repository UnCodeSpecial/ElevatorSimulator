#include "Floor.h"
#include "Rider.h"
#include "Panel.h"
#include "Building.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <climits>

const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits

//constructor
Floor::Floor(const int elevation, const char* name, const char* label) 
:name(name), label(label), elevation(elevation)
{
  panel.addButton(UP);
  panel.addButton(DOWN);

  if (TOP < elevation) TOP = elevation;
  if (elevation < BOTTOM) BOTTOM = elevation;
}

//friend function
ostream& operator<<(ostream& out, const Floor& floor)
{
  out << right << setw(4) << floor.label;
  out << right << setw(15) << floor.name << " at ";
  out << right << setw(5) << floor.elevation << "\" Up/Down:";
  out << right << setw(4) << floor.upRiders.size() << "/" << floor.downRiders.size() << "    Button:  " << floor.panel;

  return out;
}

//getter
void Floor::addRider(const Rider& rider)
{
  if(rider.goingUp)
  {
    this->upRiders.push(rider);
    panel.press(UP);
  }
  else if(rider.goingDown)
  {
    this->downRiders.push(rider);
    panel.press(DOWN);
  }
}


Rider Floor::removeUpRider()
{
  // create copy and remove rider from the queue
  if (this->upRiders.empty()) throw "**ERROR** UP_RIDER EMPTY!";     
  Rider localRider = this->upRiders.front();        
  this->upRiders.pop();        
  return localRider;
}

Rider Floor::removeDownRider()
{
  // create copy and remove rider from the queue
  if (this->downRiders.empty()) throw "**ERROR** DOWN_RIDER EMPTY!";
  Rider localRider = this->downRiders.front();
  this->downRiders.pop();      
  return localRider;
}
#include "Panel.h"

#include <iostream>
#include <string>
using namespace std;

int Panel::Button::count = 0;

//getter
void Panel::addButton(string label)
{
  Button tempB;
  tempB.label = label;
  tempB.lit = false;
  tempB.sequence = Button::count;
  buttons.push_back(tempB);
  Button::count = buttons.size();
}

//getter
string Panel::getFirstLit() const
{
  Button first;
  first.sequence = Button::count;

  for (Button button : buttons)
  {
    if (button.lit && button.sequence < first.sequence) first = button;    
  }
  return first.label;
}


void Panel::press(string label)
{
  for (unsigned int i = 0; i < buttons.size(); ++i)
  {
    if (buttons[i].label == label)
    {
      buttons[i].lit = true;
      return;
    }
  }
}


void Panel::clear(string label)
{
  for (unsigned int i = 0; i < buttons.size(); ++i)
  {
    if (buttons[i].label == label)
    {
      buttons[i].lit = false;
      return;
    }
  }
}


bool Panel::isLit(string label) const
{
  for (Button newB : buttons)
  {
    if (newB.label == label)
    {
      return newB.lit;
    }
  }
  return false;
}

bool Panel::areAnyLit() const
{
  for (Button newB : buttons)
  {
    if (newB.lit)
    {
      return true;
    }
  }
  return false;
}

//friend function
ostream& operator<<(ostream& out, const Panel& panel)
{
  for (Panel::Button newB : panel.buttons)
  {
    if (newB.lit)
    {
      out << "[" << newB.label << "]";
    }
  }
  return out;
}
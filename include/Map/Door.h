#pragma once
#include <string>
#include "../Structures/Vector.hpp"
using std::string;

class Door {
  private:
    short ID;

  public:
    bool locked;
    Vector<string> story;
    
    Door(short p_ID, string p_s, bool p_l) : 
      ID(p_ID), locked(p_l) {story.push_back(p_s);}


    short getID(){
      return ID;
    }
};
#pragma once
#include "Map/Room.h"
#include "Structures/List.hpp"
#include <iostream>

using std::string;

class Player {
  private:
    
  public:
    short HP;
    short maxHP;

    short baseDMG;
    short extraDMG;

    short baseDEF;
    short extraDEF;

    Vector<gameObject*>* inventory; 
    string Name;

    short potions = 0;
    short treasures = 0;
    short maps = 0;
    bool chessPiece = false; 
 
    Room* actualRoom;
    Room* previousRoom;

    Vector<string> text;

    Player(string n, short h, short d, short a) : Name(n), HP(h), baseDEF(d), baseDMG(a) {
      inventory = new Vector<gameObject*>();
      maxHP = h;
    }
    void line(string s);
    void drawText(Vector<string> s);
    
    Vector<string>& pikupItem(gameObject* item);
    void swapItem(gameObject* itemActual, gameObject* itemNew);
    Vector<string> fight();
    Vector<string>& showInventory();
    short getDMG();
    short getDEF();
    string getName();

};
#pragma once
#include <string>
#include <iostream>
#include "../Structures/Vector.hpp"
#include "Door.h"
#include "../GameObjects/Item.h"
#include "../Enemies/Enemy.h"

using std::string; 



class Room {
  private:

  public:
    short ID;
    Vector<string> story;
    Vector<Enemy*>* enemies;
    Vector<Door*>* doors;
    Vector<gameObject*>* items;
    bool teleporter = false;
    bool teleActive = false;
    Vector<string> text;

    Room(short p_ID, Vector<Door*>* p_D) : ID(p_ID), doors(p_D) {
      items = new Vector<gameObject*>(1);
      enemies = new Vector<Enemy*>(1);
    }

    void addEnemy(Enemy* ene);
    void addItem(gameObject* i);
    Vector<string>& describeRoom();

    void doorStory();
    void itemStory();
    void enemyStory();

    short getID(){
      return ID;
    }  
};

 

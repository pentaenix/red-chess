#pragma once
#include <string>
#include "../Structures/Vector.hpp"

using std::string;
enum objectType {KEY, WEAPON, SHIELD, POTION, TREASURE, MAP,PIECE };


class gameObject {
  private:
    short ID;
    objectType Type;
  public:
    Vector<string> story;

    gameObject(short p_Id, string p_S, objectType p_Ty) : 
      ID(p_Id), Type (p_Ty) {story.push_back(p_S);}
    
    short getID(){
      return ID;
    }

    objectType getType(){
      return Type;
    }

    string getName(){
      if(Type == KEY) return "key";
      if(Type == WEAPON) return "weapon";
      if(Type == SHIELD) return "shield";
      if(Type == POTION) return "potion";
      if(Type == MAP) return "map";
      if(Type == TREASURE) return "treasure";
      if(Type == PIECE) return "chess_piece";
    }
};


// (è_é)
class Weapon : gameObject {
  private:
    short power;
  public:

    Weapon(string p_S, short p_P) : gameObject(0, p_S, WEAPON) {
      power = p_P;
    }

    short getPower(){
      return power;
    }
};

class Shield : gameObject {
  private:
    short defence;
  public:

    Shield(string p_S, short p_D) : gameObject(0, p_S, SHIELD) {
      defence = p_D;
    }

    short getDefence(){
      return defence;
    }
};

class Potion : gameObject {
  private:
  public:
    Potion(string p_S) : gameObject(0, p_S, POTION) {
    }
};

class Key : gameObject {
  private:
    short ID; 
  public:
    Key(short p_ID, string p_S) : gameObject(p_ID, p_S, KEY) {
      ID = p_ID;
    }
    short getID(){// ?
      return ID;
    }
};

class Treasure : gameObject {
  private:
  public:
    Treasure(string p_S) : gameObject(0, p_S, TREASURE) {
    }
};

class Piece : gameObject {
  private:
  public:
    Piece(string p_S) : gameObject(0, p_S, PIECE) {
    }
};

class Map : gameObject {
  private:
  public:
    Map(string p_S) : gameObject(0, p_S, MAP) {
    }
};

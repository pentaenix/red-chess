#pragma once

enum EnemyType { PAWN, KNIGHT, ROOK, BISHOP, QUEEN, KING };

#include "../GameObjects/Item.h"
#include "../Structures/Vector.hpp"
#include <string>

using std::string;

class Enemy {
private:
  EnemyType Type;

public:
  short atk;
  short defence;
  short maxHP;
  short HP;
  Vector<string> story;

  Enemy(string s, short pow, short def, short hp, EnemyType enemyT)
      : atk(pow), defence(def), HP(hp), Type(enemyT) {
    story.push_back(s);
    maxHP = hp;
  }

  EnemyType getType() { return Type; }
  string getName() {
    if (Type == PAWN)
      return "pawn";
    if (Type == KNIGHT)
      return "knight";
    if (Type == ROOK)
      return "rook";
    if (Type == BISHOP)
      return "bishop";
    if (Type == QUEEN)
      return "queen";
    if (Type == KING)
      return "king";
  }

  void addStory(string s) { story.push_back(s); }
};

class Pawn : Enemy {
public:
  Pawn(string p_s) : Enemy(p_s, 2, 0, 3, PAWN) {}
};

class Knight : Enemy {
public:
  Knight(string p_s) : Enemy(p_s, 3, 1, 5, KNIGHT) {}
};

class Rook : Enemy {
public:
  Rook(string p_s) : Enemy(p_s, 5, 3, 6, ROOK) {}
};

class Bishop : Enemy {
public:
  Bishop(string p_s) : Enemy(p_s, 9, 7, 7, BISHOP) {}
};

class Queen : Enemy {
public:
  Queen(string p_s) : Enemy(p_s, 16, 16, 8, QUEEN) {}
};

class King : Enemy {
public:
  King(string p_s) : Enemy(p_s, 1, 1, 1, KING) {}
};
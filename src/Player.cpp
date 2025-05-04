#include <cmath>
#include "../include/Player.h"


using std::cout;
using std::cin;
using std::to_string;
using std::string;

void Player::line(string s){
  s = " "+s;
  while(s.length() < 37){
    s+=" ";
  }
  cout<<"       " << u8"\u2551" << s <<  u8"\u2551\n";
}

void Player::drawText(Vector<string> s){
  cout<<"       " <<u8"\u2554";
  for(int i = 0; i < 37; i++) 
    cout<<u8"\u2550";
  cout<<u8"\u2557\n"; 
  
  for(int i = 0; i <  s.size();i++){
    line(s[i]);
  }

  cout<<"       " <<u8"\u255A";
  for(int i = 0; i < 37; i++) 
    cout<<u8"\u2550";
  cout<<u8"\u255D\n"; 
}

Vector<string>& Player::pikupItem(gameObject* item) {
  text.clear();
  text.push_back("You take the "+item->getName());
  
  switch(item->getType()) {
    case KEY: {
      inventory->push_back(item);
      break;
    }
    case WEAPON: {
      bool skip = false;
      for(int i = 0; i < inventory->size(); ++i){
        if(inventory->at(i)->getType() == WEAPON){
          swapItem(inventory->at(i), item);
          extraDMG = ((Weapon*)item)->getPower();
          skip = true;
          break;
        }
      }
      if(!skip){
        extraDMG = ((Weapon*)item)->getPower();
        inventory->push_back(item);
        actualRoom->items->erase(item);
      }
      break;
    }
    case SHIELD: {
      bool skip = false;
      for(int i = 0; i < inventory->size(); ++i){
        if(inventory->at(i)->getType() == SHIELD){
          swapItem(inventory->at(i), item);
          extraDEF = ((Shield*)item)->getDefence();
          skip = true;
          break;
        }  
      }
      if(!skip){
        extraDEF = ((Shield*)item)->getDefence();
        inventory->push_back(item);
        actualRoom->items->erase(item);
      }
      break;
    }
    case POTION: {
      potions++;
      break;
    }
    case TREASURE: {
      treasures++;
      break;
    }
    case MAP: {
      maps++;
      break;
    }
    case PIECE:{
      chessPiece = true;
      break;
    }
    default: {
      break;
    }
  }
  return text;
}

void Player::swapItem(gameObject* itemActual, gameObject* itemNew) {
  string input = "";
  if(itemNew->getType() == WEAPON) {
    text.push_back("your weapon deals: " + to_string(((Weapon*)itemActual)->getPower()));
    text.push_back("this one in the floor deals:  " + to_string(((Weapon*)itemNew)->getPower()));
    text.push_back("Will you take it? (Y/N)");
  } else {
    text.push_back("your shields protects: " + to_string(((Shield*)itemActual)->getDefence()));
    text.push_back("this one in the floor protects:  " + to_string(((Shield*)itemNew)->getDefence()));
    text.push_back("Will you take it? (Y/N)");
  }
  drawText(text);
    std::cin.get();
    std::cin >> input;
  if(input == "Y" || input == "y"){
      inventory->push_back(itemNew);
      actualRoom->items->erase(itemNew);
      actualRoom->addItem(itemActual);
      inventory->erase(itemActual);
      text.clear();
      text.push_back("You swapped your gear");
      text.push_back("");
      text.push_back("What will you do?");
  }
}

string Player::getName(){
  return Name;
}

short Player::getDMG(){
  return baseDMG;
}

short Player::getDEF(){
  return baseDEF;
}

Vector<string>& Player::showInventory() {
  text.clear();
  text.push_back("-------------Inventory-------------");
  if(chessPiece){
    text.push_back("You have a small chess piece");
    text.push_back("it looks very important");
    text.push_back("");
  }
  for (int j = 0; j < inventory->size(); j++) {
      switch (inventory->at(j)->getType()) {
      case KEY: {
          for(int i = 0; i < inventory->at(j)->story.size(); i++)
            text.push_back(inventory->at(j)->story[i]);
          text.push_back("It has the number: "+to_string(((Key*)inventory->at(j))->getID()));
          text.push_back("");
          break;
        }
        case WEAPON: {
          for(int i = 0; i < inventory->at(j)->story.size(); i++)
            text.push_back(""+inventory->at(j)->story[i]);
          text.push_back("It has a strength of "+to_string(((Weapon*)inventory->at(j))->getPower()));
          text.push_back("");
          break;
   
        }
        case SHIELD: {
          for(int i = 0; i < inventory->at(j)->story.size(); i++)
            text.push_back(inventory->at(j)->story[i]);
          text.push_back("It has a defence of "+to_string(((Shield*)inventory->at(j))->getDefence()));
          text.push_back("");
          break;
        }
        default: {
          break;
        }
      }
    }
    if(potions > 0){
      if (potions == 1) {
        text.push_back("you have one potion");
        text.push_back("It will fill your HP or increase");
        text.push_back("it if its full");
      }else{
        text.push_back("you have "+to_string(potions)+" potions");
        text.push_back("they will fill your HP or");
        text.push_back("increase it if its full");
      }
      text.push_back("");
    }
    if(treasures > 0){
      if (treasures == 1) {
        text.push_back("you have one treasure, it could sell");
        text.push_back("for a lot of money if you escape");
      }else{
        text.push_back("you have "+to_string(treasures)+" treasures");
        text.push_back("they they could sell for a lot of");
        text.push_back("money if you escape");
      }
      text.push_back("");
  }
  text.push_back("-----------------------------------");
  return text;
}







  
#include "../include/Map/Room.h"
using std::cout;
using std::string;
using std::to_string;

void Room::addEnemy(Enemy* ene){
  if(!enemies){
    enemies = new Vector<Enemy*>(1);
  }
  enemies->push_back(ene);
}

void Room::addItem(gameObject* i){
  if(!items){
    items = new Vector<gameObject*>(1);
  }
  items->push_back(i);
}


Vector<string>& Room::describeRoom() {
  text.clear();
  text.push_back("Room: "+ to_string(ID));
  

  for(int i = 0; i < story.size(); i++){
    text.push_back(story[i]);
  }
  text.push_back("");
  if (doors->size() > 0) {
    if(doors->size() == 1){
      text.push_back("There is one door");
    } else{
      text.push_back("There are " + std::to_string(doors->size()) + " doors");
    }
    
    doorStory();
  }

  if (items) {
    itemStory();
  }

  if(enemies) {
    enemyStory();
  }

  if(teleporter){
    text.push_back("");
    text.push_back("There seems to be a strange");
    text.push_back("magic circle, it might allow");
    text.push_back("you to travel to other rooms");
    text.push_back("with the same circle");
  }

  return text;
}



void Room::doorStory(){
  for(size_t i = 0; i < doors->size(); i++) {
    Door* tmp = doors->at(i);
    text.push_back("Door: "+to_string(tmp->getID()));
    for(int i = 0; i < tmp->story.size(); i++){
      text.push_back(tmp->story[i]);
    }
  }
}
  
void Room::itemStory() {
  if(!items->size()) return;
  text.push_back("");
  if(items->size() == 1) text.push_back("there is one item");
  else text.push_back("there are " + to_string(items->size()) + " items");
  for(size_t i = 0; i < items->size(); ++i) {
    gameObject* tmp = items->at(i);
      
    switch(tmp->getType()) {
      case KEY: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(tmp->story[i]);
        text.push_back("with the number "+ to_string(((Key*)tmp)->getID()) +" written on it");
        break;
      }
      case WEAPON: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(tmp->story[i]);
        text.push_back("It has a strength of "+to_string(((Weapon*)tmp)->getPower()));
        break;
 
      }
      case SHIELD: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(""+tmp->story[i]);
        text.push_back("It has a defence of "+to_string(((Shield*)tmp)->getDefence()));
        break;
      }
      case POTION: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(""+tmp->story[i]);
        text.push_back("It restores your HP and if its full");
        text.push_back("you gain one extra heart");
        break;
      }
      case TREASURE: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(""+tmp->story[i]);
        text.push_back("That you could sell later");
        break;
      }
      
      case MAP: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(""+tmp->story[i]);
        text.push_back("a map fragment, getting all 4");
        text.push_back("might help you explore");
        break;
      }
      case PIECE: {
        for(int i = 0; i < tmp->story.size(); i++)
          text.push_back(""+tmp->story[i]);
        text.push_back("It looks really important");
        break;
      }
    }
  }
}

void Room::enemyStory() {
  if(!enemies->size()) return;
  text.push_back("");
  if(enemies->size() == 1) text.push_back("there is one enemy");
  else text.push_back("there are " + to_string(enemies->size()) + " enemies");
  
  for(size_t i = 0; i < enemies->size(); i++) {
    Enemy* tmp = enemies->at(i);
    for(int i = 0; i < tmp->story.size(); i++){
      text.push_back(tmp->story[i]);
    }
    text.push_back("");
  }
}


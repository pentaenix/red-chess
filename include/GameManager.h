#pragma once
#include "UI/Defines.h"
#include "UI/Colormod.h"
#include "UI/textBox.h"
#include "Player.h"
#include <iostream>


using std::cout;
using std::endl;
using std::string;


static textBox text;
short length = 37;
Player* player;
int health = 5;
string name;

//-------------------

Color::Modifier red(Color::FG_RED);
Color::Modifier blu(Color::FG_BLUE);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);

#define s_cnt cout<<"    ";
//10


void line(string s){
  s = " "+s;
  while(s.length()<length){
    s+=" ";
  }
  b4 cout<<s; b5
}



void inventoryUpdate(int i){
  short inv[9] = {0,0,0,0,0,0,0,0,0};
  short keys = 0;
  short invSize = player->inventory->size();
  for(int j = 0; j < invSize; j++){
    if(player->inventory->at(j)->getType()==WEAPON) inv[0]=1;
    if(player->inventory->at(j)->getType()==SHIELD) inv[1]=1;
    if(player->inventory->at(j)->getType()==KEY) keys++;
  }
    if(player->potions > 0) inv[3]=1;
    if(player->potions > 1) inv[4]=1;
    if(player->potions > 2) inv[5]=1;

    if(keys > 2) inv[6]=1;
    if(keys > 1) inv[7]=1;
    if(keys > 0) inv[8]=1;
    if(player->chessPiece)inv[2]=1;
  
  if(i==0 && inv[i]) sw
  else if(i==1 && inv[i]) sh
  else if(i==2 && inv[i]) chess
  else if(i==3 && inv[i]) sp
  else if(i==4 && inv[i]) sp
  else if(i==5 && inv[i]) sp
  else if(i==6 && inv[i]) sk
  else if(i==7 && inv[i]) sk
  else if(i==8 && inv[i]) sk
  else cout<<"   ";
}

void drawText(){
  Vector<string> s = text.text;
  top
  for(int i = 0; i <  s.size();i++){
    line(s[i]);
  }
  bottom
}


void drawHP(){
  cnt
  for(int i = 0; i < player->maxHP; i++){
    if(i < player->HP) hpf
    else hpe
  }
  cout<<endl;
}

void upWall(int i){
  if (player->actualRoom->doors->size() > 1 && ((i == (length-7)/2) || i == ((length-7)/2)-1)) {//3
    if(i == ((length-7)/2)-1){
      if (player->actualRoom->doors->at(1)->locked){
        drc
      } else{
        dro
      }
    }else
      cout<< " ";
  } else{
    midline
  }
}

void downWall(int i){
  if (player->actualRoom->doors->size() > 0 && ((i == (length-7)/2) || i == ((length-7)/2)-1)) {//4
    if(i == ((length-7)/2)-1){
      if (player->actualRoom->doors->at(0)->locked){
        drc
      } else{
        dro
      }
    }else
      cout<< " ";
  } else{
    midline
  }
}


void leftWall(int i){
  if (player->actualRoom->doors->size() > 2 && i == 4) {
    s_cnt
    if (player->actualRoom->doors->at(2)->locked){
      drc
    } else{
      dro
    }
    cout<< " ";
  }
  else {
    b4
  }
}

void rightWall(int i){
  if (player->actualRoom->doors->size() > 3 && i == 4){//2
    if(player->actualRoom->doors->at(3)->locked){
      drc
    }else{
      dro
    }
  }else{
    b4e
  }
}

//7,1
//4,4
//10,4
//7,3
void setEnemy(int i){
  if(player->actualRoom->enemies->at(i)->getType()==PAWN) e1
  if(player->actualRoom->enemies->at(i)->getType()==KNIGHT) e2
  if(player->actualRoom->enemies->at(i)->getType()==ROOK) e3
  if(player->actualRoom->enemies->at(i)->getType()==BISHOP) e4
  if(player->actualRoom->enemies->at(i)->getType()==QUEEN) e5
  if(player->actualRoom->enemies->at(i)->getType()==KING) e6
}


void setItem(int i){
  if(player->actualRoom->items->at(i)->getType()==KEY) key
  else if(player->actualRoom->items->at(i)->getType()==WEAPON) fsw
  else if(player->actualRoom->items->at(i)->getType()==SHIELD) fsh
  else if(player->actualRoom->items->at(i)->getType()==POTION) fsp
  else if(player->actualRoom->items->at(i)->getType()==MAP) mp
  else if(player->actualRoom->items->at(i)->getType()==PIECE) fch
  else itm
}

void drawMapAndInventory(){
  b1 for(int i = 0; i<length-7; i++){
    upWall(i); 
  }b3e 
  
  cout<<"  "; b1e mid3 b3//inventory top
  int a,b,c,d;
  if(player->actualRoom->getID()%2==0){
    a = 0;
    b = 1;
    c = 2;
    d = 3;
  }else{
    a = 2;
    b = 3;
    c = 0;
    d = 1;
  }
  for(int j = 0; j < 9; j++){
    leftWall(j); //wall L
      for(int i = 0; i<(length-7)/2; i++) 
      
      if (i == 7 && j == 1 && player->actualRoom->enemies->size()>0) setEnemy(0);
      else if (i == 4 && j == 4 && player->actualRoom->enemies->size()>1) setEnemy(1);
      else if (i == 10 && j == 4 && player->actualRoom->enemies->size()>2) setEnemy(2);
      else if (i == 7 && j == 3 && player->actualRoom->enemies->size()>3) setEnemy(3); 
        
      else if (i==1 && j == 1 && player->actualRoom->items->size()>a) setItem(a);
      else if (i==13 && j == 1 && player->actualRoom->items->size()>b) setItem(b);
      else if (i==1 && j == 7 && player->actualRoom->items->size()>c) setItem(c);
      else if (i==13 && j == 7 && player->actualRoom->items->size()>d) setItem(d);

      else if (i==7 && j ==5 && player->actualRoom->teleporter) tele
        
      else if(i==7&&j==7 )p1 //player
      else(((i+j)%2==0) ? f2 : f1); //floor  
     rightWall(j);//wall R 
      cout<<"  "; b4e inventoryUpdate(j); b5
  }
    
  b6 for(int i = 0; i<length-7; i++){
    downWall(i); 
  }b7e 
  
  cout<<"  "; b6e mid3 b7//inventory down
}


void drawMap(){
  system("clear");
  
  cout<<"          ";b1 for(int i = 0; i< 17; i++) midline b3
  //Draw Map
  if1 e e l3 l1 l1 l1 l1 n11 e   el1    if2 e e e e e e e e       b5 el2
  if1 e e l2 e e e e l2 e        el1    if2 e l3 l1 l1 l1 l1 l4 e b5 el2
  if1 e e l2 e l3 l1 l1 n7 l1    el1    if2 l1 n6 l1 l1 n5 e l2 e b5 el2
  if1 e e l2 e l2 e e l2 e       el1    if2 e e e e l2 e l2 e     b5 el2
  if1 n18 l1 n17 l1 n16 e e n8 e el1    if2 e n20 e e n4 l1 l6 e  b5 el2
  if1 e e l2 e e e e l2 e        el1    if2 e l2 e e l2 e e e     b5 el2
  
  if3 e e l5 l1 n15 e e n9 l1    el1    if4 l1 n10 e e n3 l1 l1 n12  b5 el2
  if3 e e e e l2 e e e e         el1    if4 e e e e l2 e e l2        b5 el2
  if3 e e e e n14 l1 l1 n13 l1   el1    if4 l1 n1 l1 l1 n2 e e n19   b5 el2
  if3 e e e e e e e e e          el1    if4 e l2 e e e e e e         b5 el2
  if3 e e e e e e e e e          el1    if4 e cout<<"o"; e e e e e e b5 el2
  cout<<"          ";b6 for(int i = 0; i< 17; i++) midline b7
  top;
  /*for(int i = 0 ; i < player->visited.length();i++){
    line(player->visited.at(0).print());
  }*/
  line("This is the map of the castle");
  bottom;
  std::cin.get();
  std::cin.get();
}


void drawUI(){
  drawHP();
  drawMapAndInventory();
  drawText();
}

void askInput(){
  text.text.push_back("");
  text.text.push_back("What will you do?");
}

void setTextBox(Vector<string> s){
  text.text = s;
  askInput();
}

void setTextBox(string s){
  text.text.clear();
  text.text.push_back(s);
}

void addTextBox(string s){
  text.addText(s);
}

void addTextBox(Vector<string> s){
  for(int i = 0; i < s.size(); i++){
    text.addText(s[i]);
  }
}

void dialogue(string s){
  system("clear");
  text.text.push_back(s);
  drawUI();
}

void wait(){
  std::cin.ignore(10000,'\n');
  std::cin.get();
}

void intro(){
  system("clear");
  top;
//     "-----------------------------------"
  line("You are an inspiring historian who ");
  line("wants to discover what happened in ");
  line("Stalemate castle, a place where");
  line("all of its inhabitants suddenly ");
  line("disappeared");
  line("");
  line("After months of research you finally");
  line("found it, a beautiful red castle, ");
  line("Decorated with marbles statues in ");
  line("every corner.   ");
  line("");
  line("It takes you a while, but you mange");
  line("to make your way though the unkeept ");
  line("Gardens.  ");
  line("");
  line("You finally arrive, its time for");
  line("you to discover what happened to the");
  line("habitants of this marvelous place");
  bottom;
  cnt cout<<"...";
  std::cin.get();
}


void startUpMenu(){
  string input = "";
  intro();
  do{
   system("clear");
   cnt cout<<"          _____ ___________  "<<endl;
   cnt cout<<"   ";e1 cout<<"    | ___ \\  ___|  _  \\   ";e5 cout<<endl;
   cnt cout<<"         | |_/ / |__ | | | |   "<<endl;
   cnt cout<<"  ";e3 cout<<"     |    /|  __|| | | |     ";e4 cout<<endl;
   cnt cout<<"         | |\\ \\| |___| |/ /  "<<endl;
   cnt cout<<"   ";e2 cout<<"    \\_| \\_\\____/|___/     ";e6 cout<<endl;     
   cnt cout<<"   _____  _   _  _____ _____ _____ "<<endl;
   cnt cout<<"  /  __ \\| | | ||  ___/  ___/  ___|"<<endl;
   cnt cout<<"  | /  \\/| |_| || |__ \\ `--.\\ `--. "<<endl;
   cnt cout<<"  | |    |  _  ||  __| `--. \\`--. \\"<<endl;
   cnt cout<<"  | \\__/\\| | | || |___/\\__/ /\\__/ /"<<endl;
   cnt cout<<"   \\____/\\_| |_/\\____/\\____/\\____/ "<<endl<<endl;
   string txt[3] = {
//  "-----------------------------------"
    "A large door lies in front of you",
    "it seems to be unlocked type \"open\"",
    "to begin your journey"};
   text.setText(txt,3);
   drawText();
   cout<<endl; 
   std::cin >> input;
  }while(input != "open");
  
  system("clear");
  text.setText("What is your name?");
  drawText();
  std::cin >> name;
  player = new Player(name, 5, 0, 1);
  text.setText("Alright "+name);
  text.text.push_back("good luck out there.");
  drawText();
  wait();
  text.setText("What will you do?");
}
    
void help(){
  system("clear");
  top;
  line("help: displays the actions you can ");
  line("take.                              ");
  line("look: narrates the layout of the   ");
  line("room you are in.                   ");
  line("walk/move: moves to another room.  ");
  line("inventory: narrates the items in   ");
  line("your inventory.                    ");
  line("take: takes an item from the floor ");
  line("attack/fight: starts combat        ");
  line("against an enemy in the same room. ");
  line("stats: shows your current stats.   ");
  line("drink: consumes a potion.          ");
  line("map: shows the map of the castle   ");
  line("teleport: in rooms with a magic");
  line("circles, you can teleport to other");
  line("rooms with magic circles");
  line("quit: kills the game, you become a ");
  line("ghost.                           ");
  bottom;
  cnt cout<<"...";
  std::cin.get();
  std::cin.get();
}



void cry(){
  string txt[4] = {"You drop down to cry, it's kind of","patetic...","","What will you do?"};
  text.setText(txt,4);
}


void drawGameOver(){
s_cnt cout<<"                 _______\n";
s_cnt cout<<"              .-\"       \"-.\n";
s_cnt cout<<"             /             \\\n";
s_cnt cout<<" _          |               |          _\n";
s_cnt cout<<"( \\         |,  .-.   .-.  ,|         / )\n";
s_cnt cout<<" > \"=._     | )(__/   \\__)( |     _.=\" <\n";
s_cnt cout<<"(_/\"=._\"=._ |/     / \\     \\| _.=\"_.=\"\\_)\n";
s_cnt cout<<"       \"=._ (_     ^ ^     _)\"_.=\"\n";
s_cnt cout<<"           \"=\\__|IIIIIII|__/=\"\n";
s_cnt cout<<"          _.=\"| \\IIIIIII/ |\"=._\n";
s_cnt cout<<" _    _.=\"_.=\"\\           /\"=._\"=._    _\n";
s_cnt cout<<"( \\_=\"_.=\"     `---------`     \"=._\"=_/ )\n";
s_cnt cout<<" > _=\"                             \"=_ <\n";
s_cnt cout<<"(_/             GAME OVER             \\_)\n";
  
}
// Replit broke Console Interaction in their latest update, the game can no
// longer be played, feel free to download the open source repo and play it
// locally

#include "include/GameManager.h"
#include "include/Map/Room.h"
#include "include/Player.h"
#include "include/Structures/Graph.hpp"
#include "include/UI/textBox.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool runningGame, gameOver;
void start();
void update();
void mapGenerator();
void createPlayer(string s);
void changeRoom();
int getNumber(string s);
void showStats();
void drink();
void fight();
void take();
void combat();
void gameManager(string step);
void gameOverUpdate();
bool checkIfOver();
void checkTeleport();

void transfer();

Graph<Room *> worldGraph(nullptr);
Vector<Room *> rooms;
Vector<Room *> teleportable;

int main() {
  start();
  update();
}

void start() {
  cout << "...\n";
  runningGame = true;
  gameOver = false;
  startUpMenu();
  mapGenerator();
  setTextBox(player->actualRoom->describeRoom());
}

void update() {
  string input = "";
  while (runningGame) {
    if (checkIfOver())
      break;
    checkTeleport();
    system("clear");
    drawUI();
    cnt cin >> input;
    gameManager(input);
  }
  if (gameOver) {
    gameOverUpdate();
  }
}

void checkTeleport() {
  if (player->actualRoom->teleporter) {
    if (!player->actualRoom->teleActive) {
      player->actualRoom->teleActive = true;
      teleportable.push_back(player->actualRoom);
    }
  }
}

bool checkIfOver() {
  if (player->actualRoom->getID() == 21) {
    if (player->chessPiece) {
      setTextBox("You defeated the king and");
      addTextBox("the secret passage opens");
      addTextBox("as you leave, the red chess");
      addTextBox("piece you took, shines and");
      addTextBox("grows, a new statue of a king");
      addTextBox("appears, sits in the throne");
      addTextBox("and smiles saying");
      addTextBox("");
      addTextBox("you are a lucky guy, run now");
      addTextBox("I need to make some changes");
      addTextBox("around here");
      addTextBox("You escape through the secret");
      addTextBox("passage and live the rest of");
      addTextBox("your life surounded by riches");
      addTextBox("");
      addTextBox("The curse in the castle will keep ");
      addTextBox("Tormenting its inhabitants.");
      addTextBox("");
      addTextBox("Thanks for playing!");
      addTextBox("");
      addTextBox("Your score was: " +
                 std::to_string((player->treasures * 87) + 2000));
      system("clear");
      drawText();
    } else {
      setTextBox("You defeated the king but");
      addTextBox("something doesnt feel right");
      addTextBox("you tremble as you watch your");
      addTextBox("skin turn to marble, there");
      addTextBox("must always be a king");
      addTextBox("the broken queens voice");
      addTextBox("says from the other side of");
      addTextBox("the room");
      addTextBox("And you have proben to be ");
      addTextBox("worthy, welcome to your");
      addTextBox("prison, your majesty");
      addTextBox("she gives a laud laugh");
      addTextBox("you turn ino a chess piece");
      addTextBox("if only you had found");
      addTextBox("a replacement, but you didnt");
      addTextBox("and now you are cursed for");
      addTextBox("an eternity unable to leave");
      addTextBox("this room");

      addTextBox("");
      addTextBox("Thanks for playing!");
      addTextBox("");
      addTextBox("Your score was: 0");
      addTextBox("But you can always try again");
      system("clear");
      drawGameOver();
      drawText();
    }
    runningGame = false;
    return true;
  }
  return false;
}

void gameOverUpdate() {
  setTextBox("You died, your body has been turned");
  addTextBox("into a pawn, an enemy for others to");
  addTextBox("face in battle...");
  system("clear");
  drawGameOver();
  drawText();
}

void gameManager(string step) {
  if (step == "quit") {
    runningGame = false;
    gameOver = true;
  }
  if (step == "help")
    help();

  if (step == "cry")
    cry();

  if (step == "look")
    setTextBox(player->actualRoom->describeRoom());

  if (step == "walk" || step == "move")
    changeRoom();

  if (step == "inventory")
    setTextBox(player->showInventory());

  if (step == "take")
    take();

  if (step == "attack" || step == "fight")
    fight();

  if (step == "stats")
    showStats();

  if (step == "drink" || step == "consume")
    drink();

  if (step == "map") {
    drawMap();
  }

  if (step == "teleport") {
    if (player->actualRoom->teleporter) {
      transfer();
    } else {
      setTextBox("There is no magic circle in the room");
      askInput();
    }
  }

  if (step == "spare" && player->actualRoom->getID() == 20 &&
      player->actualRoom->enemies->size() > 0) {
    runningGame = false;
    if (player->chessPiece) {
      setTextBox("You give the chess piece to the");
      addTextBox("king, he looks at it for a second");
      addTextBox("smiles and rises his hand, soon");
      addTextBox("the marbel of the walls begins to");
      addTextBox("fade the destroyed marble statues");
      addTextBox("are rebuild and disapear.");
      addTextBox("");
      addTextBox("you lifted the curse");
      addTextBox("he says");
      addTextBox(" finally I can rest");
      addTextBox("All the servants in the castle");
      addTextBox("disapear and in your hand appears");
      addTextBox("a paper, its ownership of the");
      addTextBox("castle and its surrounding lands");
      addTextBox("");
      addTextBox("Thanks for playing!");
      addTextBox("");
      addTextBox("Your score was: " +
                 std::to_string((player->treasures * 87) + 8000));
      system("clear");
      drawText();
    } else {
      setTextBox("You decide to spare the life of");
      addTextBox("he king, he looks at you, tired");
      addTextBox("and says:");
      addTextBox("");
      addTextBox("Thank you, traveler, but Its");
      addTextBox("too late for me, I cant leave");
      addTextBox("this room, my own people");
      addTextBox("turned against me, I need an");
      addTextBox("artifact to break this curse");
      addTextBox("And free us from this nightmare");
      addTextBox("But you shouldnt worry about it");
      addTextBox("You did well, take this crown");
      addTextBox("make a living out there, you are");
      addTextBox("free.");
      addTextBox("");
      addTextBox("The curse in the castle will keep ");
      addTextBox("Tormenting its inhabitants.");
      addTextBox("");
      addTextBox("Thanks for playing!");
      addTextBox("");
      addTextBox("Your score was: " +
                 std::to_string((player->treasures * 87) + 3000));
      system("clear");
      drawText();
    }
  }
  if (player->maxHP <= 0) {
    runningGame = false;
    gameOver = true;
  }
}

void mapGenerator() {
  string ret = "returns to the last room";

  Room *r0 = new Room(
      0, new Vector<Door *>(
             new Door *[1] { new Door(1, "A large wooden arch", false) }, 1));

  Room *r1 =
      new Room(1, new Vector<Door *>(
                      new Door *[3] {
                        new Door(0, "Takes you to the reception", false),
                            new Door(2, "The way to the gallery", false),
                            new Door(13, "Its decorated with a hat ", false)
                      },
                      3));

  Room *r2 = new Room(2, new Vector<Door *>(
                             new Door *[2] {
                               new Door(1, "Takes you to the lobby", false),
                                   new Door(3, "A large glass door", false)
                             },
                             2));

  Room *r3 = new Room(3, new Vector<Door *>(
                             new Door *[3] {
                               new Door(2, "The way to the gallery", false),
                                   new Door(4, "A small staircase", false),
                                   new Door(12, "Its made of iron bars", true)
                             },
                             3));

  Room *r4 = new Room(4, new Vector<Door *>(
                             new Door *[3] {
                               new Door(3, "A small staircase", false),
                                   new Door(5, "Has a book drawn on it", false),
                                   new Door(6, "Its a long hallway", false)
                             },
                             3));

  Room *r5 = new Room(5, new Vector<Door *>(
                             new Door *[2] {
                               new Door(4, "A small staircase", false),
                                   new Door(6, "Its made of steel", false)
                             },
                             2));

  Room *r6 = new Room(6, new Vector<Door *>(
                             new Door *[3] {
                               new Door(4, "Its a long hallway", false),
                                   new Door(5, "Its made of steel", false),
                                   new Door(7, "A normal wooden door", false)
                             },
                             3));

  Room *r7 = new Room(7, new Vector<Door *>(
                             new Door *[4] {
                               new Door(6, "A normal wooden door", false),
                                   new Door(8, "A large hallway", false),
                                   new Door(11, "A strange wall", false),
                                   new Door(16, "Its quite small", false)
                             },
                             4));

  Room *r8 = new Room(8, new Vector<Door *>(
                             new Door *[2] {
                               new Door(7, "The way back", false),
                                   new Door(9, "A flight of stairs", false)
                             },
                             2));

  Room *r9 = new Room(9, new Vector<Door *>(
                             new Door *[2] {
                               new Door(8, "The way back", false),
                                   new Door(10, "A huge wooden door", true)
                             },
                             2));

  Room *r10 =
      new Room(10, new Vector<Door *>(
                       new Door *[2] {
                         new Door(9, "A flight of stairs", false),
                             new Door(20, "Its golden, with a crown", true)
                       },
                       2));

  Room *r11 = new Room(11, new Vector<Door *>(
                               new Door *[2] {
                                 new Door(7, "Its a secret passage", false),
                                     new Door(17, "Its a hidden door", false)
                               },
                               2));

  Room *r12 = new Room(12, new Vector<Door *>(
                               new Door *[2] {
                                 new Door(3, "Its made of iron bars", false),
                                     new Door(19, "A giant stone block", true)
                               },
                               2));

  Room *r13 = new Room(13, new Vector<Door *>(
                               new Door *[2] {
                                 new Door(1, "Takes you to the lobby", false),
                                     new Door(14, "A nice marble arch", false)
                               },
                               2));

  Room *r14 = new Room(14, new Vector<Door *>(
                               new Door *[2] {
                                 new Door(13, "To the coat room", false),
                                     new Door(15, "A heavy wooden door", true)
                               },
                               2));

  Room *r15 =
      new Room(15, new Vector<Door *>(
                       new Door *[2] {
                         new Door(14, "A heavy wooden door", false),
                             new Door(17, "The way to the pantry", false)
                       },
                       2));

  Room *r16 =
      new Room(16, new Vector<Door *>(
                       new Door *[2] {
                         new Door(7, "Its quite small", false),
                             new Door(17, "Takes you to the pantry", false)
                       },
                       2));

  Room *r17 =
      new Room(17, new Vector<Door *>(
                       new Door *[4] {
                         new Door(11, "A strange wall", false),
                             new Door(15, "Takes you to the kitchen", false),
                             new Door(16, "To the staff room", false),
                             new Door(18, "a hatch in the floor", true)
                       },
                       4));

  Room *r18 = new Room(18, new Vector<Door *>(
                               new Door *[1] { new Door(17, ret, false) }, 1));

  Room *r19 = new Room(19, new Vector<Door *>(
                               new Door *[1] { new Door(12, ret, false) }, 1));

  Room *r20 = new Room(20, new Vector<Door *>(
                               new Door *[2] {
                                 new Door(21, "a secret passage", false),
                                     new Door(10, "Its imposible to open", true)
                               },
                               2));

  Room *r21 = new Room(21, new Vector<Door *>(
                               new Door *[1] { new Door(20, ret, false) }, 1));

  r0->story.push_back("This is the reception, the floor");
  r0->story.push_back("has a checkered pattern similar to");
  r0->story.push_back("a chess board");
  r0->story.push_back("");
  r0->story.push_back("Upon entering, the door locks ");
  r0->story.push_back("behind you, the only way out is");
  r0->story.push_back("foward");

  r1->story.push_back("This is the lobby, beautiful");
  r1->story.push_back("furniture decorates evey inch of");
  r1->story.push_back("the room");

  r2->story.push_back("This is the gallery, its filled");
  r2->story.push_back("with nice paintings of royals");

  r3->story.push_back("this is the sun room, the moon");
  r3->story.push_back("light filters through the glass");
  r3->story.push_back("roof, a nice breeze comes from");
  r3->story.push_back("the garden to your right");

  r4->story.push_back("This is the courtyard, water");
  r4->story.push_back("flows from a large fountain");
  r4->story.push_back("in the middle, the stars");
  r4->story.push_back("fill your heart with courage");

  r5->story.push_back("This is the library, its filled");
  r5->story.push_back("with countless books, that");
  r5->story.push_back("range from fantasy to science");

  r6->story.push_back("This is the invention room");
  r6->story.push_back("its filled with all shorts of");
  r6->story.push_back("interesting gadgets");

  r7->story.push_back("This seems to be the main");
  r7->story.push_back("bedroom, the bed looks mighty");
  r7->story.push_back("comfortable");

  r8->story.push_back("this seems to be the guestrooms");
  r8->story.push_back("horrible sounds come from every");
  r8->story.push_back("room, better not risk it");

  r9->story.push_back("This room is made of countless");
  r9->story.push_back("stairs that seem to take you");
  r9->story.push_back("to the great hall");

  r10->story.push_back("This is the great hall");
  r10->story.push_back("its set up as if to allow");
  r10->story.push_back("the queen to fight at her");
  r11->story.push_back("best");

  r11->story.push_back("this is a hidden tresury");
  r11->story.push_back("its filled with gold coins,");
  r11->story.push_back("statues and priceless things");

  r12->story.push_back("this is a small cementery");
  r12->story.push_back("the family crypt lies ahead");
  r12->story.push_back("its kinda creepy");

  r13->story.push_back("This seems to be the coat room");
  r13->story.push_back("most of the clothes here have");
  r13->story.push_back("been eated by moths");
  r13->story.push_back("A faint cinnamon smell seems");
  r13->story.push_back("to come from the door at the");
  r13->story.push_back("left");

  r14->story.push_back("This is the dinning room");
  r14->story.push_back("the table is filled with all");
  r14->story.push_back("shorts of foods!");
  r14->story.push_back("The smell intensifies, it");
  r14->story.push_back("comes from further ahead");

  r15->story.push_back("This is the Kitchen, Rats are");
  r15->story.push_back("cooking some sort of cake!");
  r15->story.push_back("it smells delicious");

  r16->story.push_back("This is the staff room.");
  r16->story.push_back("The staff wasnt very happy");
  r16->story.push_back("to see you");

  r17->story.push_back("This is the pantry, they have");
  r17->story.push_back("fresh ingredients");

  r18->story.push_back("This is the secret wine cellar");
  r18->story.push_back("these barrels must be centuries");
  r18->story.push_back("old!");

  r19->story.push_back("This is the family cript, creepy");
  r19->story.push_back("statues have their eyes fixed in");
  r19->story.push_back("you");

  r20->story.push_back("You arrive at the thone room");
  r20->story.push_back("its filled with gold in every");
  r20->story.push_back("corner, a wonderful carpet");
  r20->story.push_back("points you to the throne its");
  r20->story.push_back("tall, made of solid gold");
  r20->story.push_back("the room is cold, and lonely");
  r20->story.push_back("moss grows on the rocks and");
  r20->story.push_back("resentment fills the air");
  r20->story.push_back("The door locks behind you");
  r20->story.push_back("theres no way back");

  r21->story.push_back("this is the way out");

  r5->addItem(((gameObject *)new Key(12, "A key made out of iron")));
  r7->addItem(((gameObject *)new Key(19, "A stone key")));
  r16->addItem(((gameObject *)new Key(18, "A tiny key")));
  r19->addItem(((gameObject *)new Key(20, "A key made out of gold")));
  r18->addItem(((gameObject *)new Key(10, "A key meant for a large door")));
  r15->addItem(((gameObject *)new Key(15, "The key to the kitchen")));

  r5->addItem(((gameObject *)new Map("A map fragment")));
  r17->addItem(((gameObject *)new Map("A map fragment")));
  r12->addItem(((gameObject *)new Map("A map fragment")));
  r9->addItem(((gameObject *)new Map("A map fragment")));

  r11->addItem(((gameObject *)new Piece("A red chess piece")));

  r1->addItem(((gameObject *)new Potion("A red potion")));
  r2->addItem(((gameObject *)new Potion("A red potion")));
  r3->addItem(((gameObject *)new Potion("A red potion")));
  r4->addItem(((gameObject *)new Potion("A red potion")));
  r6->addItem(((gameObject *)new Potion("A red potion")));
  r8->addItem(((gameObject *)new Potion("A red potion")));
  r10->addItem(((gameObject *)new Potion("A red potion")));
  r12->addItem(((gameObject *)new Potion("A red potion")));
  r15->addItem(((gameObject *)new Potion("A red potion")));
  r16->addItem(((gameObject *)new Potion("A red potion")));

  r2->addItem(((gameObject *)new Weapon("A rusty sword", 2)));
  r5->addItem(((gameObject *)new Weapon("A steel sword", 4)));
  r15->addItem(((gameObject *)new Weapon("A golden sword", 8)));
  r19->addItem(((gameObject *)new Weapon("A magic sword", 16)));

  r13->addItem(((gameObject *)new Shield("A rusty shield", 2)));
  r12->addItem(((gameObject *)new Shield("A steel shield", 4)));
  r7->addItem(((gameObject *)new Shield("A golden shield", 8)));
  r18->addItem(((gameObject *)new Shield("A magic shield", 16)));

  r1->addItem(((gameObject *)new Treasure("A nice rug")));
  r2->addItem(((gameObject *)new Treasure("A painting")));
  r3->addItem(((gameObject *)new Treasure("An exotic plant")));
  r4->addItem(((gameObject *)new Treasure("A statue")));
  r5->addItem(((gameObject *)new Treasure("A stash of expensive books")));
  r6->addItem(((gameObject *)new Treasure("A Scientific notebook")));
  r7->addItem(((gameObject *)new Treasure("A fancy ring")));
  r8->addItem(((gameObject *)new Treasure("A diary")));
  r9->addItem(((gameObject *)new Treasure("A torch")));
  r10->addItem(((gameObject *)new Treasure("The queen's dog")));
  r11->addItem(((gameObject *)new Treasure("A chest full of gold")));
  r12->addItem(((gameObject *)new Treasure("A skull")));
  r13->addItem(((gameObject *)new Treasure("Cool coat")));
  r14->addItem(((gameObject *)new Treasure("A golden chalice")));
  r15->addItem(((gameObject *)new Treasure("A cooking rat")));
  r16->addItem(((gameObject *)new Treasure("A pouch of copper coins")));
  r17->addItem(((gameObject *)new Treasure("Expensive bread")));
  r18->addItem(((gameObject *)new Treasure("Fine wine")));
  r19->addItem(((gameObject *)new Treasure("Royal bones")));
  r20->addItem(((gameObject *)new Treasure("The Crown")));

  r4->addEnemy(((Enemy *)new Knight("A knight made of marble")));
  r12->addEnemy(((Enemy *)new Knight("A knight made of marble")));

  r8->addEnemy(((Enemy *)new Rook("A Towering rook made of marble")));
  r16->addEnemy(((Enemy *)new Rook("A Towering rook made of marble")));

  r19->addEnemy(((Enemy *)new Bishop("A bishop made of marble")));
  r18->addEnemy(((Enemy *)new Bishop("A bishop made of marble")));

  r3->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r3->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r4->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r4->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r5->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r5->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r5->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r2->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r13->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r14->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));
  r14->addEnemy(((Enemy *)new Pawn("A pawn made of marble")));

  Enemy *queen = (Enemy *)new Queen("A powerfull aura fills the room");
  queen->addStory("the marble queen lies in front");
  queen->addStory("of you, her blade unsheathed");
  queen->addStory("she seems to be protecting");
  queen->addStory("something, you wont pass");
  queen->addStory("unless you defeat her");

  Enemy *king = (Enemy *)new King("A sad King sits in his throne");
  king->addStory("He looks at you, bored and");
  king->addStory("tired, his eyes plea for mercy");
  king->addStory("");
  king->addStory("Will you spare his life?");
  king->addStory("Or will you end his misery");

  r10->addEnemy(queen);
  r20->addEnemy(king);

  player->actualRoom = r0;

  worldGraph = Graph<Room *>(r0);

  r2->teleporter = true;
  r5->teleporter = true;
  r10->teleporter = true;
  r15->teleporter = true;
  r16->teleporter = true;
  r19->teleporter = true;

  worldGraph.addDoubleEdge(r0, r1);
  worldGraph.addDoubleEdge(r1, r2);
  worldGraph.addDoubleEdge(r1, r13);
  worldGraph.addDoubleEdge(r2, r3);
  worldGraph.addDoubleEdge(r3, r4);
  worldGraph.addDoubleEdge(r3, r12);
  worldGraph.addDoubleEdge(r4, r5);
  worldGraph.addDoubleEdge(r4, r6);
  worldGraph.addDoubleEdge(r5, r6);
  worldGraph.addDoubleEdge(r6, r7);
  worldGraph.addDoubleEdge(r7, r8);
  worldGraph.addDoubleEdge(r7, r11);
  worldGraph.addDoubleEdge(r7, r16);
  worldGraph.addDoubleEdge(r8, r9);
  worldGraph.addDoubleEdge(r9, r10);
  worldGraph.addDoubleEdge(r10, r20);
  worldGraph.addDoubleEdge(r11, r17);
  worldGraph.addDoubleEdge(r12, r19);
  worldGraph.addDoubleEdge(r13, r14);
  worldGraph.addDoubleEdge(r14, r15);
  worldGraph.addDoubleEdge(r15, r17);
  worldGraph.addDoubleEdge(r16, r17);
  worldGraph.addDoubleEdge(r17, r18);
  worldGraph.addDoubleEdge(r20, r21);

  rooms.push_back(r0);
  rooms.push_back(r1);
  rooms.push_back(r2);
  rooms.push_back(r3);
  rooms.push_back(r4);
  rooms.push_back(r5);
  rooms.push_back(r6);
  rooms.push_back(r7);
  rooms.push_back(r8);
  rooms.push_back(r9);
  rooms.push_back(r10);
  rooms.push_back(r11);
  rooms.push_back(r12);
  rooms.push_back(r13);
  rooms.push_back(r14);
  rooms.push_back(r15);
  rooms.push_back(r16);
  rooms.push_back(r17);
  rooms.push_back(r18);
  rooms.push_back(r19);
  rooms.push_back(r20);
  rooms.push_back(r21);
}

void take() {
  if (player->actualRoom->items) {
    if (player->actualRoom->items->size() > 0) {
      if (player->actualRoom->enemies) {
        if (player->actualRoom->enemies->size() > 0) {
          setTextBox("There are enemies in the room");
          addTextBox("you cant lower your guard");
          askInput();
          return;
        }
      }
      setTextBox("Take which item?");
      string tmp = "";
      for (int i = 0; i < player->actualRoom->items->size(); i++) {
        tmp += "[" + player->actualRoom->items->at(i)->getName() + "] ";
      }
      addTextBox(tmp);
      system("clear");
      drawUI();
      string input = "";
      cin.get();
      cin >> input;

      for (int i = 0; i < player->actualRoom->items->size(); i++) {
        gameObject *tmp_item = player->actualRoom->items->at(i);
        if (input == tmp_item->getName()) {
          setTextBox(player->pikupItem(tmp_item));
          if (tmp_item->getType() != WEAPON && tmp_item->getType() != SHIELD) {
            player->actualRoom->items->erase(tmp_item);
          }
          return;
        }
      }
      setTextBox("you couldnt find that item in the");
      addTextBox("room");
      addTextBox("");
      addTextBox("What will you do?");
      return;
    }
  }
  setTextBox("there are no items in this room");
  addTextBox("");
  addTextBox("What will you do?");
}

void fight() {
  if (player->actualRoom->enemies) {
    if (player->actualRoom->enemies->size() > 0) {
      combat();
    } else {
      Vector<string> tmp;
      tmp.push_back("There are no enemies left.");
      setTextBox(tmp);
    }
  } else {
    Vector<string> tmp;
    tmp.push_back("There are no enemies in this room.");
    setTextBox(tmp);
  }
}

void drink() {
  Vector<string> say;
  if (player->potions > 0) {
    say.push_back("You drank the potion and");
    player->potions--;
    if (player->HP != player->maxHP) {
      short tmp = (player->maxHP - player->HP);
      string modifier = (tmp == 1) ? "point" : "points";
      say.push_back("restored " + std::to_string(tmp) + " health " + modifier);
      player->HP = player->maxHP;
    } else {
      say.push_back("increased your HP by 1");
      player->maxHP++;
      player->HP = player->maxHP;
    }
  } else {
    say.push_back("You dont seem to have any potions");
  }
  setTextBox(say);
}

void showStats() {
  Vector<string> say;
  say.push_back("---------------Stats---------------");
  say.push_back("HP: ..........................  " +
                std::to_string(player->HP));
  say.push_back("DAMAGE: ......................  " +
                std::to_string(player->baseDMG + player->extraDMG));
  say.push_back("DEFENCE: .....................  " +
                std::to_string(player->baseDEF + player->extraDEF));
  say.push_back("-----------------------------------");
  setTextBox(say);
}

void changeRoom() {
  int temp = 0;
  text.text.clear();
  dialogue("Move to which room?");
  string door_num = "";
  for (int i = 0; i < player->actualRoom->doors->size(); i++) {
    door_num +=
        "[" + std::to_string(player->actualRoom->doors->at(i)->getID()) + "] ";
  }
  dialogue(door_num);
  cin >> temp;
  Room *toMove;
  Vector<Room *> *roomDoors = &worldGraph.getChildren(player->actualRoom);
  for (int i = 0; i < roomDoors->size(); i++) {
    if (roomDoors->at(i)->getID() == temp) {
      toMove = roomDoors->at(i);
    }
  }

  if (temp > 22)
    return;
  for (int i = 0; i < player->actualRoom->doors->size(); i++) {
    if (temp == player->actualRoom->doors->at(i)->getID()) {
      if (player->actualRoom->enemies && toMove != player->previousRoom) {
        if (player->actualRoom->enemies->size() > 0) {
          setTextBox("Defeat all enemies before moving on");
          askInput();
          return;
        }
      }
      if (!player->actualRoom->doors->at(i)->locked) {
        player->previousRoom = player->actualRoom;
        player->actualRoom = toMove;
        setTextBox("You moved into room " + std::to_string(temp));
        addTextBox(player->actualRoom->describeRoom());
        return;
      } else {
        setTextBox("This door is locked, check your");
        dialogue("inventory? (Y/N)");
        string input;
        cin >> input;
        if (input == "Y" || input == "y") {
          if (!player->inventory) {
            dialogue("Your Inventory is empty");
            cin.clear();
            cin.get();
            setTextBox("What will you do?");
            return;
          }
          for (int j = 0; j < player->inventory->size(); ++j) {
            gameObject *tmp = player->inventory->at(j);
            if (tmp->getType() == KEY &&
                ((Key *)tmp)->getID() ==
                    player->actualRoom->doors->at(i)->getID()) {
              player->actualRoom->doors->at(i)->locked = false;
              setTextBox("You found the key, the door");
              dialogue("opens");
              player->inventory->erase(tmp);
              player->previousRoom = player->actualRoom;
              player->actualRoom = toMove;
              setTextBox("You moved into room " + std::to_string(temp));
              addTextBox(player->actualRoom->describeRoom());
              askInput();
              return;
            }
          }
          setTextBox("it seems you dont have the correct");
          dialogue("key");
          addTextBox("");
          addTextBox("What will you do?");
          return;
        }
      }
    }
  }
  setTextBox("You couldnt go into that room");
  askInput();
}

void transfer() {
  if (teleportable.size() > 1) {
    setTextBox("Teleport to which room?");
    cin.clear();
    string tmp = "";
    int indx;
    for (int i = 0; i < teleportable.size(); i++) {
      if (teleportable.at(i)->getID() != player->actualRoom->getID()) {
        tmp += " [" + std::to_string(teleportable.at(i)->getID()) + "] ";
      }
    }
    addTextBox(tmp);
    system("clear");
    drawUI();
    cin >> indx;
    for (int i = 0; i < teleportable.size(); i++) {
      if (indx == teleportable.at(i)->getID() &&
          indx != player->actualRoom->getID()) {
        player->previousRoom = player->actualRoom;
        player->actualRoom = teleportable.at(i);
        setTextBox("you teleported into the");
        addTextBox("room number: " + std::to_string(indx));
        addTextBox(player->actualRoom->describeRoom());
        askInput();
        return;
      }
    }
    setTextBox("You couldnt go into that room");
    askInput();
  } else {
    setTextBox("There are no other teleporters");
    addTextBox("active");
    askInput();
  }
}

void pause() {
  cin.get();
  system("clear");
  drawUI();
}

void combat() {

  string input = "";
  Vector<string> say;
  bool pTurn = true;
  bool shielding = false;
  bool stunned = false;
  int def = player->baseDEF + player->extraDEF;

  Enemy *adversary = player->actualRoom->enemies->at(0);
  setTextBox("You are fighting a fearsome " + adversary->getName());
  system("clear");
  drawUI();
  cin.get();
  cin.get();
  while (adversary->HP > 0) {
    int chance = rand() % 100;

    // draw fighting UI

    if (pTurn) {
      setTextBox("------------ your turn ------------");
      addTextBox("");
      addTextBox("  [attack] [defend] [drink] [run]  ");
      system("clear");
      drawUI();
      cin >> input;
      if (input == "attack" || input == "a") {
        if (chance > 25) {
          int dmg =
              abs((player->baseDMG + player->extraDMG) - adversary->defence);
          adversary->HP -= dmg;
          addTextBox("");
          addTextBox("You hit the " + adversary->getName() + " and dealt [" +
                     std::to_string(dmg) + "]p of");
          addTextBox("damage.");
        } else {
          addTextBox("");
          addTextBox("The " + adversary->getName() + " avoided your attack!");
        }
        pTurn = false;
      } else if (input == "defend" || input == "d") {
        addTextBox("You embraced for impact");
        def *= 2;
        if (def == 0)
          def = 1;
        shielding = true;
        pTurn = false;
      } else if (input == "run" || input == "r") {
        addTextBox("");
        addTextBox("You try to run away");
        if (chance > 33 + (adversary->HP) * 2) {
          setTextBox("You managed to escape!");
          askInput();
          return;
        } else {
          addTextBox("You couldnt get away!");
          pTurn = false;
        }
      } else if (input == "drink" || input == "d") {
        if (player->potions > 0) {
          addTextBox("You drank a potion");
          if (player->HP < player->maxHP) {
            addTextBox("And restored your HP");
          } else {
            addTextBox("And increased your HP");
            player->maxHP++;
          }
          pTurn = false;
          player->HP = player->maxHP;
          player->potions--;
        } else {
          addTextBox("You dont have any potions!");
          cin.get();
          cin.get();
        }
      }
      if (adversary->HP <= 0) {
        setTextBox("You defeated the " + adversary->getName());
        askInput();
        player->actualRoom->enemies->erase_at(0);
        return;
      }
    } else {
      pause();
      pTurn = true;
      setTextBox("------------ enemy turn -----------");
      if (chance < 20 - adversary->HP && !stunned) {
        addTextBox("The enemy launches, but you");
        addTextBox("managed to avoid its attack");
        pause();
      } else {
        if (!stunned) {
          int dmg = adversary->atk - def;
          if (dmg > 0) {
            addTextBox("The " + adversary->getName() + " attacked and dealt");
            addTextBox("[" + std::to_string(dmg) + "] P of damage");
            player->HP -= dmg;
          } else {
            addTextBox("The " + adversary->getName() +
                       " attacked but its weak");
            addTextBox("weapon couldnt pierce your defences");
          }
        } else {
          stunned = false;
          addTextBox("The enemy is still stunned from");
          addTextBox("your defence and cant attack");
        }
        if (shielding && chance > 75 + adversary->HP && !stunned) {
          addTextBox("The " + adversary->getName() + "\'s weapon bounced back");
          addTextBox("thanks to your defence and got");
          addTextBox("stunned");
          stunned = true;
        }
        pause();
      }
      def = player->baseDEF + player->extraDEF;
      shielding = false;
      pause();
    }
    if (player->HP <= 0) {
      Vector<string> say;
      say.push_back("You were defeated and pushed to");
      say.push_back("the previous room");
      say.push_back("");
      say.push_back("If you lose too many times");
      say.push_back("You will perish...");
      setTextBox(say);

      player->maxHP--;
      player->HP = player->maxHP;
      if (player->maxHP <= 0) {
        runningGame = false;
        gameOver = true;
      }
      player->actualRoom = player->previousRoom;
      adversary->HP = adversary->maxHP;
      return;
    }
  }
}

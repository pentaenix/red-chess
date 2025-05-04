#pragma once
#include "../Structures/Vector.hpp"
using std::string;

class textBox{
public:
  Vector<string> text;

  void setText(string s[], size_t size){
    Vector<string> tmp(s,size);
    text = tmp;
  }

  void setText(string s){
    text.clear();
    text.push_back(s);
  }

  void addText(Vector<string> s){
    for(int i = 0; i < s.size(); i++){
      text.push_back(s[i]);
    }
  }

  void addText(string s){
    text.push_back(s);
  }

};
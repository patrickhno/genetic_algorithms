// string.cpp - copyright (C) 2001-2011 by Patrick Hanevold

//#include "network/socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

//using namespace base;

String::String() : Array<char>(){
  add(0);
}
String::String(const String &str) : Array<char>(str){
}
String::String(const char *str) : Array<char>(){
  for(unsigned int n=0; n<strlen(str)+1; n++) add(str[n]);
}
String::~String(){
}

void String::toLower(){
  int len=length();
  for(int n=0; n<len; n++) (*this)[n]=tolower((*this)[n]);
}

int String::find(const char c) const{
  int len=length();
  for(int n=0; n<len; n++){
    if((*this)[n]==c) return n;
  }
  return -1;
}
String String::substring(int beg, int end) const{
  cout << "1," << beg << ',' << end << ',' << getCount() << endl;
  String s;
  s.clear();
  for(int n=beg; n<end; n++) s.add((*this)[n]);
  s.add(0);
  cout << "2" << endl;
  return s;
}

String String::getWord(){
  String w;
  w.clear();
  int n;
  int len=length();
  for(n=0; n<len; n++) if((*this)[n]!=' ') break;
  for(;n<len&&(*this)[n]!=' '; n++){
    w.add((*this)[n]);
  }
  w.add(0);
  *this=substring(n,len);
  return w;
}

int String::length() const{
//	return strlen(buffer);
  return getCount()-1;
}

void String::toUpperCase(){
  int len=length();
  for(int n=0; n<len; n++){
    if((*this)[n]>='a'&&(*this)[n]<='z') (*this)[n]=(*this)[n]-'a'+'A';
  }
}

String String::trim(){
  int i0 = 0;
  int i1 = length()-1;

  cout << "3" << endl;
  for ( ;(i0 <= i1) && ((*this)[i0] <= ' '); i0++ );
  if ( i0 > i1 ) return "";
  for ( ;(i1 > i0) && ((*this)[i1] <= ' '); i1-- );
  cout << "4" << endl;

  return substring( i0, i1+1);
}

bool String::operator==(const String &str) const{
  for(int n=0; n<length(); n++) if((*this)[n]!=str[n]) return false;
  return true;
}

bool String::operator!=(const String &str) const{
  for(int n=0; n<length(); n++) if((*this)[n]==str[n]) return false;
  return true;
}
bool String::operator>(const String &str) const{
  for(int n=0; n<length()&&n<str.length(); n++){
    if((*this)[n]==str[n]) continue;
    if((*this)[n]>str[n]) return true;
    return false;
  }
}

String &String::operator=(const String &str){
  clear();
  int len=str.length();
  for(int n=0; n<len+1; n++) add(str[n]);
  return *this;
}

String String::operator+(const String &str){
  String ret;
  ret<<*this;
  ret<<str;
  return ret;
}

String &String::operator<<(const String &str){
  *this << str.getString();
  return *this;
}
String &String::operator<<(const char *str){
  remove(length());
  for(unsigned int n=0; n<strlen(str)+1; n++) add(str[n]);
  return *this;
}
String &String::operator<<(const char c){
  (*this)[length()]=c;
  add(0);
  return *this;
}
ostream &operator<<(ostream &out, const String &in){
  out << in.getString();
  return out;
}
/*
OStream &operator<<(OStream &out, const String &in){
  int len=in.length();
  for(int n=0; n<len; n++) out << in[n];
  out << char(0);
  return out;
}
Socket  &operator<<(Socket &out, const String &in){
  //out << strlen(in.buffer);
  out << in.getString();
  return out;
}

IStream &operator>>(IStream &i, String &o){
//  unsigned int len;
//  i >> len;
  char c;
  i >> c;
  while(c){
    o << c;
    i >> c;
  }
  return i;
}
*/

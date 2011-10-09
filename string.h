// string.h - copyright (C) 2001-2011 by Patrick Hanevold

#ifndef __STRING__H
#define __STRING__H

#include "array.h"
//#include "streams.h"

#include <iostream>
using namespace std;

class Socket;

class String : public /*base::*/Array<char>{
public:                 String();
                        String(const String &str);
                        String(const char *str);
                        ~String();
        void            toLower();
//const   char            *getString() const{ return buffer; }
const   char            *getString() const{
          //return list;
          static char str[1024];
          char *d = str;
          for(int n=0; n<getCount(); n++) *d++ = (*this)[n];
          *d++=0;
          return str;
        }
        int             find(const char c) const;
        String          substring(int beg, int end) const;
        String          getWord();
        void            toUpperCase();
        int             length() const;
        
        String trim();
//        String substring( int sIdx, int eIdx);
        
        bool            operator==(const String &str) const;
        bool            operator!=(const String &str) const;
        bool            operator>(const String &str) const;
        String          &operator=(const String &str);
        String          operator+(const String &);
        String          &operator<<(const char *str);
        String          &operator<<(const String &str);
        String          &operator<<(const char c);
        String          &operator<<(const Socket &);
//friend  ostream         &operator<<(ostream &out, const String &in);
//friend  Socket          &operator<<(Socket &out, const String &in);

//friend  OStream         &operator<<(OStream &out, const String &in);
//friend  IStream         &operator>>(IStream &i, String &o);

//        Socket  &operator<<(const String);
//friend  void    operator<<(Socket &,const String&);

/*
friend  class Socket    &operator<<(String &out, Socket &in);
*/
//private:
//  char      *buffer;
};


#endif

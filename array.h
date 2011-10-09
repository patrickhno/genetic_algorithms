// array.h  -  copyright (C) 2001-2011 by Patrick Hanevold

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <assert.h>
#include <stdlib.h>

//class OStream;

#define __bs 32

//namespace base{

template <typename T> class Array{
public: Array(){
          count=0;
          list=0;
        }
        Array(int n){
          count=0;
          list=0;
          init(n);
        }
        Array(const Array<T> &a){
          count = a.count;
          list = (T**)malloc(count*sizeof(T*));
          for(int n=0; n<count; n++){ list[n]=new T(); *(list[n])=*(a.list[n]); }
        }
        ~Array(){
          if(list){
            for(int n=0; n<count; n++){ delete list[n]; }
          }
          free(list);
        }
  void  init(int n){
    if(list){
      for(int n=0; n<count; n++){ delete list[n]; }
    }
    count=n;
    list = (T**)realloc(list,sizeof(T*)*count);
    for(int n=0; n<count; n++) list[n]=new T();
  }
  Array<T> &operator=(const Array<T> &a){
    if(list){
      for(int n=0; n<count; n++){ delete list[n]; }
    }
    free(list);
    count = a.count;
    list = (T**)malloc(count*sizeof(T*));
    for(int n=0; n<count; n++){ list[n]=new T(); *(list[n])=*(a.list[n]); }
    return *this;
  }
  void  clear(){
    if(list){
      for(int n=0; n<count; n++){ delete list[n]; }
    }
    free(list);
    list=0;
    count=0;
  }
  void  remove(int r){
    count--;
    for(int n=r; n<count; n++) list[n]=list[n+1];
    list = (T**)realloc(list,sizeof(T*)*count);
  }
  void  insert(int at, T t){
    count++;
    list = (T**)realloc(list,sizeof(T*)*count);
    for(int n=count-1; n>=at+1; n--) list[n]=list[n-1];
    list[at]=new T();
    *list[at]=t;
  }
  void  add(T t){
    count++;
    list = (T**)realloc(list,sizeof(T*)*count);
    list[count-1]=new T();
    *list[count-1]=t;
  }
  int   getCount() const{ return count; }
  T     &operator[](int i) const{
          assert(i>=0&&i<count);
          return *list[i];
        }
  //friend OStream &operator<<(OStream &out, const Array<T> &in){ return in.out(out); }
  //OStream &out(OStream &out) const{
  //  out << count;
  //  for(int n=0; n<count; n++) out << *list[n];
  //  return out;
  //}
private:
  int   count;
  T     **list;
};

//}

#endif

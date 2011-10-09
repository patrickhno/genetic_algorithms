// copyright (C) 2001-2011 by Patrick Hanevold

// simple template for drawing graphs

template <typename T> class Graph : public Array<T>, public Widget{
public:  Graph() : Array<T>(), Widget(){
         }
         ~Graph(){
         }

  void   add(T v){
    if(Array<T>::getCount()==0) min=max=v;
    else{
           if(v>max) max=v;
      else if(v<min) min=v;
    }
    Array<T>::add(v);
  }

  void   render(Rect r){
    fillRect(r,Color(1,1,1));

    int w = r.w;
    int h = r.h;
    int base = h/10;
    int border = base + h/20;

    drawLine(r.x,r.y+h-1,r.x+r.w,r.y+h-1,Color(0,0,0));
    drawLine(r.x+r.w-1,r.y,r.x+r.w,r.y+h-1,Color(0,0,0));

    // baseline
    drawLine(r.x,r.y+h-base,r.x+r.w,r.y+h-base,Color(0,0,0));
//    double high = log2(max);
//    double low  = log2(min);
    double high = max;
    double low  = min;

    // main graph
    if(Array<T>::getCount()){
      int lastx,lasty;
      for(int n=0; n<Array<T>::getCount(); n++){
        int tox= r.x + n*w/Array<T>::getCount();
//        int toy= r.y + int(h-base-(log2((*this)[n])-low)*(h-border)/(high-low));
        int toy= r.y + int(h-base-(((*this)[n])-low)*(h-border)/(high-low));
        if(n){
          drawClippedLine(
            lastx,
            lasty,
            tox,
            toy,Color(0,0,0));
        }
        lasty=toy;
        lastx=tox;
      }
    }
  }
private:
  T min,max;
};

#include<iostream>
using namespace std;

/*  Watch out the coordinates are integers! */
int maxi(int x, int y){
  return ((x>y)?x:y); }

int mini(int x, int y){
  return ((x<y)?x:y); }

struct Point{
  int x,y; };

struct Segment{
  Point p1,p2; };

bool isInBoundingBox(Segment s, Point p){
  if((mini(s.p1.x,s.p2.x)<=p.x && p.x<=maxi(s.p1.x,s.p2.x)) &&
     (mini(s.p1.y,s.p2.y)<=p.y && p.y<=maxi(s.p1.y,s.p2.y)))
    return true;
  return false;
}

/*  The cross product: (pk-pi) X (pj-pi): Is zero if
parallel segments*/
int CrossProduct(Point pi, Point pj, Point pk){
  return ((pk.x-pi.x)*(pj.y-pi.y) - (pj.x-pi.x)*(pk.y-pi.y));
}

bool isPointOverSegment(Segment s1, Point p)
{  
  if( (CrossProduct(s1.p1, s1.p2, p)==0 
		&& isInBoundingBox(s1,p)) ) return true;
  return false;
}

istream &operator>>(istream &is, Point &p){
  is>>p.x>>p.y;
  return is;
}

istream &operator>>(istream &is, Segment &s){
  is>>s.p1>>s.p2;
  return is;
}

int main(){
  int c;
  c = 0;
  Segment s1;
  Point p;
  while(!cin.eof()){
    cin>>s1; // using operator oeverload!  :)
    if(cin.eof()) break;
    cin>>p; // using operator oeverload!  :)
    cout<<"Case #"<<++c<<":"<<endl;
    if(isPointOverSegment(s1,p))
      cout<<"Yes.";
    else 
      cout<<"No.";
    cout<<endl;
  }
  return 0;
}

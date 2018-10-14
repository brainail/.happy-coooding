#include<iostream>
using namespace std;

/*  Watch out the coordinates are integers! */
struct Point{
  int x,y; };

struct Segment{
  Point p1,p2; };


istream &operator>>(istream &is, Point &p){
  is>>p.x>>p.y;
  return is;
}

istream &operator>>(istream &is, Segment &s){
  is>>s.p1>>s.p2;
  return is;
}

Point operator-(Point p1, Point p2){
  Point temp;
  temp.x = p1.x - p2.x;
  temp.y = p1.y - p2.y;
  return temp;
}

/*  The cross product for vectors:
u X v: Is zero if parallel segments*/
int VectorCrossProduct(Point u, Point v){
  return (u.x*v.y - u.y*v.x);
}

bool isIntersection(Segment s1, Segment s2){
  Point vector1, vector2;
  vector1 = s1.p1-s1.p2;
  vector2 = s2.p1-s2.p2;  
  if( VectorCrossProduct(vector1,vector2) == 0 )
    return false;
  return true;
}

int main(){
  int c;
  c = 0;
  Segment s1,s2;
  while(!cin.eof()){
    cin>>s1; // using operator oeverload!  :)
    if(cin.eof()) break;
    cin>>s2; // using operator oeverload!  :)
    cout<<"Case #"<<++c<<": Do they intersect?"<<endl;
    if(isIntersection(s1,s2))
      cout<<"Yes.";
    else 
      cout<<"No.";
    cout<<endl;
  }
  return 0;
}

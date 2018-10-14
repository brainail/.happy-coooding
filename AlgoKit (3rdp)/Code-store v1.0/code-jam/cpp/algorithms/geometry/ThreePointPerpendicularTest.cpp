#include<iostream>
using namespace std;

/*  Watch out the coordinates are integers! */
struct Point{
  int x,y; };

struct Segment{
  Point p1,p2; };

/*  The point product (pk-pi)°(pj-pi): Is zero if
perpendicular segments*/
int PointProduct(Point pi, Point pj, Point pk){
  return ((pk.x-pi.x)*(pj.x-pi.x) + (pk.y-pi.y)*(pj.y-pi.y));
}

bool ThreePointPerpendicularTest(Point p1, Point p2, Point p3, Segment *sr1, Segment *sr2){
  Segment s1, s2, s3;
  s1.p1 = p1;
  s1.p2 = p2;
  s2.p1 = p2;
  s2.p2 = p3;
  s3.p1 = p3;
  s3.p2 = p1;
  
  if(PointProduct(p2,p1,p3) == 0){
		(*sr1)=s1;
		(*sr2)=s2;
		return true;
  }else if(PointProduct(p3,p2,p1) == 0){
		(*sr1)=s2;
		(*sr2)=s3;
		return true;
  }else if(PointProduct(p1,p3,p2) == 0){
		(*sr1)=s3;
		(*sr2)=s1;
		return true;
  }
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

ostream &operator<<(ostream &os, Point &p){
  os<<"("<<p.x<<","<<p.y<<")";
  return os;
}

ostream &operator<<(ostream &os, Segment &s){
  os<<s.p1<<"-"<<s.p2;
  return os;
}
int main(){
  int c;
  c = 0;
  Segment s1,s2;
  Point p1,p2,p3;
  while(!cin.eof()){
    cin>>p1; // using operator overload!  :)
    if(cin.eof()) break;
    cin>>p2; // using operator overload!  :)
    if(cin.eof()) break;
    cin>>p3; // using operator overload!  :)
    cout<<"Case #"<<++c<<":"<<endl;
    if(ThreePointPerpendicularTest(p1,p2,p3,&s1,&s2))
      cout<<"Yes. Segments are "<<s1<<" y "<<s2;
    else 
      cout<<"No.";
    cout<<endl;
  }
  return 0;
}

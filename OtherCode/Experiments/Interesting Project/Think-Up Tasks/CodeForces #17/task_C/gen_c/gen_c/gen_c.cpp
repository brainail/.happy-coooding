#include "testlib.h"
#include <iostream>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int main(int argc, char* argv[]) {
 registerGen(argc, argv);

 int pa = atoi(argv[2]);
 int pb = atoi(argv[3]);
 int pc = 100 - pa - pb;
 if(pc < 0) pc = 0;
 
 string token = "";
 token += "[";
 
 forr(i,1,pa) token += 'a';
 forr(i,1,pb) token += 'b';
 forr(i,1,pc) token += 'c';
 
 token += "]";

 token = token + "{" + argv[1] + "," + argv[1] + "}";
 
 string ans = rnd.next(token);
 
 cout << ans.length() << endl;
 
 cout << ans << endl;

 return 0;
}

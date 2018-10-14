#include<iostream>
#include<string.h>
using namespace std;

int findMatch(char *p, char*t)
{
    int plen, tlen;
    
    plen = strlen(p);
    tlen = strlen(t);
    
    for(int i=0; i<=(tlen-plen); i++) {
       int j=0; 
       
       while((j<plen) && (t[i+j]==p[j]))
          j++;
       if(j == plen) 
          return i;
    }
    return -1;
}

int main()
{
    int position = findMatch("jair", "Cazarin jai villanueva jair");
    cout << position << endl;
    return 0;
}

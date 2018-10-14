#include <stdio.h>
#include <map>
#include <malloc.h>

struct species {
   char s[81];
} buf;

bool operator==(const species &a, const species &b) {
   return !strcmp(a.s, b.s);
}

bool operator<(const species &a, const species &b) {
   return strcmp(a.s, b.s) < 0;
}

map<species,int> cnt;

main(){
   int tot = 0;
   while(gets(buf.s)){
      cnt[buf]++;
      tot++;
   }
   for (map<species,int>::iterator i = cnt.begin(); i!=cnt.end(); *i++) {
      printf("%s %0.4lf\n",i->first.s, 100.0*i->second/tot);
   }
}

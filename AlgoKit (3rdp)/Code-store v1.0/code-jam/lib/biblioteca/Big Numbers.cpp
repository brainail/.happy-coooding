#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(A,B) (A)>(B)?(A):(B)
#define SIZ 100

class BigNum {
 public:

   int digit[SIZ];
       int len;

   BigNum();       /* set to zero */
   BigNum(char *); /* set from numeric string */


   void divide_by_int(int dividend, int &remainder);

       /* metodos de inicializacao */
       BigNum& operator=(const BigNum &n);
       BigNum& operator=(int n);

       /* operacoes aritmeticas */
       BigNum operator*(BigNum &n);
       BigNum operator*(int factor);
       BigNum operator+(BigNum &n);
       BigNum operator-(BigNum &n);
       BigNum operator^(BigNum &n);

       /* shift left de n numeros, o mesmo que multiplicar por 10^n*/
       BigNum& operator<<(const int n);


       /* metodos de comparacao */
       bool operator>(BigNum &n);
       bool operator<(BigNum &n);
       bool operator==(BigNum &n);

       /* metodos auxiliares*/
   void print();
};


  /* initialize to 0 */

BigNum::BigNum() {
   for (int i=0; i<SIZ; i++) digit[i] = 0;
       len = 1;
}

  /* set from a numeric string.  remember the string will be

     most-to-least in significance */

BigNum::BigNum(char *str) {
   int i, j;
   for (i=0; i<SIZ; i++) digit[i] = 0;

   j = strlen(str) - 1;
   i = 0;
   while (j >= 0) {
       digit[i] = str[j] - '0';
       j--;
       i++;
   }

       len = i;
}

void BigNum::divide_by_int(int dividend, int &remainder) {
   int i = len-1;
   remainder = 0;
   while (i >= 0) {
       remainder = remainder * 10 + digit[i];
       digit[i] = 0;
       if (dividend <= remainder) {
           digit[i] = remainder / dividend;
           remainder %= dividend;
       }
       i--;
   }

}

//multipilca por 10^n
BigNum& BigNum::operator<<( int n) {
       memmove(&this->digit[n], this->digit,(SIZ-n)*sizeof(int));
       for(int i=0; i<n; i++)
               this->digit[i]= 0;

       len += n;
       return *this;
}


BigNum& BigNum::operator=(const BigNum &n) {
       if (this != &n) {
               memcpy(this->digit,n.digit,sizeof(this->digit));
               len = n.len;
       }
       return *this;
}

BigNum& BigNum::operator=(int n) {
       char str[15];
       BigNum res;

       sprintf(str, "%d", n);
       res = BigNum(str);

       *this = res;

       return *this;
}

BigNum BigNum::operator*(int factor) {
   int i,carry = 0;
       BigNum res = *this;

   for (i=0; i<res.len || carry; i++) {
       carry += res.digit[i] * factor;
       res.digit[i] = carry % 10;
       carry /= 10;
   }

       if (i > res.len) {
               res.len = i;
       }

       return res;
}

BigNum BigNum::operator*(BigNum &n) {
       BigNum res, prod;

       for (int i = 0; i < n.len; i++) {
               prod = *this * n.digit[i];
               prod<<i;
               res = res + prod;
       }

       return res;
}

BigNum BigNum::operator+(BigNum &n) {
       BigNum res;

       int i,carry = 0;
       int maxLen = MAX(this->len, n.len);

       for (i=0; i<maxLen || carry; i++) {
               carry += this->digit[i] + n.digit[i];
               res.digit[i] = carry % 10;
               carry /= 10;
       }
       res.len = MAX(this->len,i);

       return res;
}

/* Assumindo que n eh menor que this */
BigNum BigNum::operator-(BigNum &n) {
       BigNum res, n1, n2;

       n1 = *this;
       n2 = n;

       int carry = 0;
       int maxLen = MAX(n1.len, n2.len);
       int i = 0;

       for (i=0; i<maxLen || carry; i++) {
               carry = n1.digit[i] - n2.digit[i] - carry;
               if(carry >= 0) {
                       res.digit[i] = carry;
                       carry = 0;
               } else {
                       res.digit[i] = carry+10;
                       carry = 1;
               }
       }

       while(!res.digit[i] && i) i--;
       res.len = i+1;

       return res;
}

/* exponenciacao a potencia n */
BigNum BigNum::operator^(BigNum &n) {
       BigNum res, pot, zero, um;

       um = 1;
       pot = 2;
       res = *this;

       if (n == zero) {
               res = 1;
       } else if (!(n == um)) {
               while(1) {
                       res = res * res;

                       if (pot*2 > n) {
                               BigNum dif = n - pot;
                               while(!(dif == zero)) {
                                       res = res * (*this);
                                       dif = dif - um;
                               }
                               break;
                       } else {
                               pot = pot * 2;
                       }

                       if (pot == n) break;
               }
       }

       return res;
}


bool BigNum::operator>(BigNum &n) {
   int i = MAX(len-1, n.len-1);

   while (n.digit[i] == this->digit[i] && i>0) i--;
       return (this->digit[i]> n.digit[i]);
}

bool BigNum::operator==(BigNum &n) {
       return (memcmp(this->digit,n.digit,this->len*sizeof(this->digit[0]))==0)
                       && (this->len == n.len);
}

bool BigNum::operator<(BigNum &n) {
       return !( *this > n || *this == n );
}

void BigNum::print() {
   int i = len-1;

   while (digit[i] == 0 && i > 0) i--;

   while (i >= 0) {
       putchar('0' + digit[i]);
       i--;
   }
}


int casos;
char n[100];
struct BigNum m,m1,m2,m3,m4;

int readdata(){

   if( scanf("%s",n) != 1 ) return 0;
   return 1;
}

int process(){
    
    
    int tam = strlen(n);
    int i;
    BigNum total = BigNum("0");
    BigNum sum = BigNum("1");
    
    for(i=tam-1;i>=0;i--){
        if( n[i] == 'b' ){
            total = total + sum;
        }
        sum = sum*2;
    }
    
    printf("Palavra %d\n",casos++);
    total.print();
    printf("\n\n");
    return 0;
}

int main(){
    casos=1;
    while( readdata())  process();
   
    return 0;
}


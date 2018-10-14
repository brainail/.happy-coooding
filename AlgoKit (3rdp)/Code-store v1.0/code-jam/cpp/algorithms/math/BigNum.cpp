# include <stdio.h>
# include <string.h>

//typedef __int64 Big;
typedef long long Big;

# define MAXLEN 300

void rev(char s[])
{
  int len=strlen(s),t;
  for(int i=0,j=len-1;i<j;i++,j--){
    t=s[i];
    s[i]=s[j];
    s[j]=t;
  }
}

class BigNum{
  int len;
  char n[MAXLEN+1];
 public:
  BigNum();
  BigNum(int val);
  void trim();
  void print();
  void get(char s[]);
  BigNum operator=(BigNum b);
  BigNum operator=(int b);
  BigNum operator=(char s[]);
  BigNum operator+(BigNum b);
  BigNum operator+(int b);
  BigNum operator-(BigNum b);
  BigNum operator-(int b);
  BigNum operator>>(int b);
  BigNum operator*(int b);
  BigNum operator*(BigNum b);
  BigNum operator^(int b);
  BigNum operator/(BigNum b);
  BigNum operator/(int b);
  BigNum operator%(BigNum b);
  int operator%(int b);
  BigNum sqrt(void);
  BigNum gcd(BigNum b);
  BigNum lcm(BigNum b);
  int operator==(BigNum b);
  int operator==(int b);
  int operator!=(BigNum b);
  int operator!=(int b);
  int operator<(BigNum b);
  int operator<=(BigNum b);
  int operator>(BigNum b);
  int operator>=(BigNum b);
  int operator<(int b);
  int operator<=(int b);
  int operator>(int b);
  int operator>=(int b);
};

BigNum::BigNum()
{
  len=0;
}
BigNum::BigNum(int val)
{
  char s[MAXLEN+1];
  sprintf(s,"%d",val);
  rev(s);
  len=strlen(s);
  strcpy(n,s);
}  
void BigNum::trim()
{
  int i;
  for(i=len-1;i>0;i--)
    if(n[i]!='0')
	break;
  len=i+1;
}
void BigNum::print()
{
  int i;
  for(i=len-1;i>=0;i--)
    putchar(n[i]);
}
void BigNum::get(char s[])
{
  n[len]='\0';
  strcpy(s,n);
  rev(s);
}
BigNum BigNum::operator=(BigNum b)
{
  len=b.len;
  b.n[len]='\0';
  strcpy(n,b.n);
  return *this;
}
BigNum BigNum::operator=(int b)
{
  char s[MAXLEN+1];
  sprintf(s,"%d",b);
  rev(s);
  len=strlen(s);
  strcpy(n,s);
  return *this;
}
BigNum BigNum::operator=(char s[])
{
  len=strlen(s);
  strcpy(n,s);
  rev(n);
  this->trim();
  return *this;
}
BigNum BigNum::operator+(BigNum b)
{
  BigNum c;
  int k,t,t1,t2,carry;
  for(carry=0,k=0;k<len || k<b.len;k++){
    t1= k<len? n[k]-'0':0;
    t2= k<b.len? b.n[k]-'0':0;
    t=carry+t1+t2;
    c.n[k]=t%10+'0';
    carry=t/10;
  }
  if(carry) c.n[k++]=carry+'0';
  c.len=k;
  c.trim();
  return c;
}
BigNum BigNum::operator+(int b)
{
  BigNum c(b);
  return *this+c;
}
BigNum BigNum::operator-(BigNum b)
{
  BigNum c;
  int k,t,t1,t2,borrow;
  for(borrow=0,k=0;k<len || k<b.len;k++){
    t1= k<len? n[k]-'0':0;
    t2= k<b.len? borrow+b.n[k]-'0':borrow;
    borrow=0;
    if(t1<t2){
      t1+=10;
      borrow=1;
    }
    t=t1-t2;
    c.n[k]=t+'0';
  }
  c.len=k;
  c.trim();
  return c;
}
BigNum BigNum::operator-(int b)
{
  BigNum c(b);
  return *this-c;
}
BigNum BigNum::operator>>(int b)
{
  int i;
  BigNum c(*this);
  for(i=c.len-1;i>=0;i--)
    c.n[i+b]=c.n[i];
  for(i=0;i<b;i++)
    c.n[i]='0';
  c.len+=b;
  return c;
}
BigNum BigNum::operator*(int b)
{
  BigNum c;
  Big k,carry,t;
  for(carry=0,k=0;k<len;k++){
    t=b*(Big)(n[k]-'0')+carry;
    c.n[k]=t%10+'0';
    carry=t/10;
  }
  while(carry){
    c.n[k++]=carry%10+'0';
    carry/=10;
  }
  c.len=k;
  c.trim();
  return c;
}
BigNum BigNum::operator*(BigNum b)
{
  int k;
  BigNum c(0);
  for(k=0;k<b.len;k++)
    c=c+(((*this)*(b.n[k]-'0'))>>k);
  c.trim();
  return c;
}
BigNum BigNum::operator^(int b)
{
  BigNum d=1;
  int k=1<<(8*sizeof(int)-2);
  while(!(k&b) && k)
    k>>=1;
  while(k){
    d=d*d;
    if(k&b) d=d*(*this);
    k>>=1;
  }
  d.trim();
  return d;
}
BigNum BigNum::operator/(BigNum b)
{
  BigNum c=0,d=0;
  int i,k;
  for(k=len-1;k>=0;k--){
    c=c*10+(n[k]-'0');
    for(i=1;i<=9;i++)
      if(c<b*i)
	break;
    d=d*10+(i-1);
    c=c-b*(i-1);
  }
  d.trim();
  return d;
}
BigNum BigNum::operator/(int b)
{
  BigNum c=b;
  return (*this)/c;
}
BigNum BigNum::operator%(BigNum b)
{
  BigNum c=0;
  int i,k;
  for(k=len-1;k>=0;k--){
    c=c*10+(n[k]-'0');
    for(i=1;i<=9;i++)
      if(c<b*i)
	break;
    c=c-b*(i-1);
  }
  c.trim();
  return c;
}
int BigNum::operator%(int b)
{
  BigNum c=b;
  int r;
  c=(*this)%c;
  rev(c.n);
  sscanf(c.n,"%d",&r);
  return r;
}
BigNum BigNum::sqrt(void)
{
  int i,j,k=len-1;
  BigNum b,c,d;
  i=n[k--]-'0';
  if(len%2==0) i=10*i+n[k--]-'0';
  for(j=1;j<=9;j++)
    if(i<j*j)
      break;
  b=i-(j-1)*(j-1);
  c=j-1;
  while(k>=0){
    b=b*100+10*(n[k]-'0')+(n[k-1]-'0');
    k-=2;
    d=c*20;
    for(j=0;j<=9;j++)
      if(b<(d+j)*j)
	break;
    j--;
    c=c*10+j;
    b=b-(d+j)*j;
  }
  c.trim();
  return c;
}
BigNum BigNum::gcd(BigNum b)
{
  if(b==0) return *this;
  return b.gcd((*this)%b);
}
BigNum BigNum::lcm(BigNum b)
{
  return ((*this)*b)/this->gcd(b);
}
int BigNum::operator==(BigNum b)
{
  n[len]='\0';
  b.n[b.len]='\0';
  return !strcmp(n,b.n);
}
int BigNum::operator==(int b)
{
  BigNum c=b;
  return c==*this;
}
int BigNum::operator!=(BigNum b)
{
  return !(*this==b);
}
int BigNum::operator!=(int b)
{
  BigNum c=b;
  return c!=*this;
}
int BigNum::operator<(BigNum b)
{
  int i;
  if(len<b.len) return 1;
  if(len>b.len) return 0;
  for(i=len-1;i>=0;i--)
    if(n[i]!=b.n[i])
      break;
  return n[i]<b.n[i];
}
int BigNum::operator<=(BigNum b)
{
  int i;
  if(b==*this || len<b.len) return 1;
  if(len>b.len) return 0;
  for(i=len-1;i>=0;i--)
    if(n[i]!=b.n[i])
      break;
  return n[i]<b.n[i];
}
int BigNum::operator>(BigNum b)
{
  int i;
  if(len>b.len) return 1;
  if(len<b.len) return 0;
  for(i=len-1;i>=0;i--)
    if(n[i]!=b.n[i])
      break;
  return n[i]>b.n[i];
}
int BigNum::operator>=(BigNum b)
{
  int i;
  if(b==*this || len>b.len) return 1;
  if(len<b.len) return 0;
  for(i=len-1;i>=0;i--)
    if(n[i]!=b.n[i])
      break;
  return n[i]>b.n[i];
}
int BigNum::operator<(int b)
{
  BigNum c=b;
  return (*this)<c;
}
int BigNum::operator<=(int b)
{
  BigNum c=b;
  return (*this)<=c;
}
int BigNum::operator>(int b)
{
  BigNum c=b;
  return (*this)>c;
}
int BigNum::operator>=(int b)
{
  BigNum c=b;
  return (*this)>=c;
}
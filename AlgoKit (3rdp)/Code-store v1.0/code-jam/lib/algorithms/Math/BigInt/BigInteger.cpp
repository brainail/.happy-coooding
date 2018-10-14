#include <iostream>
#include <strstream>
#include <string>
#include <stdexcept>
#include <malloc.h>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

/**
 * BigInteger Class
 * Version 6.7.25
 *
 * Copyright (c) 2001
 * Mahbub Murshed Suman (suman@bttb.net.bd)
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Mahbub Murshed Suman makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

namespace BigMath
{
  enum BigMathERROR { BigMathMEM = 1 , BigMathOVERFLOW , BigMathUNDERFLOW, BigMathINVALIDINTEGER, BigMathDIVIDEBYZERO,BigMathDomain};

  const char *BigIntErrDes[] = { "Allocation Failed", "Overflow","Underflow", "Invalid Integer", "Divide by Zero" ,"Domain Error"};
  const char BigIntPROGRAMNAME[] = { "BigInteger" };
  const int BigIntMajorVersion = 6;
  const int BigIntMinorVersion = 7;
  const int BigIntRevision = 25;

  void Dump(const char *,enum BigMathERROR);
  string& DumpString (char const*,enum BigMathERROR);

  // The Size Type
  typedef unsigned int SizeT;
  // The Data Type
  typedef unsigned int DATATYPE;

  // The Base Used
  const DATATYPE BASE = 10000;
  // An invalid data
  const DATATYPE INVALIDDATA = 65535U;
  // Number of digits in `BASE'
  const SizeT LOG10BASE = 4;
  class BigInteger
  {
  private:
    // The integer array to hold the number
    DATATYPE *TheNumber;
    // Start of the location of the number in the array
    SizeT Start;
    // End  of the location of the number in the array
    SizeT End;
    // True if the number is negative
    bool isNegative;

    // Constructor with specified bytes
    BigInteger(SizeT,DATATYPE,bool);

    // Copies data to 'this' upto size bytes
    void datacopy(BigInteger const&,SizeT);

    // Determines valid data range
    SizeT datalen(DATATYPE const*) const;
    // deallocates the array
    void deallocateBigInteger();
    // Trims zeros in front of a number
    void TrimZeros();
    // the array with the `fill' value
    void Set(DATATYPE);

    // Subscript operator
    DATATYPE& operator[](unsigned int) const;
  public:
    // Default Constructor
    BigInteger();
    // Long integer constructor
    BigInteger(long);
    // Character array constructor
    BigInteger(char const*);
    // Copy Constructor
    BigInteger(BigInteger const&);

    // The Destructor
    ~BigInteger();

    // Compares Two BigInteger values irrespective of sign
    int UnsignedCompareTo(BigInteger const&)const;
    // Compares Two BigInteger values
    int CompareTo(BigInteger const&)const;

    // Returns Number of digits in the BigInteger
    SizeT Digits() const;
    // Determines if the number representation is OK or not
    bool isValidNumber() const;
    // True is the nubmer is zero
    bool isZero()const;

    // Straight pen-pencil implementation for addition
    BigInteger& Add(BigInteger const&) const;
    // Straight pen-pencil implementation for subtraction
    BigInteger& Subtract(BigInteger const&) const;
    // Straight pen-pencil implementation for multiplication
    BigInteger& Multiply(BigInteger const&) const;
    BigInteger& Multiply(DATATYPE const&) const;
    // Straight pen-pencil implementation for division and remainder
    BigInteger& DivideAndRemainder(BigInteger const&,BigInteger&,bool) const;
    BigInteger& DivideAndRemainder(DATATYPE const&,DATATYPE&,bool) const;

    // Overloaded Binary Operators

    // Adds Two BigInteger
    friend BigInteger& operator+(BigInteger const&, BigInteger const&);
    // Subtructs Two BigInteger
    friend BigInteger& operator-(BigInteger const&, BigInteger const&);
    // Multiplies Two BigInteger
    friend BigInteger& operator*(BigInteger const&, BigInteger const&);
    friend BigInteger& operator*(BigInteger const&, DATATYPE const&);
    friend BigInteger& operator*(DATATYPE const&, BigInteger const&);
    // Divides Two BigInteger
    friend BigInteger& DivideAndRemainder(BigInteger const&, BigInteger const&,BigInteger&,bool);
    friend BigInteger& DivideAndRemainder(BigInteger const&, DATATYPE const&,DATATYPE&,bool);
    friend BigInteger& operator/(BigInteger const&, BigInteger const&);
    friend BigInteger& operator/(BigInteger const&, DATATYPE const&);
    friend BigInteger& operator/(DATATYPE const&, BigInteger const&);
    // Modulo Division of Two BigInteger
    friend BigInteger& operator%(BigInteger const&, BigInteger const&);
    friend BigInteger& operator%(BigInteger const&, DATATYPE const&);
    friend BigInteger& operator%(DATATYPE const&, BigInteger const&);

    // Assignment Operator
    BigInteger& operator=(BigInteger const&);

    // Inserter
    friend ostream& operator<<(ostream& ,  BigInteger const&);
    // Extractor
    friend istream& operator>>(istream& , BigInteger& );

    // Overloaded Unary Operators

    // Postfix Unary Increment
    BigInteger& operator++();
    // Prefix Unary Increment
    BigInteger& operator++(int);

    // Postfix Unary Decrement
    BigInteger& operator--();
    // Prefix Unary Decrement
    BigInteger& operator--(int);

    // Negation
    BigInteger& operator-();

    // Bit Wise Operators

    // Left Shift
    BigInteger& operator<<(SizeT);
    // Right Shift
    BigInteger& operator>>(SizeT);
    // Returns the BigInteger absolute
    void abs();
    friend BigInteger& abs(BigInteger&);

    // Conversion functions
    string& toString() const;
    int toInt();
    long toLong();

  };

  // Private Constructor which provides a new BigInteger Object
  // Filled with specified data
  // Useful for internal operation
  BigInteger::BigInteger(SizeT bytes,DATATYPE fill, bool toInit = true)
  {
    TheNumber = new DATATYPE[bytes];
    isNegative = false;
    Start = 0;
    End = bytes - 1;

    if(toInit) Set(fill);
  }

  // Default Constructor
  BigInteger::BigInteger()
  {
    TheNumber = new DATATYPE[1];
    TheNumber[0] = 0;
    Start = 0;
    End = 0;
    isNegative = false;
  }

  // Long Constructor
  BigInteger::BigInteger(long n)
  {
    if(n<0)
    {
      isNegative = true;
      n *= -1;
    }
    else isNegative = false;

    SizeT i = (SizeT)(floor(log10((double)n)/LOG10BASE) + 1);

    Start = 0;
    End = i-1;
    TheNumber = new DATATYPE [i];
    Set(0);

    while(n)
    {
      TheNumber[--i] = n % BASE;
      n /= BASE;
    }
    TrimZeros();
  }

  // Character array constructor
  BigInteger::BigInteger(char const* n)
  {
    if(n[0]=='-') { isNegative = true; n++; }
    else if(n[0]=='+') { isNegative = false; n++; }
    else isNegative = false;

    while(*n=='0') n++;

    int l = strlen(n);
    if(l==0)
    {
      *this = *new BigInteger();
      return;
    }
    Start = 0;
    End = (SizeT)(l/LOG10BASE + l%LOG10BASE - 1);
    TheNumber = new DATATYPE [Digits()];
    Set(0);

    int cur = l - 1;
    for(SizeT i = End; i>=Start;i--)
    {
      if(cur<0) break;
        DATATYPE r = 0;
      DATATYPE TEN = 1;
      for(l=0;l<4;l++)
      {
        if(cur<0) break;
        r = r + TEN*(n[cur]-'0');
        TEN *= 10;
        cur--;
      }
      TheNumber[i] = r;
    }
    TrimZeros();
    if(isZero()) isNegative = false;
  }

  // Copy constructor
  BigInteger::BigInteger(BigInteger const& Temp)
  {
    Start = 0;
    End = Temp.Digits() - 1;
    TheNumber = new DATATYPE [Temp.Digits()];

    datacopy(Temp,Temp.Digits());
    isNegative = Temp.isNegative;
  }

  // Deallocates the array
  void BigInteger::deallocateBigInteger()
  {
    if(TheNumber!=0)
    {
      delete [] TheNumber;
      TheNumber = 0;
    }
  }

  // The Destructor
  BigInteger::~BigInteger()
  {
    deallocateBigInteger();
    Start = 0;
    End = 0;
  }

  // Sets the array with the `fill' value
  void BigInteger::Set(DATATYPE fill)
  {
    for(SizeT i=Start;i<=End;i++)
      TheNumber[i] = fill;
  }

  // Copies data from `a' to `this'
  void BigInteger::datacopy(BigInteger const& a,SizeT size)
  {
    for(SizeT i=0;i<size;i++)
      TheNumber[Start+i] = a.TheNumber[a.Start+i];
  }

  // Determines the length upto valid data
  SizeT BigInteger::datalen(DATATYPE const* a) const
  {
    SizeT l = 0;
    while(a[l]!=INVALIDDATA) l++;
    return l;
  }

  // Returns number of digits in a BigInteger
  SizeT BigInteger::Digits() const
  { return End-Start+1; }

  // true if 'this' is zero
  bool BigInteger::isZero() const
  { return End==Start && TheNumber[Start]==0; }

  // Checks for the validity of the number
  bool BigInteger::isValidNumber() const
  {
    for(SizeT i=Start; i<End ; i++)
      if(TheNumber[i]>=BASE) return false;

    return true;
  }

  // Trims Leading Zeros
  void BigInteger::TrimZeros()
  {
    while(TheNumber[Start]==0 && Start<End)
      Start++;
  }

  // Compares this with `with' irrespective of sign
  // Returns
  // 0 if equal
  // 1 if this>with
  // -1 if this<with
  int BigInteger::UnsignedCompareTo(BigInteger const& with)const
  {
    if(isZero() && with.isZero()) return 0;
    if(!isZero() && with.isZero()) return 1;
    if(isZero() && !with.isZero()) return -1;

    long temp = Digits() - with.Digits();
    // Case 3: First One got more digits
    // Case 4: First One got less digits
    if(temp!=0) return temp<0?-1:1;

    // Now I know Both have same number of digits
    // Case 5,6,7:
    /*
    Compares two array of data considering the
    case that both of them have the same number
    of digits
    */

    int cmp = 0;
    for(SizeT i=0;i<Digits();i++)
    {
      temp = TheNumber[i+Start] - with.TheNumber[i+with.Start];
      if(temp!=0)
      {
        cmp = temp<0?-1:1;
        break;
      }
    }

    return cmp;
  }

  // Compares this with `with'
  // Returns
  // 0 if equal
  // 1 if this>with
  // -1 if this<with
  int BigInteger::CompareTo(BigInteger const& with)const
  {
    int cmp = UnsignedCompareTo(with);

    // Case 1: Positive , Negative
    if(isNegative==false && with.isNegative==true) return 1;
    // Case 2: Negative, Positive
    if(isNegative==true && with.isNegative==false) return -1;
    // Now, Both are Same Sign
    int both_neg = 1;
    if(isNegative==true && with.isNegative==true) both_neg = -1;
    return cmp*both_neg;
  }

  // Implentation of addition by paper-pencil method
  BigInteger& BigInteger::Add(BigInteger const& Small) const
  {
    BigInteger const& Big = *this;
    BigInteger &Result= *new BigInteger(Big.Digits()+1,0);

    long Carry=0,Plus;
    long i=Big.Digits() - 1,
      j=Small.Digits() -1;

    for(; i>=0 ;i--,j--){
      Plus = Big.TheNumber[i+Big.Start] + Carry;
      if(j>=0) Plus += Small.TheNumber[j+Small.Start] ;

      Result.TheNumber[i+1] = Plus%BASE;
      Carry = Plus/BASE;
    }
    i++;

    if(Carry) Result.TheNumber[i] = Carry;

    Result.TrimZeros();

    return Result;
  }

  // Implentation of subtraction by paper-pencil method
  BigInteger& BigInteger::Subtract(BigInteger const& Small)const
  {
    BigInteger const& Big = *this;
    BigInteger& Result = *new BigInteger(Big.Digits()+1,0);

    long Carry=0,Minus;

    long i = Big.Digits() - 1,
      j= Small.Digits() - 1;

    for( ; i>=0 ;i--,j--)
    {
      Minus = Big.TheNumber[i+Big.Start] - Carry;
      if(j>=0) Minus -= Small.TheNumber[j+Small.Start];

      if(Minus < 0)
      {
        Result.TheNumber[i+1] = Minus + BASE;
        Carry = 1;
      }
      else
      {
        Result.TheNumber[i+1]  = Minus;
        Carry = 0;
      }
    }
    Result.TrimZeros();
    return Result;
  }

  // Addition operator
  BigInteger& operator+(BigInteger const& N1, BigInteger const& N2)
  {
    if(N1.isNegative && !N2.isNegative)
    {
      // First is negaive and second is not
      BigInteger& Res = *new BigInteger(N1);
      Res.isNegative = false;
      Res = N2-Res;
      return Res;
    }
    if(!N1.isNegative && N2.isNegative)
    {
      // Second is negaive and first is not
      BigInteger& Res = *new BigInteger(N2);
      Res.isNegative = false;
      Res = N1-Res;
      return Res;
    }

    BigInteger& ret = *new BigInteger();

    if(N1.UnsignedCompareTo(N2)<0)
      ret = N2.Add(N1);
    else
      ret = N1.Add(N2);
    if(N1.isNegative==true && N2.isNegative==true)
      ret.isNegative = true;
    return ret;
  }

  // Subtruction operator
  BigInteger& operator-(BigInteger const& N1, BigInteger const& N2)
  {
    if(N1.isNegative && !N2.isNegative)
    {
      BigInteger& res = *new BigInteger(N1);
      res.isNegative = false;
      res = res+N2;
      res.isNegative = true;
      return res;
    }
    if(!N1.isNegative && N2.isNegative)
    {
      BigInteger& res = *new BigInteger(N2);
      res.isNegative = false;
      res = res+N1;
      return res;
    }


    BigInteger& ret = *new BigInteger();
    int cmp = N1.UnsignedCompareTo(N2);
    if(cmp==0)
    {
      ret = *new BigInteger();
    }
    if(cmp<0)
    {
      ret = N2.Subtract(N1);
      ret.isNegative = true;
    }
    else
    {
      ret = N1.Subtract(N2);
      ret.isNegative = false;
    }
    return ret;
  }

  // Implentation of multiplication by paper-pencil method
  BigInteger& BigInteger::Multiply(BigInteger const& Small) const
  {
    BigInteger const& Big = *this;
    BigInteger& Result = *new BigInteger(Big.Digits()+Small.Digits(),0);

    long Carry,Multiply;

    SizeT i;
    SizeT j;

    for(i = 0 ; i< Small.Digits() ; i++)
    {
      Carry = 0;
      for(j = 0 ; j< Big.Digits() ; j++)
      {
        Multiply = ( (long)Small.TheNumber[Small.End-i] * (long)Big.TheNumber[Big.End-j] )
          + Carry + Result.TheNumber[Result.End-i-j];
        Result.TheNumber[Result.End-i-j] = Multiply%BASE;
        Carry = Multiply/BASE ;
      }
      Result.TheNumber[Result.End-i-j] = Carry;
    }

    Result.TrimZeros();

    return Result;
  }

  // Implentation of multiplication by paper-pencil method
  // See: D. E. Knuth 4.3.1
  BigInteger& BigInteger::Multiply(DATATYPE const& with) const
  {
    BigInteger& Result = *new BigInteger(Digits()+1,0);

    long Carry,Multiply;

    SizeT i;

    Carry = 0;
    for(i = 0 ; i< Digits() ; i++)
    {
      Multiply = Carry + (long)TheNumber[End-i] * (long)with;
      Carry = Multiply / BASE;
      Result.TheNumber[Result.End-i] = Multiply % BASE;
    }
    Result.TheNumber[Result.End-i] = Carry;
    Result.TrimZeros();

    return Result;
  }

  // Multiplication operator
  BigInteger& operator*(BigInteger const& N1, BigInteger const& N2)
  {
    if(N1.isZero() || N2.isZero()) return *new BigInteger();
    BigInteger& ret = *new BigInteger();
    if(N1.UnsignedCompareTo(N2)<0)
      ret = N2.Multiply(N1);
    else
      ret = N1.Multiply(N2);
    if(N1.isNegative!=N2.isNegative)
      ret. isNegative = true;
    return ret;
  }

  // Multiplication operator
  BigInteger& operator*(BigInteger const& N1, DATATYPE const& N2)
  {
    if(N1.isZero() || N2==0) return *new BigInteger();
    BigInteger& ret = N1.Multiply(N2);
    // if(N1.isNegative!=(N2<0)) ret. isNegative = true;
    return ret;
  }

  // Multiplication operator
  BigInteger& operator*(DATATYPE const& N1, BigInteger const& N2)
  {
    if(N2.isZero() || N1==0) return *new BigInteger();
    BigInteger& ret = N2.Multiply(N1);
    // if(N2.isNegative!=(N1<0)) ret. isNegative = true;
    return ret;
  }

  // Implentation of division by paper-pencil method
  // Here `this' is divided by 'V'
  BigInteger& BigInteger::DivideAndRemainder(DATATYPE const& V,DATATYPE& _R,bool skipRemainder=false) const
  {
    BigInteger& W = *new BigInteger(Digits(),0,false);
    DATATYPE R = 0;
    SizeT j;
    for(j=0;j<=End;j++)
    {
      W.TheNumber[j] = (R*BASE+TheNumber[Start+j])/V;
      R = (R*BASE+TheNumber[Start+j])%V;
    }

    W.TrimZeros();
    if(skipRemainder==false)
      _R = R;

    return W;
  }

  // Implentation of division by paper-pencil method
  // Does not perform the validity and sign check
  // It is assumed that this > `_V'
  // See: D.E.Knuth 4.3.1
  BigInteger& BigInteger::DivideAndRemainder(BigInteger const& _V,BigInteger& R,bool skipRemainder=false) const
  {
    SizeT m = this->Digits()-_V.Digits();
    SizeT n = _V.Digits();
    BigInteger& Q = *new BigInteger(m+1,0,false);

    DATATYPE d, qhat, rhat;
    long temp,x,y;
    SizeT i;
    int j;

    d = (BASE-1)/_V.TheNumber[_V.Start];

    BigInteger& U = this->Multiply(d);
    BigInteger& V = _V.Multiply(d);

    for(j = m; j>=0; j--)
    {
      temp = (long)U.TheNumber[U.End-j-n]*(long)BASE + (long)U.TheNumber[U.End-j-n+1];
      x = temp / (long)V.TheNumber[V.Start];
      y = temp % (long)V.TheNumber[V.Start];
      if(x>(long)BASE) x /= BASE;
      if(y>(long)BASE) y %= BASE;
      qhat = (DATATYPE) x;
      rhat = (DATATYPE) y;

      bool badRhat = false;
      do
      {
        x = (long)qhat * (long)V.TheNumber[V.Start+1];
        y = (long)BASE*(long)rhat + (long)U.TheNumber[U.End-j-n+1];

        if(qhat==BASE || x > y)
        {
          qhat --;
          rhat += V.TheNumber[V.Start];
          if(rhat<BASE) badRhat = true;
          else badRhat = false;
        }
        else break;
      }while(badRhat);

      // `x' Will act as Carry in the next loop
      x = 0;
      temp = 0;
      for(i=0;i<=n;i++)
      {
        if(V.End>=i) temp = (long)qhat*(long)V.TheNumber[V.End-i] + temp;
        y = (long)U.TheNumber[U.End-j-i] - temp%BASE - x;
        temp /= BASE;
        if(y < 0)
        {
          U.TheNumber[U.End-j-i] = (DATATYPE)(y+BASE);
          x = 1;
        }
        else
        {
          U.TheNumber[U.End-j-i]  = (DATATYPE)y;
          x = 0;
        }
      }
      // if(x) U.TheNumber[U.Start+j+i] --;

      Q.TheNumber[Q.End-j] = qhat;

      if(x)
      {
        Q.TheNumber[Q.End-j] --;
        // `x' Will act as Carry in the next loop
        x = 0;
        for(i=0;i<=n;i++)
        {
          y = (long)U.TheNumber[U.End-j-i] + x;
          if(V.End>=i) y += (long)V.TheNumber[V.End-i];
          U.TheNumber[U.End-j-i] = (DATATYPE)(y % BASE);
          x = y / BASE;
        }
        U.TheNumber[U.End-j-i] = (DATATYPE)x;
      }
    }

    U.TrimZeros();
    DATATYPE _t;
    if(skipRemainder==false)
      R = U.DivideAndRemainder(d,_t,true);
    Q.TrimZeros();

    return Q;
  }

  // Front end for Divide and Remainder
  // Performs the validity and sign check
  BigInteger& DivideAndRemainder(BigInteger const& U, BigInteger const& V,BigInteger& R,bool skipRemainder=false)
  {
    if(V.isZero())
      throw logic_error (DumpString ("DivideAndRemainder (BigInteger/BigInteger)",BigMathDIVIDEBYZERO));

    if(U.isZero())
    {
      R = *new BigInteger();
      return *new BigInteger();
    }

    int cmp = U.UnsignedCompareTo(V);
    if(cmp==0)
    {
      R = *new BigInteger();
      BigInteger& W = *new BigInteger(1l);
      if(U.isNegative!=V.isNegative) W.isNegative = true;
      return W;
    }
    else if(cmp<0)
    {
      R = *new BigInteger(U);
      if(U.isNegative!=V.isNegative) R.isNegative = true;
      return *new BigInteger();
    }
    BigInteger& ret = U.DivideAndRemainder(V,R,skipRemainder);
    if(U.isNegative!=V.isNegative) ret.isNegative = true;
    return ret;
  }

  // Front end for Divide and Remainder
  // Performs the validity and sign check
  BigInteger& DivideAndRemainder(BigInteger const& U, DATATYPE const& V,DATATYPE& R,bool skipRemainder=false)
  {
    if(V==0)
      throw logic_error ( DumpString ("DivideAndRemainder (BigInteger/DATATYPE)",BigMathDIVIDEBYZERO) );

    if(U.isZero())
    {
      R = 0;
      return *new BigInteger();
    }

    int cmp = 1;
    if(U.Digits()==1)
    {
        if(U.TheNumber[U.Start]<V) cmp = -1;
        else if(U.TheNumber[U.Start]>V) cmp = 1;
        else cmp = 0;
    }
    if(cmp==0)
    {
      R = 0;
      return *new BigInteger(1l);
    }
    else if(cmp<0)
    {
      R = U.TheNumber[U.Start];
      return *new BigInteger();
    }
    BigInteger& ret = U.DivideAndRemainder(V,R,skipRemainder);
    // if(U.isNegative!=(V<0)) ret.isNegative = true;
    return ret;
  }

  // Division operator
  BigInteger& operator/(BigInteger const& N1, BigInteger const& N2)
  {
    BigInteger& R = *new BigInteger();
    return DivideAndRemainder(N1,N2,R,true);
  }

  // Division operator
  BigInteger& operator/(BigInteger const& U, DATATYPE const& V)
  {
    DATATYPE R;
    return DivideAndRemainder(U,V,R,true);
  }

  // Division operator
  BigInteger& operator/(DATATYPE const& U, BigInteger const& V)
  {
    if(V.Digits()==1 && U>V.TheNumber[V.Start])
    {
      return *new BigInteger(U/V.TheNumber[V.Start]);
    }
    return *new BigInteger();
  }

  // Modulus operator
  BigInteger& operator%(BigInteger const& N1,BigInteger const& N2)
  {
    BigInteger& R = *new BigInteger();
    DivideAndRemainder(N1,N2,R);
    return R;
  }

  // Modulus operator
  BigInteger& operator%(BigInteger const& U, DATATYPE const& V)
  {
    DATATYPE R;
    DivideAndRemainder(U,V,R);
    return *new BigInteger(R);
  }

  // Modulus operator
  BigInteger& operator%(DATATYPE const& U, BigInteger const& V)
  {
    if(V.Digits()==1 && U>V.TheNumber[V.Start])
    {
      return *new BigInteger(U%V.TheNumber[V.Start]);
    }
    return *new BigInteger();
  }

  // Assignment Operator
  BigInteger& BigInteger::operator=(BigInteger const&arg)
  {
    Start = 0;
    End = arg.Digits() - 1;
    delete [] TheNumber;
    TheNumber = new DATATYPE [arg.Digits()];

    datacopy(arg,arg.Digits());
    isNegative = arg.isNegative;
    return *this;
  }

  // Inserter
  ostream& operator<<(ostream& stream,  BigInteger const& out)
  {
    if(out.isNegative==true && out.isZero()==false) stream << '-';
    stream << out.TheNumber[out.Start];
    for(SizeT i=out.Start+1;i<=out.End;i++)
    {
      stream.width(4);
      stream.fill('0');
      stream << out.TheNumber[i];
    }

    return stream;
  }

  // Extracter
  istream& operator>>(istream& stream, BigInteger& in)
  {
    SizeT SIZE = 500;
    char *data = new char[SIZE];
    // if(data==0) Dump("Extractor operator",BigMathMEM);
    SizeT i = 0;
    int input;
    bool isNegative = false;
    stream >> ws;
    input = stream.get();
    if(input=='-') isNegative = true;
    else if(input=='+') isNegative = false;
    else stream.putback(input);

    while(true)
    {
      input = stream.get();
      if(isdigit(input))
        data[i++] = input;
      else
      {
        stream.putback(input);
        break;
      }
      if(i>=SIZE)
      {
        SIZE += SIZE;
        char *p = new char [SIZE];
        // if(p==0) Dump("Extractor operator",BigMathMEM);
        strcpy(p,data);
        delete [] data;
        data = p;
      }
    }
    data[i] = 0;
    in = *new BigInteger(data);
    if(in.isZero()==false)
        in.isNegative = isNegative;
    return stream;
  }

  // Inserts the version information into the output stream
  ostream& BigIntegerVersion(ostream& out)
  {
    out << BigIntPROGRAMNAME << " (Version "<< BigIntMajorVersion
      << "." << BigIntMinorVersion << "." << BigIntRevision << ")";
    return out;
  }

  // Inserts the author information into the output stream
  ostream& BigIntegerAuthor(ostream& out)
  {
    out << "Author: S. M. Mahbub Murshed" <<
        endl << "mailto: suman@bttb.net.bd";
    return out;
  }

  // Inserts the about information into the output stream
  ostream& BigIntegerAbout(ostream& out)
  {
    out << BigIntegerVersion << endl << BigIntegerAuthor << endl;
    return out;
  }

  // Returns a string containing version information
  string& BigIntegerVersionString()
  {
    char out[100];
    ostrstream str(out,sizeof(out));
    str << BigIntegerVersion;
    return *new string(out);
  }

  // Converts `this' to a string representation
  string& BigInteger::toString()const
  {
    const int DIGITS = Digits()*4;
    char *R = new char[DIGITS+2];
    ostrstream ostr(R,DIGITS);
    ostr << *this;
    return *new string(R);
  }

  // Converts `this' to equivalent int value
  int BigInteger::toInt()
  {
    return (int)toLong();
  }

  // Converts `this' to equivalent 32 bit long value
  long BigInteger::toLong()
  {
    long r = TheNumber[End];
    if(Digits()>1) r += BASE * TheNumber[End-1] ;
    if(Digits()>2) r += BASE*BASE*(TheNumber[End-2]%100);
    return r;
  }

  // Postfix Increment , that is *this++
  BigInteger& BigInteger::operator++()
  {
    BigInteger& ONE = *new BigInteger(1l);
    *this = *this+ONE;
    return *this;
  }

  // Prefix Increment , that is ++*this
  BigInteger& BigInteger::operator++(int notused)
  {
    BigInteger one(1l);
    BigInteger& Ret = *new BigInteger(*this);
    *this = *this+one;
    return Ret;
  }

  // Postfix Decrement , that is *this--
  BigInteger& BigInteger::operator--()
  {
    BigInteger one(1l);
    *this = *this-one;
    return *this;
  }

  // Pretfix Increment , that is --*this
  BigInteger& BigInteger::operator--(int notused)
  {
    BigInteger one(1l);
    BigInteger& Ret = *new BigInteger(*this);
    *this = *this-one;
    return Ret;
  }

  // Negation, returns -*this
  BigInteger& BigInteger::operator-()
  {
    this->isNegative = this->isNegative==true?false:true;
    return *this;
  }

  DATATYPE& BigInteger::operator[](unsigned int pos) const
  {
      if(pos<Start || pos>End)
          throw domain_error ( DumpString("operator[]", BigMathDomain) );

      return TheNumber[pos];
  }

  // Left Shift
  // To be checked
  BigInteger& BigInteger::operator<<(SizeT b)
  {
    SizeT i = (SizeT)(b / LOG10BASE);
    b %= LOG10BASE;
    while(b--) TheNumber[Digits()-1] *= 10;

    if(i>0)
    {
      DATATYPE *temp = new DATATYPE[Digits()+i];
      for(b=0;b<Digits();b++)
        temp[b] = TheNumber[b];
      for(b=0;b<i; b++)
        temp[Digits()+b] = 0;
      delete [] TheNumber;
      TheNumber = temp;
      End += i-1;
    }
    return *this;
  }

  // Right Shift
  BigInteger& BigInteger::operator>>(SizeT b)
  {
    SizeT i = (SizeT)(b / LOG10BASE);
    b %= LOG10BASE;
    End -= i;
    while(b--)
    {
      DATATYPE f = 0,l;
      for(i=Start;i<=End;i++)
      {
        l = TheNumber[i]%10;
        TheNumber[i] = f*BASE + TheNumber[i]/10;
        f = l;
      }
      if(TheNumber[Start]==0)
        Start--;
    }
    return *this;
  }

  // Makes `this' BigInteger value to absolute
  void BigInteger::abs()
    { isNegative = false; }

  // Returns new BigInteger value which is absolute
  // copy of `arg'
  BigInteger& abs(BigInteger& arg)
  {
      BigInteger& ret = *new BigInteger(arg);
      ret.isNegative = false;
      return ret;
  }

  void Dump(char const* s,enum BigMathERROR e)
  {
    cerr << BigIntegerVersion << endl;
    cerr << "Exception: " << BigIntErrDes[e-1] << endl;
    cerr << "In function: " << s  << endl;
    cerr << "Error Code: " << e << endl;
    exit(e);
  }

  string& DumpString (char const* s,enum BigMathERROR e)
  {
    char *R = new char[256];
    ostrstream ostr(R,255);
    ostr << BigIntegerVersion << endl;
    ostr << "Exception: " << BigIntErrDes[e-1] << endl;
    ostr << "In function: " << s  << endl;
    ostr << "Error Code: " << e << endl;
    return *new string(R);
  }

  bool operator==(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)==0; }

  bool operator!=(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)!=0; }

  bool operator>=(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)>=0; }

  bool operator<=(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)<=0; }

  bool operator>(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)>0; }

  bool operator<(BigInteger const& a, BigInteger const& b)
  { return a.CompareTo(b)<0; }
}

/* Demo: UVa 10430 */
using namespace BigMath;
int main()
{
    long T,N;
    char Tc[10];

    printf("Dear GOD, Pardon Me\n");
    int First = 0;

    while(scanf("%ld %ld",&T,&N)!=EOF)
    {
        if(T==-1 && N==-1) break;

        if(First) printf("\n");
        else First = 1;

        BigInteger X(1),K(T);
        long BigT = T;

        for(T=1;T<N;T++)
        {
            X = X + K;
            K = K.Multiply(BigT);
        }

        cout << "X = " << X << endl;
        cout << "K = " << K << endl;
    }

  return 0;
}

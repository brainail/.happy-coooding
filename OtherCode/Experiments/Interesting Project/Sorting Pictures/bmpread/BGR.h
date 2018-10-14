#ifndef _BGR_h_
#define _BGR_h_

class BGR {
public:
	typedef unsigned char T;
public:
	T	b, g, r;
public:
	BGR(T _b = T(), T _g = T(), T _r = T())
		: b(_b), g(_g), r(_r) { }
	BGR(const BGR & rhs)
		: b(rhs.b), g(rhs.g), r(rhs.r) { }

	BGR & operator = (const BGR & rhs) 
		{ b = rhs.b; g = rhs.g; r = rhs.r; return *this; }

	bool operator == (const BGR & rhs) const
		{ return (b == rhs.b && g == rhs.g && r == rhs.r); }
	bool operator != (const BGR & rhs) const
		{ return (b != rhs.b || g != rhs.g || r != rhs.r); }
	BGR & operator += (const BGR & rhs) { 
		b += rhs.b;
		g += rhs.g;
		r += rhs.r;
		return * this;
	}
	BGR & operator -= (const BGR & rhs) { 
		b -= rhs.b;
		g -= rhs.g;
		r -= rhs.r;
		return * this;
	}
	BGR & operator *= (T c) {
		b *= c;
		g *= c;
		r *= c;
		return * this;
	}
	BGR & operator /= (T c) {
		b /= c;
		g /= c;
		r /= c;
		return * this;
	}

	bool is_black() const
		{ return b==0 && g==0 && r==0; }

	friend BGR operator + (const BGR & lhs, const BGR & rhs) {
		BGR res(lhs);
		res += rhs;
		return res;
	}
	friend BGR operator - (const BGR & lhs, const BGR & rhs) {
		BGR res(lhs);
		res -= rhs;
		return res;
	}
	friend BGR operator - (const BGR & c)
		{ return BGR()-c; }
	friend BGR operator * (const BGR & lhs, T c) {
		BGR res(lhs);
		res *= c;
		return res;
	}
	friend BGR operator * (T c, const BGR & lhs) {
		BGR res(lhs);
		res *= c;
		return res;
	}
	friend BGR operator / (const BGR & lhs, T c) {
		BGR res(lhs);
		res /= c;
		return res;
	}
	friend bool operator < (const BGR & lhs, const BGR & rhs) {
		return 
			(lhs.r < rhs.r || lhs.r == rhs.r &&
				(lhs.g < rhs.g || lhs.g == rhs.g &&
					lhs.b < rhs.b));
	}
};

#endif //_BGR_h_

#ifndef _BGRimage_h_
#define _BGRimage_h_

#include "BGR.h"
#include <vector>
#include <algorithm>

enum order_type { bottom_up, top_down };

inline order_type flip(order_type o)
	{ return order_type(1-o); }

class image {
public:
	typedef BGR T;
	typedef T elem_type;
	typedef unsigned size_type;
private:
	typedef unsigned char byte;
	byte *			_data;
	bool			_owner;
	size_type		_width;
	size_type		_height;
	size_type		_alignment;
	order_type		_order;
	size_type		_scansize;
	size_type		_bytes;
	std::vector<T*>	_scans;
private:
	void update_scans() {
		_scans.resize(_height);
		unsigned int n = 0;
		if (_order == bottom_up) {
			 std::vector<T *>::reverse_iterator it;
			for (it = _scans.rbegin(); it != _scans.rend(); ++it)
				* it = reinterpret_cast<T *>(_data + (n++) * _scansize);
		} else {
			 std::vector<T *>::iterator it;
			for (it = _scans.begin(); it != _scans.end(); ++it)
				* it = reinterpret_cast<T *>(_data + (n++) * _scansize);
		}
	}
	void recalc(size_type w, size_type h, size_type a) {
		_width = w;
		_height = h;
		_alignment = a;
		_scansize = _width * sizeof(T);
		if (_alignment > 1)
			if ((_scansize % _alignment) != 0)
				_scansize = (_scansize / _alignment + 1) * _alignment;
		_bytes = _scansize * _height;
	}
public:
	image(size_type w = 0, size_type h = 0, size_type a = 4)
		: _data(0), _owner(true), _width(0), _height(0), _alignment(1), _order(top_down), _scansize(0), _bytes(0)
		{ resize(w, h, a); }
	image(void * data, size_type w = 0, size_type h = 0, size_type a = 4)
		: _data(0), _owner(true), _width(0), _height(0), _alignment(1), _order(top_down), _scansize(0), _bytes(0)
		{ attach(data, w, h, a); }
	image(const image & i) 
		: _data(0), _owner(true), _width(0), _height(0), _alignment(1), _order(top_down), _scansize(0), _bytes(0)
		{ operator = (i); }
	~image() 
		{ clear(); }
	size_type bytes() const
		{ return _bytes; }
	size_type scansize() const
		{ return _scansize; }
	size_type width() const 
		{ return _width; }
	size_type height() const
		{ return _height; }
	size_type size() const
		{ return _width * _height; }
	size_type alignment() const
		{ return _alignment; }
	order_type order() const
		{ return _order; }
	const void * data() const
		{ return _data; }
	void * data() 
		{ return _data; }
	bool empty() const
		{ return _data == 0; }
	T * scan(size_type y)
		{ return _scans[y]; }
	const T * scan(size_type y) const
		{ return _scans[y]; }
	const T & operator () (size_type x, size_type y) const
		{ return _scans[y][x]; }
	T & operator () (size_type x, size_type y)
		{ return _scans[y][x]; }
public:
	image & operator = (const image & rhs) {
		resize(rhs.width(), rhs.height());
		if (scansize() == rhs.scansize() && order() == rhs.order())
			memcpy(data(), rhs.data(), bytes());
		else
			for (unsigned int n = 0; n < _scans.size(); ++n)
				memcpy(_scans[n], rhs._scans[n], sizeof(T) * width());
		return * this;                                                                                
	}
	void resize(size_type w, size_type h, size_type a = 4) {
		if (a == 0)
			a = _alignment;
		if (!_owner || w != _width || h != _height || a != _alignment) {
			size_type old_bytes = _bytes;	
			std::vector<T*> old_scans(_scans);
			byte * old_data = _data;
			bool copy_data = (_data != 0 && w == _width && h == _height);
			recalc(w, h, a);
			if (_bytes != old_bytes)
				_data = _bytes != 0 ? new byte[_bytes] : 0;
			update_scans();
			if (copy_data)
				for (unsigned int n = 0; n < _scans.size(); ++n)
					memcpy(_scans[n], old_scans[n], sizeof(T) * _width);
			if (_owner && old_data != 0 && old_data != _data)
				delete [] old_data;
			_owner = true;
		}
	}
	void clear() {
		if (_owner)
			resize(0, 0);
		else 
			detach();
	}
	void attach(void * data, size_type w, size_type h, size_type a = 4) {
		if (a == 0)
			a = _alignment;
		if (_owner)
			resize(0, 0);
		if (data != _data || w != _width || h != _height || a != _alignment) {
			recalc(w, h, a);
			_data = reinterpret_cast<byte *>(data);
			update_scans();
			_owner = false;
		}
	}
	void take(void * data, size_type w, size_type h, size_type a = 4) {
		attach(data, w, h, a);
		_owner = true;
	}
	void * detach() { 
		void * data = _data;
		recalc(0, 0, 0);
		_data = 0;
		_scans.clear();
		return data;
	}
	void alignment(size_type a) {
		if (_owner)
			resize(_width, _height, a);
		else
			attach(_data, _width, _height, a);
	}
	void order(order_type o) {
		if (o != _order) {
			_order = o;
			update_scans();
		}
	}
	void flip_order() {
		_order = ::flip(_order);
		update_scans();
	}
	void flip() {
		size_type src, dest; //count = _width * sizeof(T);
		for (src = 0, dest = _height - 1; src < dest; ++src, --dest) {
			//why memcpy, it's too slow? 
			//because we may avoid copy with flip_order(), 
			//but we are not going to change ordering 
			std::swap_ranges(_scans[src], _scans[src] + _width, _scans[dest]);
		}
	}	
	void swap(image &i) {
		std::swap(_data, i._data);
		std::swap(_owner, i._owner);
		std::swap(_width, i._width);
		std::swap(_height, i._height);
		std::swap(_alignment, i._alignment);
		std::swap(_order, i._order);
		std::swap(_scansize, i._scansize);
		std::swap(_bytes, i._bytes);
		_scans.swap(i._scans);
	}
};

#endif //_BGRimage_h_

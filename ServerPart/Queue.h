#pragma once
template <class T>
class Queue
{
private:
	T* _data;
	size_t _size;
	size_t _firstInd;
	size_t _lastInd;
	size_t _countElem;
public:
	Queue(size_t size = 10) : _size(size) {
		_data = new T[_size];
		_firstInd = 0;
		_lastInd = 0;
		_countElem = 0;
	}
	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;
	bool Push(const T& elem) {
		if (!IsFull()) {
			_data[_lastInd] = elem;
			_lastInd = (_lastInd + 1) % _size;
			_countElem++;
			return true;
		}
		return false;
	}
	void PriorityPush(const T& elem) {

	}
	T Pop() {
		const T& elem = _data[_firstInd];
		_firstInd = (_firstInd + 1) % _size;
		_countElem--;
		return elem;
	}
	bool IsEmpty() const{
		return _countElem == 0;
	}
	bool IsFull() const{
		return _countElem == _size;
	}
};


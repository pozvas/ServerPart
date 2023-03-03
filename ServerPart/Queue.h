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
	// 0 - elem 0
	bool PriorityPush(const T& elem) {
		if (!IsFull()) {
			int i;
			if (_countElem) {
				i = _lastInd - 1;
				while (i != _firstInd - 1) {
					if (i < 0) i = _size - 1;
					if (elem > _data[i]) {
						_data[(i + 1) % _size] = _data[i];
						i--;
					}
					else {
						break;
					}
				}
				i++;
			}
			else
				i = 0;
			_data[i] = elem;
			_lastInd = (_lastInd + 1) % _size;
			_countElem++;
			return true;
		}
		return false;
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


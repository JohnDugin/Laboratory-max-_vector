#include <cassert>
#include "Vector.h"

//ЗАДАЧА-------------------------------------------------------------
Vector sortedSquares(const Vector &vec, bool strategy) {
    Vector vector;
    if (strategy) {
        int i = 0;
        Vector vc;
        while (vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for (; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushBack(a);
            } else if (vec[i] > vc[j]) {
                a = vc[j] * vc[j];
                vector.pushBack(a);
                j++;
            } else {
                a = vc[j] * vc[j];
                vector.pushBack(a);
                vector.pushBack(a);
                j++;
            }
        }
        for (; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushBack(a);
        }
        for (; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushBack(a);
        }
    } else {
        int i = 0;
        Vector vc;
        while (vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for (; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushFront(a);
            } else if (vec[i] > vc[j]) {
                a = vc[j] * vc[j];
                vector.pushFront(a);
                j++;
            } else {
                a = vc[j] * vc[j];
                vector.pushFront(a);
                vector.pushFront(a);
                j++;
            }
        }
        for (; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushFront(a);
        }
        for (; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushFront(a);
        }
    }
    return vector;
}
//ЗАДАЧА-------------------------------------------------------------


//КОНСТРУКТОРЫ и ДИСТРУКТОР------------------------------------------
Vector::Vector(size_t size, ResizeStrategy strategy, float coef) {
    _size = 0;
    _capacity = 0;
    this->reserve(size);
    _cf = coef;
    _rStrategy = strategy;
}

Vector::Vector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    _cf = coef;
    _size = 0;
    _capacity = 1;
    _data = nullptr;
    for (int i = 0; i < size; i++)
        this->pushBack(value);
    _rStrategy = strategy;
}

Vector::Vector(const Vector &copy) {
    _cf = copy._cf;
    _size = 0;
    if (_size != 0)
        delete[] _data;
    _capacity = 1;
    for (int i = 0; i < copy._size; i++)
        this->pushBack(copy[i]);
    _rStrategy = copy._rStrategy;
}

Vector &Vector::operator=(const Vector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;
    _data = copy._data;
    _rStrategy = copy._rStrategy;
    _cf = copy._cf;
    return *this;
}

Vector::~Vector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
    _cf = 0;
}


//функции GET--------------------------------------------------------
size_t Vector::capacity() const {
    return _capacity;
}

size_t Vector::size() const {
    return _size;
}

ValueType* Vector::begin(){
    return _data;
}

ValueType* Vector::end(){
    return _data + _size;
}

float Vector::loadFactor() {
    if (_rStrategy == ResizeStrategy::Multiplicative) {
        if ((_size / _capacity) >= 1) {
            _capacity *= _cf;
            float k = _capacity;
            return k;
        } else if ((_size / _capacity) < 1 / (_cf * _cf)) {
            int a = _capacity / _cf;
            float k = _capacity / _cf;
            if (a >= _size && a != 0)
                return k;
            return _capacity;
        } else {
            return _size;
        }
    } else{
        if ((_size / _capacity) >= 1) {
            _capacity += _cf;
            float k = _capacity + _cf;
            return k;
        } else if (_size < _capacity) {
            int a = _capacity - _cf;
            float k = _capacity - _cf;
            if (a >= _size && a != 0)
                return k;
            return _capacity;
        } else {
            return _size;
        }
    }
}


//перегрузка = ------------------------------------------------------
ValueType &Vector::operator[](const size_t i) const {
    return _data[i];
}


//функции PUSH и INSERT----------------------------------------------
void Vector::pushBack(const ValueType &value) {
    resize(_size + 1);
    _data[_size - 1] = value;
}

void Vector::pushFront(const ValueType &value) {
    ValueType *newData = new ValueType[_size + 1];
    for (int i = 1; i < _size + 1; ++i) {
        newData[i] = _data[i-1];
    }
    newData[0] = value;
    delete [] _data;
    _capacity = _size + 1;
    _size = _size + 1;
    _data = newData;
}

void Vector::insert(const size_t index, const ValueType &value) {
    if (index < 0 || index > _size)
        assert(index < 0 || index >= _size);
    else if (index == 0) {
        pushFront(value);
    } else if (index == _size) {
        pushBack(value);
    } else if (index < _size) {
        if (loadFactor())
            reserve(loadFactor());
        ValueType a1, a2;
        a1 = _data[index];
        _data[index] = value;
        for (int i = index; i < _size - 1; i++) {
            a2 = _data[i + 1];
            _data[i + 1] = a1;
            a1 = a2;
        }
        _data[_size] = a1;
        _size++;
    } else {
        pushBack(value);
    }
}

void Vector::insert(const size_t index, const Vector &vector) {
    for (int i = 0; i < vector._size; i++) {
        this->insert(index + i, vector[i]);
    }
}


//POP BACK-----------------------------------------------------------
void Vector::popBack() {
    _data[_size - 1] = NULL;
    _size--;
    resize(_size);
}


//ERASE--------------------------------------------------------------
void Vector::erase(const size_t index) {
    if (index < 0)
        assert(index < 0);
    if (index < _size) {
        for (int i = index; i < _size; i++)
            _data[i] = _data[i + 1];
        _size--;
        resize(_size);
    }
}

void Vector::erase(const size_t index, const size_t len) {
    if (index < 0)
        assert(index < 0);
    else if (index < this->_size) {
        for (int i = 0; i < len; i++) {
            erase(index);
        }
    }
}


//функция RESERVE----------------------------------------------------
void Vector::reserve(const size_t capacity) {
    _capacity = (_capacity == 0) ? 1 : _capacity;
    if (_capacity < capacity)
        _capacity = capacity;
    if (capacity == 0)
        _data = new ValueType[_capacity];
    else {
        ValueType *newData = new ValueType[_capacity];
        for (int i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        if(_size != 0)
            delete[] _data;
        _data = newData;
    }
}


//функция FIND-------------------------------------------------------
long long int Vector::find(const ValueType &value, bool isBegin) const {
    if (isBegin == true) {
        for (int i = 0; i < this->_size; i++) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    } else {
        for (int i = this->_size - 1; i > 0; i--) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    }
    return -1;
}


//функция RESIZE-----------------------------------------------------
void Vector::resize(const size_t size, const ValueType dflt) {
    if (size > this->_size) {
        reserve(size);
        for (int i = this->_size; i < size; i++) {
            _data[i] = dflt;
            _size++;
        }
        this->_capacity = size;
    } else {
        ValueType *new_data = new ValueType[size + 1];
        for (int i = 0; i < size; ++i) {
            new_data[i] = _data[i];
        }
        delete[] this->_data;
        this->_data = new_data;
        this->_capacity = size + 1;
        this->_size = size;
    }
}


//функция CLEAR------------------------------------------------------
void Vector::clear() {
    erase(0, this->_size);
}


//функция PRINT------------------------------------------------------
void Vector::print() {
    std::cout << "size: " << this->_size << "\n";
    std::cout << "capacity: " << this->_capacity << "\n";
    for (int i = 0; i < this->_size; i++)
        std::cout << "[" << i << "] - " << this->_data[i] << "\n";
    std::cout << "\n";
}



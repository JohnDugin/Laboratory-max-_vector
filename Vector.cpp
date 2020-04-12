#include <cassert>
#include "Vector.h"

//ЗАДАЧА-------------------------------------------------------------
Vector sortedSquares(const Vector& vec, bool strategy){
    Vector vector;
    if (strategy){
        int i = 0;
        Vector vc;
        while(vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for(; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushBack(a);
            }
            else if(vec[i] > vc[j]){
                a = vc[j] * vc[j];
                vector.pushBack(a);
                j++;
            }
            else {
                a = vc[j] * vc[j];
                vector.pushBack(a);
                vector.pushBack(a);
                j++;
            }
        }
        for(; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushBack(a);
        }
        for(; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushBack(a);
        }
    }
    else{
        int i = 0;
        Vector vc;
        while(vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for(; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushFront(a);
            }
            else if(vec[i] > vc[j]){
                a = vc[j] * vc[j];
                vector.pushFront(a);
                j++;
            }
            else{
                a = vc[j] * vc[j];
                vector.pushFront(a);
                vector.pushFront(a);
                j++;
            }
        }
        for(; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushFront(a);
        }
        for(; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushFront(a);
        }
    }
    return vector;
}
//ЗАДАЧА-------------------------------------------------------------


//КОНСТРУКТОРЫ и ДИСТРУКТОР------------------------------------------
Vector::Vector(size_t size, ResizeStrategy strategy,float coef){
    _size = size;
    _capacity = 1;
    _data = nullptr;
    _coef = coef;
    _strategy = strategy;
}

Vector::Vector(size_t size, ValueType value, ResizeStrategy strategy, float coef){
    _coef = coef;
    _size = 0;
    _capacity = 1;
    for(int i = 0; i < size; i++)
        this->pushBack(value);
    _strategy = strategy;
}

Vector::Vector(const Vector& copy){
    _coef = copy._coef;
    delete [] _data;
    _size = 0;
    _capacity = 1;
    for (int i = 0; i < copy._size; i++)
        this->pushBack(copy[i]);
}

Vector& Vector::operator=(const Vector& copy){
    _size = copy._size;
    _capacity = copy._capacity;
    _data = copy._data;
    _strategy = copy._strategy;
    return *this;
}

Vector::~Vector(){
    delete [] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}


//функции GET--------------------------------------------------------
size_t Vector::capacity() const{
    return _capacity;
}

size_t Vector::size() const{
    return  _size;
}

float Vector::loadFactor(){
    if(_size/_capacity > 1){
        _capacity * _coef;
        float k = _capacity * _coef;
        return k;
    }
    else if(_size/_capacity < 1/(_coef * _coef)){
        _capacity / _coef;
        float k = _capacity / _coef;
        return k;
    }
}


//перегрузка = ------------------------------------------------------
ValueType& Vector::operator[] (const size_t i) const{
    return _data[i];
}


//функции PUSH и INSERT----------------------------------------------
void Vector::pushBack(const ValueType& value){
    if(_capacity == 1)
        reserve(2);
    else if(_size + 2 > _capacity)
        reserve(_capacity * _coef);
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value){
    if(_capacity == 1)
        reserve(2);
    else if(_size + 2 > _capacity)
        reserve(_capacity * _coef);
    int a = _data[0], b;
    for(int i = 1; i < _size + 1; i++) {
        b = _data[i];
        _data[i] = a;
        a = b;
    }
    _data[0] = value;
    _size++;
}

void Vector::insert(const size_t index, const ValueType& value){
    if(index < 0 || index >= _size)
        assert(index<0 || index >= _size);
    else if(index == 0){
        pushFront(value);
    }
    else if(index == _size - 1){
        pushBack(value);
    }
    else if (index < _size) {
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
    }
    else {
        pushBack(value);
    }
}

void Vector::insert(const size_t index, const Vector& vector){
    for(int i = 0; i < vector._size; i++){
        this->insert(index + i, vector[i]);
    }
}


//POP BACK-----------------------------------------------------------
void Vector::popBack(){
    _data[_size - 1] = NULL;
    _size--;
}


//ERASE--------------------------------------------------------------
void Vector::erase( const size_t index){
    if(index < 0)
        assert(index < 0);
    if (index < _size) {
        for (int i = index; i < _size; i++)
            _data[i] = _data[i + 1];
        _size--;
    }
}

void Vector::erase( const size_t index, const size_t len){
    if(index < 0)
        assert(index < 0);
    else if (index < this->_size) {
        for(int i = 0; i < len; i++){
            erase(index);
        }
    }
}


//функция RESERVE----------------------------------------------------
void Vector::reserve(const size_t capacity){
    _capacity = (_capacity == 0) ? 1 : _capacity;
    while (_capacity < capacity)
        _capacity ++;
    if (_data == 0)
        _data = new ValueType[_capacity];
    else {
        ValueType* newData = new ValueType[_capacity];
        memcpy(newData, _data, _size * sizeof(ValueType));
        delete [] _data;
        _data = newData;
    }
}

long long int Vector::find(const ValueType& value, bool isBegin) const {
    if (isBegin == true) {
        for (int i = 0; i < this->_capacity; i++) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    }
    else {
        for (int i = this->_capacity; i > 0; i--) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    }
    return -1;
}

void Vector::resize(const size_t size, const ValueType){
    if(size > this->_size) {
        reserve(size);
        ValueType * new_data = new ValueType[size];
        memcpy(new_data, this->_data, size * sizeof(ValueType));
        delete[] this->_data;
        this->_data = new_data;
        for(int i = this->_size; i < size; i++){
            _data[i] = 0;
        }
        this->_size = size;
    }
    else{
        ValueType * new_data = new ValueType[size];
        memcpy(new_data, this->_data, size * sizeof(ValueType));
        delete[] this->_data;
        this->_data = new_data;
        this->_size = size;
    }
}

void Vector::clear(){
    erase(0, this->_size);
}

void Vector::print(){
    std::cout << "size: " << this->_size << "\n";
    std::cout << "capacity: " << this->_capacity << "\n";
    for(int i = 0 ; i < this->_size; i++)
        std::cout << "[" << i << "] - " << this->_data[i] << "\n";
    std::cout << "\n";
}



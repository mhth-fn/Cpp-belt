#pragma once

#include <algorithm>
#include <bits/node_handle.h>
#include <cstdlib>
#include <iostream>


// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector() : data(nullptr), end_(nullptr), capacity_(0){};

  explicit SimpleVector(size_t size){
		capacity_ = 2 * size;
	 	data = new T[capacity_];
		end_ = data + size;
	}

	SimpleVector (const SimpleVector <T>& other) 
	: data(new T[other.capacity_]), end_(data + other.Size()),
	capacity_(other.capacity_)
	{
		std::copy(other.begin(), other.end(), begin());
	}

	void operator=(const SimpleVector<T> other){
		if (data != other.data){
			if (capacity_ < other.capacity_) capacity_ = other.capacity_;
			delete[] data;
			data = new T[other.capacity_];
			end_ = data + other.Size();
			for (size_t i = 0; i != other.Size(); ++i){
				data[i] = other[i];
			}
		}
	}

  ~SimpleVector(){
		delete[] data;
	}

  const T& operator[](size_t index) const{
		return data[index];
	}

  T& operator[](size_t index){
		return data[index];
	}

  T* begin() const{
		return data;
	}
  T* end() const{
		return end_;
	}


  T* begin(){
		return data;
	}
  T* end(){
		return end_;
	}

  size_t Size() const{
		return end_ - data;
	}
  size_t Capacity() const{
		return capacity_;
	}
  void PushBack(const T& value){
		if (Size() >= Capacity()){
			if (Size() == 0){
				capacity_ = 1;
			} else{
				capacity_ *= 2;
			}
			T* new_data = new T[capacity_];
			size_t size = Size();
			std::copy(data, end_, new_data);	
			std::swap(data, new_data);
			delete[] new_data;
			end_ = data + size;
		}
		data[Size()] = value;
		++end_;
	}

private:
  // Добавьте поля для хранения данных вектора
	T* data;
	T* end_;
	size_t capacity_;
};

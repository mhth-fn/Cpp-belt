#pragma once

#include <stdexcept>
#include <array> 

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : 
		size_(a_size){
		if (a_size > N){
			throw invalid_argument("Argument size more then capacity");
		}	
	}

  T& operator[](size_t index){
		return data[index];
	}
  const T& operator[](size_t index) const{
		return data[index];
	}

  auto begin() const {
		return &data[0];
	}
  auto end() const {
		return &data[size_];
	}
  auto begin(){
		return &data[0];
	}
  auto end(){
		return &data[size_];
	}

  size_t Size() const{
		return size_;
	}
  size_t Capacity() const{
		return N;
	}

  void PushBack(const T& value){
		if (size_ < N){
			data[size_] = value;
			++size_;
		} else {
			throw overflow_error("Cant pushback, becouse size_ = capacity");
		}
	}

  T PopBack(){
		if (size_ != 0){
			return data[--size_];
		} else {
			throw underflow_error("Vector is empty");
		}
	}

private:
	array<T, N> data;	
	size_t size_;
};


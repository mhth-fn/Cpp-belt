#include <cstdint>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector(){
		data_ = nullptr;
		size_ = capacity_ = 0;
	}
  explicit SimpleVector(size_t size) : 
	data_(new T[size]), size_(size), capacity_(size){
	}
  ~SimpleVector(){
		delete[] data_;
	}

	SimpleVector(const SimpleVector& rhs) : 
		size_(rhs.size_), capacity_(rhs.capacity_), data_(new T[rhs.capacity_]){
		copy(rhs.begin(), rhs.end(), begin());
	}

  void operator = (const SimpleVector& rhs){
		if (data_ != nullptr){
			delete[] data_;
		}
		data_ = new T[rhs.capacity_];
		capacity_ = rhs.capacity_;
		size_ = rhs.size_;
		copy(rhs.begin(), rhs.end(), begin());
	}
  T& operator[](size_t index){
		return data_[index];
	}
  T* begin() const{
		return data_;
	}
  T* end() const{
		return data_ + size_;
	}


  T* begin(){
		return data_;
	}
  T* end(){
		return data_ + size_;
	}

  size_t Size() const{
		return size_;
	}
  size_t Capacity() const{
		return capacity_;
	}

  void PushBack(T value){
		if (size_ >= capacity_){
			if (size_ == 0){
				capacity_ = 1;
			} else {
				capacity_ *= 2;
			}
			T* tmp = new T[capacity_];
			std::copy(make_move_iterator(begin()), 
				make_move_iterator(end()), tmp);
			delete[] data_;
			data_ = tmp;
		}
		data_[size_] = std::move(value);
		++size_;
	}
	
  // При необходимости перегрузите
  // существующие публичные методы

private:
  // Добавьте сюда поля
	T* data_;
	size_t size_;
	size_t capacity_;
};

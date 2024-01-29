#include <vector>
#include <stdexcept>
using namespace std;

#define SIZE (front_.size() + back_.size())

template <typename T>
class Deque{
public:
	Deque() = default;
	//tested
	bool Empty() const{
		return front_.empty() && back_.empty();
	}
	//tested
	size_t Size() const{
		return front_.size() + back_.size();
	}

	T& operator[](size_t index){
		if (InFront(index)){
			size_t front_index = front_.size() - 1 - index;
			return front_[front_index];	
		} else if (InBack(index)){
			size_t back_index = index - front_.size();
			return back_[back_index];
		} else {
			throw out_of_range("Out of range");
		}

	}
	const T& operator[](size_t index) const{
		if (InFront(index)){
			size_t front_index = front_.size() - 1 - index;
			return front_[front_index];	
			} else if (InBack(index)) {
			size_t back_index = index - front_.size();
			return back_[back_index];
		} else {
			throw out_of_range("Out of range");
		}
	}

	T& At(size_t index){
		if (index >= SIZE){
			throw out_of_range("index >= size");
		} else if (InFront(index)){
			return front_.at(front_.size() - 1 - index);	
		} else {
			size_t back_index = index - front_.size();
			return back_.at(back_index);
		}
	}

	const T& At(size_t index) const{
		if (index >= SIZE){
			throw out_of_range("index >= size");
		} else if (InFront(index)){
			return front_.at(front_.size() - 1 - index);	
		} else {
			size_t back_index = index - front_.size();
			return back_.at(back_index);
		}
	}
	//tested
	T& Front(){
		if (front_.empty()){
			return back_[0];
		} else{
			return front_.back();
		}
	}
	//tested;
	const T& Front() const{
		if (front_.empty()){
			return back_[0];
		} else{
			return front_.back();
		}
	}
	//tested;
	T& Back(){
		if (back_.empty()){
			return front_[0];
		} else {
			return back_.back();	
		}
	}
	//tested;
	const T& Back() const{
		if (back_.empty()){
			return front_[0];
		} else{
			return back_.back();
		}
	}
	//tested;
	void PushFront(const T& item){
		front_.push_back(item);
	}
	//tested
	void PushBack(const T& item){
		back_.push_back(item);
	}

private:
	vector<T> front_, back_;

	bool InFront(size_t index){
		return front_.size() > index; 
	}

	bool InBack(size_t index){
		return back_.size() > (index - front_.size());
	}
};


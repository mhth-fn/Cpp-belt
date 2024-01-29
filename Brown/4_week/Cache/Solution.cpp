#include "Common.h"

#include <list>
#include <algorithm>
#include <mutex>
#include <iostream>

using namespace std;
class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) : unpacker(books_unpacker),
    max_memory_(settings.max_memory) {
    // реализуйте метод
  }
  // size_t GetMemory() override{
  //   return memory_;
  // }
  BookPtr GetBook(const string& book_name) override {
    // реализуйте метод
    BookPtr res = SearchInCache(book_name);
    if (res == nullptr){
      res = unpacker->UnpackBook(book_name);
      size_t book_size = res->GetContent().size();
      if (book_size <= max_memory_) {
        FreeCache(book_size);
        PushCache(res, book_size);
      }
    }
    return move(res);
  }

private:
  void FreeCache(const size_t book_size){
    lock_guard<mutex> g(m);
    while (max_memory_ < memory_ + book_size && !cache_.empty()){
      memory_ -= cache_.back()->GetContent().size();
      cache_.pop_back();
    }
  }

  void PushCache(BookPtr book, const size_t book_size){
    lock_guard<mutex> g(m);
    cache_.push_front(book);
    memory_ += book_size;
  }
  
  BookPtr UpdatePriority(list<BookPtr>::iterator it){
    auto book = move(*it);
    cache_.erase(it);
    cache_.push_front(move(book));
    return cache_.front();
  }

  BookPtr SearchInCache(const string& book_name){
    lock_guard<mutex> g(m);
    auto it = find_if(begin(cache_), end(cache_), [&book_name](const BookPtr lhs){
      return lhs->GetName() == book_name;
    });
    if (it != end(cache_)) {
      if (it != begin(cache_)){
        return UpdatePriority(it);
      } else {
        return *begin(cache_);
      }
    }
    return nullptr;
  }

private:
  mutex m;

  list<BookPtr> cache_;
  shared_ptr<IBooksUnpacker> unpacker;
  const size_t max_memory_;
  size_t memory_ = 0;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  // реализуйте функцию
  return make_unique<LruCache>(move(books_unpacker), settings);
}

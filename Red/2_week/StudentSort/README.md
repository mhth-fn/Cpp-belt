## Задание по программированию  «Сортировка студентов по рейтингу»

 

В данной задаче необходимо оптимизировать код, использующийся для  сортировки студентов по рейтингу. Данные каждого студента находятся в  структуре Student, объявленной в файле student.h. Рейтинг студента  записан в поле rating:

```
struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};
```

 

Для сортировки студентов по рейтингу используется функция сравнения,  возвращающая true, если рейтинг студента first выше рейтинга студента  second.

```
bool Compare(Student first, Student second) {
  return first.Less(second);
}
```

 

Было выявлено, что эта функция является узким местом процесса сортировки, и именно её нужно оптимизировать.

Пришлите на проверку файл, содержащий оптимизированную версию функции Compare. Если ваша реализация будет недостаточно эффективной, то  решение не уложится в ограничение по времени.

- [student](https://stepik.org/media/attachments/lesson/285350/uNZEiWQZEeiaEg6Thd1Wwg_b9344290641911e8af492fae745a22e6_student.h)
- [sort_students](https://stepik.org/media/attachments/lesson/285350/zW9nEnu0EeiC-BK3XY5K_A_cdc464d07bb411e88b6339ac39854c06_sort_students.cpp)

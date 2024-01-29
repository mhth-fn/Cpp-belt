#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

using namespace std;
void CheckAndDelete(TasksInfo& in){
	TasksInfo buf = in;
	for (auto& item : buf){
		if (item.second == 0){
			in.erase(item.first);
		}
	}
}

TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const{
		return tasks_for_person.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person){
		++tasks_for_person[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
	  const string& person, int task_count){
		TasksInfo update, not_update;
		for (TaskStatus eit = TaskStatus::NEW; eit != TaskStatus::DONE; eit = Next(eit)){
			update[Next(eit)] = min(task_count, tasks_for_person[person][eit]);
			task_count -= update[Next(eit)];
			not_update[eit] = tasks_for_person[person][eit] - update[Next(eit)];
    		tasks_for_person[person][eit] += update[eit] - update[Next(eit)];
		}
		tasks_for_person[person][TaskStatus::DONE] += update[TaskStatus::DONE];
		CheckAndDelete(update);
		CheckAndDelete(not_update);
		return tie(update, not_update);
	}

private:
	map<std::string, TasksInfo> tasks_for_person;


};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
	  ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
	  ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	  ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
	tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
	  tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
	  tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}

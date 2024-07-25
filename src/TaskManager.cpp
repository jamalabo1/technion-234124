//
// Created by jamal on 20/07/2024.
//
#include <functional>
#include "TaskManager.h"


//bool operator<()

// List implementation

TaskManager::PersonList::PersonList() : list(nullptr), count(0) {

}

TaskManager::PersonList::~PersonList() {
    delete[] list;
}

bool TaskManager::PersonList::exists(const string &name) {
    for (Person &person: *this) {
        if (person.getName() == name) return true;
    }
    return false;
}

Person &TaskManager::PersonList::findPersonByName(const string &name) {
    for (Person &person: *this) {
        if (person.getName() == name) return person;
    }

    throw std::runtime_error("person does not exist");
}

void TaskManager::PersonList::insert(Person &person) {
    Person *newList = new Person[count + 1];

    for (int i = 0; i < count; i++) {
        newList[i] = list[i];
    }
    newList[count] = person;

    if (count > 0) {
        delete[] list;
    }
    list = newList;
    count++;
}

int TaskManager::PersonList::size() const {
    return count;
}

TaskManager::PersonList::Iterator TaskManager::PersonList::begin() const {
    return {this, 0};
}

TaskManager::PersonList::Iterator TaskManager::PersonList::end() const {
    return {this, size()};
}

TaskManager::PersonList::Iterator::Iterator(const TaskManager::PersonList *list, int index) : list(list),
                                                                                              currentIndex(index) {

}

TaskManager::PersonList::Iterator &TaskManager::PersonList::Iterator::operator++() {
    currentIndex++;
    return *this;
}

bool TaskManager::PersonList::Iterator::operator!=(const TaskManager::PersonList::Iterator &it) {
    return it.currentIndex != currentIndex;
}

Person &TaskManager::PersonList::Iterator::operator*() {
    return list->list[currentIndex];
}


// End list implementation

TaskManager::TaskManager() = default;

void TaskManager::assignTask(const string &personName, const Task &task) {

    bool personExists = persons.exists(personName);
    if (!personExists && persons.size() >= MAX_PERSONS) {
        throw std::runtime_error("");
    }
    Task copy = task;
    copy.setId(nextTaskId++);

    if (personExists) {
        Person &person = persons.findPersonByName(personName);
        person.assignTask(copy);
    } else {
        Person person(personName);
        person.assignTask(copy);
        persons.insert(person);
    }
}

void TaskManager::completeTask(const string &personName) {
    Person &person = persons.findPersonByName(personName);

    person.completeTask();
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    PriorityBumpHandler handler(type, priority);

    for (Person &person: persons) {
        SortedList<Task> personTasks = person.getTasks();

        person.setTasks(personTasks.apply(handler));
    }
}

void TaskManager::printAllEmployees() const {
    for (const Person &person: persons) {
        std::cout << person << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> tasks = getTasks().filter([type](const Task &task) {
        return task.getType() == type;
    });

    for (const Task &task: tasks) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> tasks = getTasks();

    for (const Task &task: tasks) {
        std::cout << task << std::endl;
    }
}

SortedList<Task> TaskManager::getTasks() const {
    SortedList<Task> tasks;
    for (const Person &person: persons) {
        for (const Task &task: person.getTasks()) {
            tasks.insert(task);
        }
    }
    return tasks;
}


Task TaskManager::PriorityBumpHandler::operator()(const Task &task) {
    bool matchType = task.getType() == type;

    if (matchType) {
        auto newTask = Task(task.getPriority() + priority, task.getType(), task.getDescription());
        newTask.setId(task.getId());
        return newTask;
    }
    return task;
}

TaskManager::PriorityBumpHandler::PriorityBumpHandler(const TaskType &type, const int &priority) : type(type),
                                                                                                   priority(priority) {

}

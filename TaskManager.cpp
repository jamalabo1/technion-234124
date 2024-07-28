//
// Created by jamal on 20/07/2024.
//
#include "TaskManager.h"

// List implementation

TaskManager::PersonList::PersonList() : list(nullptr), count(0) {

}

TaskManager::PersonList::~PersonList() {
    delete[] list;
}

Person *TaskManager::PersonList::findPersonByName(const string &name) {
    for (Person &person: *this) {
        if (person.getName() == name) return &person;
    }

    return nullptr;
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
    // returns a pointer to the requested person if exists.
    Person *pPerson = persons.findPersonByName(personName);
    if (pPerson == nullptr && persons.size() >= MAX_PERSONS) {
        throw std::runtime_error("maximum capacity has been reached");
    }
    // since all types in the class are clr types, default copy ctr by value can be used.
    Task copy(task);
    copy.setId(nextTaskId++);

    if (pPerson != nullptr) {
        pPerson->assignTask(copy);
    } else {
        Person person(personName);
        person.assignTask(copy);
        persons.insert(person);
    }
}

void TaskManager::completeTask(const string &personName) {
    Person *person = persons.findPersonByName(personName);

    if (person == nullptr) {
        std::cout << "No tasks assigned to this person" << std::endl;
        return;
    }

    person->completeTask();
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
    TaskFilterByTypeHandler handler(type);

    SortedList<Task> tasks = getAllTasks().filter(handler);

    for (const Task &task: tasks) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> tasks = getAllTasks();

    for (const Task &task: tasks) {
        std::cout << task << std::endl;
    }
}

SortedList<Task> TaskManager::getAllTasks() const {
    SortedList<Task> tasks;
    for (const Person &person: persons) {
        for (const Task &task: person.getTasks()) {
            tasks.insert(task);
        }
    }
    return tasks;
}


TaskManager::PriorityBumpHandler::PriorityBumpHandler(const TaskType &type, const int &priority) : type(type),
                                                                                                   priority(priority) {
}

Task TaskManager::PriorityBumpHandler::operator()(const Task &task) {
    bool matchType = task.getType() == type;

    if (matchType) {
        Task newTask = Task(task.getPriority() + priority, task.getType(), task.getDescription());
        newTask.setId(task.getId());
        return newTask;
    }
    return task;
}

TaskManager::TaskFilterByTypeHandler::TaskFilterByTypeHandler(TaskType type) : type(type) {

}

bool TaskManager::TaskFilterByTypeHandler::operator()(const Task &task) {
    return task.getType() == type;
}
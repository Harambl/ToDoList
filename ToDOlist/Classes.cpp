#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>

#include "Classes.h"



Task::Task(const QString& desc, bool comp, const QString& final) : Description(desc), complete(comp), finalday(final) {}

QString Task::getDesc() const {
    return Description;
}

QString Task::getDay() const {
    return finalday;
}

bool Task::isCompleted() const {
    return complete;
}

void Task::setDescription(const QString& desc) {
    Description = desc;
}

void Task::setCompleted(bool comp) {
    complete = comp;
}

void Task::setDay(const QString& final){
    finalday = final;
}

QString Task::toString() const {
    return QString("%1").arg(Description);
}



void TDList::AddTask(const QString& desc) {
    tasks.append(Task(desc));
}

void TDList::DelTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.removeAt(index);
    }
}

void TDList::editTaskDescription(int index, const QString& newdesc) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].setDescription(newdesc);
    }
}

void TDList::saveList() {
    QSettings settings("P1tch_z3r0", "To-Do List");
    settings.beginWriteArray("Tasks");
    for (int i = 0; i < tasks.size(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("desc", tasks[i].getDesc());
        settings.setValue("completed", tasks[i].isCompleted());
    }
    settings.endArray();
}

void TDList::CompleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].setCompleted(!tasks[index].isCompleted());
    }
}

void TDList::loadFromSettings() {
    QSettings settings("P1tch_z3r0", "To-Do List");
    int size = settings.beginReadArray("Tasks");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString desc = settings.value("desc").toString();
        bool completed = settings.value("completed").toBool();
        tasks.append(Task(desc, completed));
    }
    settings.endArray();
}

const QList<Task>& TDList::getTasks() const {
    return tasks;
}

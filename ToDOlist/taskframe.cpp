#include "taskframe.h"

TaskFrame::TaskFrame(const QString& Desc, bool comp, const QDate& fday): Description(Desc), complete(comp), finalday(fday) {}

QString TaskFrame::getDescription() const {
    return Description;
}

QDate TaskFrame::getDate() const{
    return finalday;
}

bool TaskFrame::isCompleted() const {
    return complete;
}

void TaskFrame::setDescription(const QString& desc) {
    Description = desc;
}

void TaskFrame::setDate(const QDate& day){
    finalday = day;
}

void TaskFrame::setCompleted(bool comp) {
    complete = comp;
}

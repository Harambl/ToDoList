#include "taskframe.h"

TaskFrame::TaskFrame(const QString& Desc, bool comp): Description(Desc), complete(comp) {}

QString TaskFrame::getDescription() const {
    return Description;
}

bool TaskFrame::isCompleted() const {
    return complete;
}

void TaskFrame::setDescription(const QString& desc) {
    Description = desc;
}

void TaskFrame::setCompleted(bool comp) {
    complete = comp;
}

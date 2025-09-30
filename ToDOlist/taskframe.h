#ifndef TASKFRAME_H
#define TASKFRAME_H

#include <QObject>
#include <QString>

class TaskFrame : public QObject
{
    Q_OBJECT

private:
    QString Description;
    bool complete;
    int number;

public:
    TaskFrame(const QString& Desc = "", bool complete = false);
    explicit TaskFrame(QObject *parent = nullptr);

    QString getDescription() const;
    bool isCompleted() const;

    void setDescription(const QString& desc);
    void setCompleted(bool comp);

};

#endif // TASKFRAME_H

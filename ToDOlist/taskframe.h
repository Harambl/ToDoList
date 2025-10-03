#ifndef TASKFRAME_H
#define TASKFRAME_H

#include <QObject>
#include <QString>
#include <QDate>

class TaskFrame {

private:
    QString Description;
    bool complete;
    int number;
    QDate finalday;

public:
    TaskFrame(const QString& Desc = "", bool complete = false, const QDate& day = QDate::currentDate());
    explicit TaskFrame(QObject *parent = nullptr);

    QString getDescription() const;
    QDate getDate() const;
    bool isCompleted() const;

    void setDescription(const QString& desc);
    void setCompleted(bool comp);
    void setDate(const QDate& day);

};

#endif // TASKFRAME_H

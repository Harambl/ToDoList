#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include "taskframe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTaskFrame();
    void DelTaskFrame(int index);
    void SetCompleted(int index);

    const QList<TaskFrame>& getTasks() const;

private:
    QList<TaskFrame> tasks;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

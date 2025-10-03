#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QTextEdit>
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

    void closeEvent(QCloseEvent* event);

    void createTaskFrame();
    void DelTaskFrame(int index);
    void SetCompleted(int index);
    void setDescription(int index, const QString& desc);
    void updateTaskList();

    void saveList();
    void loadfromList();

    const QList<TaskFrame>& getTasks() const;

private:
    QList<TaskFrame> tasks;

    Ui::MainWindow *ui;

    void deleteLayout(QLayout *layout);

private slots:
    void on_AddButton_clicked();
};


#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QCloseEvent>
#include <QMessageBox>
#include <QShortcut>
#include <QCheckBox>
#include <QTextEdit>
#include <QLabel>
#include <QDateEdit>
#include <QSettings>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::loadfromList();
    MainWindow::updateTaskList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    MainWindow::saveList();
    event->accept();
}


void MainWindow::saveList() {
    QSettings settings("Harambl", "TDList");
    settings.beginWriteArray("Tasks");
    for (int i = 0; i < tasks.size(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("desc", tasks[i].getDescription());
        settings.setValue("completed", tasks[i].isCompleted());
        settings.setValue("date", tasks[i].getDate());
    }
    settings.endArray();
}

void MainWindow::loadfromList() {
    QSettings settings("Harambl", "TDList");
    int size = settings.beginReadArray("Tasks");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString desc = settings.value("desc").toString();
        bool completed = settings.value("completed").toBool();
        QDate finalday = settings.value("date").toDate();
        tasks.append(TaskFrame(desc, completed, finalday));
    }
    settings.endArray();
}



void MainWindow::DelTaskFrame(int index) {
    tasks.removeAt(index);

    QLayoutItem *item = ui->TaskLayout->takeAt(index);
    if (item) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        else if (QLayout *layout = item->layout()) {
            deleteLayout(layout);
        }
        delete item;
    }

    updateTaskList();
}

void MainWindow::deleteLayout(QLayout *layout) {
    if (!layout) return;

    while (QLayoutItem *item = layout->takeAt(0)) {
        if (item->widget()) {
            delete item->widget();
        } else if (item->layout()) {
            deleteLayout(item->layout());
        }
        delete item;
    }
    delete layout;
}



void MainWindow::SetCompleted(int index){
    tasks[index].setCompleted(!tasks[index].isCompleted());
}

void MainWindow::setDescription(int index, const QString& desc){
    tasks[index].setDescription(desc);
}

void MainWindow::updateTaskList(){
    QLayoutItem *child;
    while ((child = ui->TaskLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (int i = 0; i < tasks.size(); i++) {
        QString stri = QString::number(i+1);

        QWidget* TWidget = new QWidget;
        TWidget->setStyleSheet("background-color: peru; border-radius: 6px; padding: 5px;");
        TWidget->setMaximumHeight(80);

        QLineEdit* Task = new QLineEdit(tasks[i].getDescription());
        Task->setStyleSheet("background-color: tan;");
        Task->setMaximumHeight(60);
        connect(Task, &QLineEdit::returnPressed, this, [this, i, Task]{
            MainWindow::setDescription(i, Task->text().trimmed());
        });

        QLabel* NumLabel = new QLabel();
        NumLabel->setText(stri);

        QDateEdit *dueDateEdit = new QDateEdit;
        dueDateEdit->setCalendarPopup(true);
        dueDateEdit->setMinimumDate(tasks[i].getDate());
        connect(dueDateEdit, &QDateEdit::dateChanged, this, [this, i](const QDate& newDate) {
            tasks[i].setDate(newDate);
        });

        QHBoxLayout* NumLayout = new QHBoxLayout(TWidget);
        NumLabel->setStyleSheet("font-weight: bold;");

        QPushButton* delButton = new QPushButton( "Удалить");
        delButton->setStyleSheet("background-color: maroon; color: white;");
        connect(delButton, &QPushButton::clicked, this, [this, i]{
            MainWindow::DelTaskFrame(i);

        });
        QCheckBox* compButton = new QCheckBox;
        compButton->setChecked(tasks[i].isCompleted());
        connect(compButton, &QCheckBox::toggled, this, [this, i](){
            MainWindow::SetCompleted(i);
        });

        NumLayout->addWidget(NumLabel);

        NumLayout->addWidget(Task);
        NumLayout->addWidget(dueDateEdit);

        NumLayout->addWidget(delButton);
        NumLayout->addWidget(compButton);

        ui->TaskLayout->addWidget(TWidget);

    }
}


void MainWindow::createTaskFrame(){
    tasks.append(TaskFrame("Новая задача"));
    long long number = tasks.size();
    QString strnumber = QString::number(number);

    QWidget* TWidget = new QWidget;
    TWidget->setStyleSheet("background-color: peru; border-radius: 6px; padding: 5px;");
    TWidget->setMaximumHeight(80);

    QLineEdit* Task = new QLineEdit(tasks[number-1].getDescription());
    Task->setStyleSheet("background-color: tan;");
    Task->setMaximumHeight(60);
    connect(Task, &QLineEdit::returnPressed, this, [this, number, Task]{
        MainWindow::setDescription(number - 1, Task->text().trimmed());
    });

    QLabel* NumLabel = new QLabel();
    NumLabel->setText(strnumber);

    QDateEdit *dueDateEdit = new QDateEdit;
    dueDateEdit->setCalendarPopup(true);
    dueDateEdit->setMinimumDate(QDate::currentDate());
    connect(dueDateEdit, &QDateEdit::dateChanged, this, [this, number](const QDate& newDate) {
        tasks[number - 1].setDate(newDate);
    });

    QHBoxLayout* NumLayout = new QHBoxLayout(TWidget);
    NumLabel->setStyleSheet("font-weight: bold;");

    QPushButton* delButton = new QPushButton( "Удалить");
    delButton->setStyleSheet("background-color: maroon; color: white;");
    connect(delButton, &QPushButton::clicked, this, [this, number]{
        MainWindow::DelTaskFrame(number - 1);

    });
    QCheckBox* compButton = new QCheckBox;
    connect(compButton, &QCheckBox::toggled, this, [this, number](){
        MainWindow::SetCompleted(number - 1);
    });

    NumLayout->addWidget(NumLabel);

    NumLayout->addWidget(Task);
    NumLayout->addWidget(dueDateEdit);

    NumLayout->addWidget(delButton);
    NumLayout->addWidget(compButton);

    ui->TaskLayout->addWidget(TWidget);

}

void MainWindow::on_AddButton_clicked(){
    MainWindow::createTaskFrame();
}


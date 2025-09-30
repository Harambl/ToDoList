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

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DelTaskFrame(int index){

}

void MainWindow::SetCompleted(int index){
    tasks[index].setCompleted(!tasks[index].isCompleted());

}

void MainWindow::createTaskFrame(){
    tasks.append(TaskFrame("Новая задача"));
    long long number = tasks.size();
    QString strnumber = QString::number(number);

    QFrame* TFrame = new QFrame;
    TFrame->setStyleSheet("Peru");

    QTextEdit* Task = new QTextEdit(tasks[number-1].getDescription());
    Task->setTextBackgroundColor("Tan");

    QLabel* NumLabel = new QLabel;
    NumLabel->setText(strnumber);

    QDateEdit *dueDateEdit = new QDateEdit;
    dueDateEdit->setCalendarPopup(true);
    dueDateEdit->setMinimumDate(QDate::currentDate());;

    QVBoxLayout* MainLayout = new QVBoxLayout();
    QVBoxLayout* NumLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();
    QHBoxLayout* btnLayout = new QHBoxLayout();

    QPushButton* delButton = new QPushButton("Удалить");
    delButton->setStyleSheet("Maroon");
    connect(delButton, &QPushButton::clicked, this, [this, number]{
        MainWindow::DelTaskFrame(number - 1);
    });
    QCheckBox* compButton = new QCheckBox("Не выполнено");
    connect(compButton, &QCheckBox::toggled, this, [this, number](){
        MainWindow::SetCompleted(number - 1);
    });

    MainLayout->addWidget(TFrame);
    MainLayout->addLayout(NumLayout);
    MainLayout->addLayout(inputLayout);
    MainLayout->addLayout(btnLayout);

    NumLayout->addWidget(NumLabel);

    inputLayout->addWidget(Task);
    inputLayout->addWidget(dueDateEdit);

    btnLayout->addWidget(delButton);
    btnLayout->addWidget(compButton);

    ui->TaskLayout->addLayout(MainLayout);

}

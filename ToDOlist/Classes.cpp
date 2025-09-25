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


class Task{
private:
    QString Description;
    bool complete;
public:
    Task (const QString& desc = "", bool comp = false) : Description(desc), complete(comp){

    }
    void SetDescription(const QString& desc) { Description = desc; }
    void SetCompletion(const bool comp) { complete = comp; }

    QString GetDescription() { return Description; }
    bool IsComplete() { return complete; }

    QString ToString() const {
        return QString("%1 %2").arg(complete ? "[V]" : "[]").arg(Description);
    }
};

#ifndef MESSAGELISTWIDGET_H
#define MESSAGELISTWIDGET_H

#include <QWidget>

namespace Ui {
class messagelistwidget;
}

class messagelistwidget : public QWidget
{
    Q_OBJECT

public:
    explicit messagelistwidget(QWidget *parent = nullptr);
    ~messagelistwidget();
signals:
    void setUserList();

private slots:
    void on_userlistButton_clicked();

private:
    Ui::messagelistwidget *ui;
};

#endif // MESSAGELISTWIDGET_H

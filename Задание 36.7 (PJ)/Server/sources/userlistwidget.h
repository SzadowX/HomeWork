#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QWidget>

namespace Ui {
class userlistwidget;
}

class userlistwidget : public QWidget
{
    Q_OBJECT

public:
    explicit userlistwidget(QWidget *parent = nullptr);
    ~userlistwidget();
signals:
    void setMessageList();
    void disconnect(QString username);
    void ban(QString username);
    void unban(QString username);

private slots:
    void on_messageButton_clicked();

    void on_banButton_clicked();

    void on_disconnectButton_clicked();

    void on_unbanButton_clicked();

private:
    Ui::userlistwidget *ui;
};

#endif // USERLISTWIDGET_H

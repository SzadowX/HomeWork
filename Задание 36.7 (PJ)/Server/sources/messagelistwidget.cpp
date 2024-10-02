#include "messagelistwidget.h"
#include "ui_messagelistwidget.h"

messagelistwidget::messagelistwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::messagelistwidget)
{
    ui->setupUi(this);
}

messagelistwidget::~messagelistwidget()
{
    delete ui;
}

void messagelistwidget::on_userlistButton_clicked()
{
    emit setUserList();
}


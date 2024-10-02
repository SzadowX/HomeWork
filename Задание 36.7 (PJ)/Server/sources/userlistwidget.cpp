#include "userlistwidget.h"
#include "ui_userlistwidget.h"

userlistwidget::userlistwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userlistwidget)
{
    ui->setupUi(this);
}

userlistwidget::~userlistwidget()
{
    delete ui;
}

void userlistwidget::on_messageButton_clicked()
{
    emit setMessageList();
}


void userlistwidget::on_banButton_clicked()
{
    emit ban(ui->userlistWidget->currentItem()->text());
}


void userlistwidget::on_disconnectButton_clicked()
{
    emit disconnect(ui->userlistWidget->currentItem()->text());
}


void userlistwidget::on_unbanButton_clicked()
{
    emit unban(ui->userlistWidget->currentIndex()->text());
}


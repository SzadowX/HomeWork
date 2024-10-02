#include "startscreen.h"
#include "ui_startscreen.h"
#include <QMessageBox>

StartScreen::StartScreen(std::shared_ptr<Database> dbPtr,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUI(this);

    if(dbPtr)
        m_dbPtr = dbPtr;
    else
        m_dbPtr = make_shared<Database>();

    m_dbPtr->addUser("admin", "admin");
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::on_buttonBox_accepted()
{
    auto userId = m_dbPtr->checkPassword(ui->loginEdit->text().toStdString(),
                                         ui->passwordEdit->text().toStdString());
    if(userId == -1){
        QMessageBox::critical(this, tr("Error"), tr("Password is wrong"));
        return;
    }

    m_userId = userId;
    m_userName = ui->loginEdit->text();
    accept();
}


void StartScreen::on_buttonBox_rejected()
{
    reject();
}

QString StartScreen::userName() const
{
    return m_userName;
}

int StartScreen::userId() const
{
    return m_userId;
}

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>
#include "Database.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<Database> dbPtr = nullptr,
                         QWidget *parent = nullptr);
    ~StartScreen();

    int userId() const;
    QString userName() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::StartScreen *ui;
    int m_userId;
    QString m_userName;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // STARTSCREEN_H

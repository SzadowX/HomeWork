/********************************************************************************
** Form generated from reading UI file 'userlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLISTWIDGET_H
#define UI_USERLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userlistwidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *userlistWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *banButton;
    QPushButton *disconnectButton;
    QPushButton *unbanButton;
    QPushButton *messageButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *userlistwidget)
    {
        if (userlistwidget->objectName().isEmpty())
            userlistwidget->setObjectName("userlistwidget");
        userlistwidget->resize(381, 336);
        horizontalLayout = new QHBoxLayout(userlistwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        userlistWidget = new QListWidget(userlistwidget);
        userlistWidget->setObjectName("userlistWidget");

        horizontalLayout->addWidget(userlistWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        banButton = new QPushButton(userlistwidget);
        banButton->setObjectName("banButton");

        verticalLayout->addWidget(banButton);

        disconnectButton = new QPushButton(userlistwidget);
        disconnectButton->setObjectName("disconnectButton");

        verticalLayout->addWidget(disconnectButton);

        unbanButton = new QPushButton(userlistwidget);
        unbanButton->setObjectName("unbanButton");

        verticalLayout->addWidget(unbanButton);

        messageButton = new QPushButton(userlistwidget);
        messageButton->setObjectName("messageButton");

        verticalLayout->addWidget(messageButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(userlistwidget);

        QMetaObject::connectSlotsByName(userlistwidget);
    } // setupUi

    void retranslateUi(QWidget *userlistwidget)
    {
        userlistwidget->setWindowTitle(QCoreApplication::translate("userlistwidget", "Form", nullptr));
        banButton->setText(QCoreApplication::translate("userlistwidget", "Ban", nullptr));
        disconnectButton->setText(QCoreApplication::translate("userlistwidget", "Disconnect", nullptr));
        unbanButton->setText(QCoreApplication::translate("userlistwidget", "Unban", nullptr));
        messageButton->setText(QCoreApplication::translate("userlistwidget", "Message List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userlistwidget: public Ui_userlistwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLISTWIDGET_H

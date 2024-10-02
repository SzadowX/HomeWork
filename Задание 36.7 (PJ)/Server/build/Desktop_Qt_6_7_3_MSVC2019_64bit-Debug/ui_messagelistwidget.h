/********************************************************************************
** Form generated from reading UI file 'messagelistwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGELISTWIDGET_H
#define UI_MESSAGELISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_messagelistwidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *userlistButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *messagelistwidget)
    {
        if (messagelistwidget->objectName().isEmpty())
            messagelistwidget->setObjectName("messagelistwidget");
        messagelistwidget->resize(388, 284);
        horizontalLayout = new QHBoxLayout(messagelistwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        listWidget = new QListWidget(messagelistwidget);
        listWidget->setObjectName("listWidget");

        horizontalLayout->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        userlistButton = new QPushButton(messagelistwidget);
        userlistButton->setObjectName("userlistButton");

        verticalLayout->addWidget(userlistButton);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(messagelistwidget);

        QMetaObject::connectSlotsByName(messagelistwidget);
    } // setupUi

    void retranslateUi(QWidget *messagelistwidget)
    {
        messagelistwidget->setWindowTitle(QCoreApplication::translate("messagelistwidget", "Form", nullptr));
        userlistButton->setText(QCoreApplication::translate("messagelistwidget", "User List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messagelistwidget: public Ui_messagelistwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGELISTWIDGET_H

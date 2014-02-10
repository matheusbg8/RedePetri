/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created: Thu Jan 9 20:36:08 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLineEdit *textLineEdit;
    QPushButton *sendButton;
    QTextEdit *chatTextEdit;
    QLineEdit *pseudoLineEdit;
    QLabel *socketStateLabel;
    QPushButton *connectButton;
    QLabel *socketStateLabel_2;
    QPushButton *disconnectButton;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(480, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Client->sizePolicy().hasHeightForWidth());
        Client->setSizePolicy(sizePolicy);
        Client->setMinimumSize(QSize(480, 480));
        Client->setMaximumSize(QSize(480, 480));
        textLineEdit = new QLineEdit(Client);
        textLineEdit->setObjectName(QString::fromUtf8("textLineEdit"));
        textLineEdit->setGeometry(QRect(120, 440, 271, 27));
        sendButton = new QPushButton(Client);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(400, 440, 71, 27));
        chatTextEdit = new QTextEdit(Client);
        chatTextEdit->setObjectName(QString::fromUtf8("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(10, 50, 461, 381));
        pseudoLineEdit = new QLineEdit(Client);
        pseudoLineEdit->setObjectName(QString::fromUtf8("pseudoLineEdit"));
        pseudoLineEdit->setGeometry(QRect(10, 440, 101, 27));
        socketStateLabel = new QLabel(Client);
        socketStateLabel->setObjectName(QString::fromUtf8("socketStateLabel"));
        socketStateLabel->setGeometry(QRect(380, 10, 91, 31));
        connectButton = new QPushButton(Client);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(10, 10, 91, 31));
        socketStateLabel_2 = new QLabel(Client);
        socketStateLabel_2->setObjectName(QString::fromUtf8("socketStateLabel_2"));
        socketStateLabel_2->setGeometry(QRect(290, 10, 91, 31));
        disconnectButton = new QPushButton(Client);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));
        disconnectButton->setGeometry(QRect(110, 10, 91, 31));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "QtWebsocket Client Example", 0, QApplication::UnicodeUTF8));
        textLineEdit->setText(QString());
        textLineEdit->setPlaceholderText(QApplication::translate("Client", "message", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("Client", "Send", 0, QApplication::UnicodeUTF8));
        pseudoLineEdit->setText(QString());
        pseudoLineEdit->setPlaceholderText(QApplication::translate("Client", "pseudo", 0, QApplication::UnicodeUTF8));
        socketStateLabel->setText(QApplication::translate("Client", "Unknow", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("Client", "Connect", 0, QApplication::UnicodeUTF8));
        socketStateLabel_2->setText(QApplication::translate("Client", "Socket state:", 0, QApplication::UnicodeUTF8));
        disconnectButton->setText(QApplication::translate("Client", "Disconnect", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H

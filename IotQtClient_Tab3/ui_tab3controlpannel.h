/********************************************************************************
** Form generated from reading UI file 'tab3controlpannel.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB3CONTROLPANNEL_H
#define UI_TAB3CONTROLPANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab3ControlPannel
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pPBPlug;
    QPushButton *pPBLamp;
    QLabel *label;

    void setupUi(QWidget *Tab3ControlPannel)
    {
        if (Tab3ControlPannel->objectName().isEmpty())
            Tab3ControlPannel->setObjectName(QStringLiteral("Tab3ControlPannel"));
        Tab3ControlPannel->resize(556, 357);
        gridLayout = new QGridLayout(Tab3ControlPannel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scrollArea = new QScrollArea(Tab3ControlPannel);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 536, 337));
        pPBPlug = new QPushButton(scrollAreaWidgetContents);
        pPBPlug->setObjectName(QStringLiteral("pPBPlug"));
        pPBPlug->setGeometry(QRect(420, 210, 71, 71));
        QIcon icon;
        icon.addFile(QStringLiteral(":/IotQtClient/Image/plug_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/IotQtClient/Image/plug_on.png"), QSize(), QIcon::Normal, QIcon::On);
        pPBPlug->setIcon(icon);
        pPBPlug->setIconSize(QSize(60, 60));
        pPBPlug->setCheckable(true);
        pPBLamp = new QPushButton(scrollAreaWidgetContents);
        pPBLamp->setObjectName(QStringLiteral("pPBLamp"));
        pPBLamp->setGeometry(QRect(70, 100, 71, 71));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/IotQtClient/Image/light_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/IotQtClient/Image/light_on.png"), QSize(), QIcon::Normal, QIcon::On);
        pPBLamp->setIcon(icon1);
        pPBLamp->setIconSize(QSize(60, 60));
        pPBLamp->setCheckable(true);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 523, 326));
        label->setPixmap(QPixmap(QString::fromUtf8(":/IotQtClient/Image/room.png")));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label->raise();
        pPBPlug->raise();
        pPBLamp->raise();

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(Tab3ControlPannel);

        QMetaObject::connectSlotsByName(Tab3ControlPannel);
    } // setupUi

    void retranslateUi(QWidget *Tab3ControlPannel)
    {
        Tab3ControlPannel->setWindowTitle(QApplication::translate("Tab3ControlPannel", "Form", 0));
        pPBPlug->setText(QString());
        pPBLamp->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tab3ControlPannel: public Ui_Tab3ControlPannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB3CONTROLPANNEL_H

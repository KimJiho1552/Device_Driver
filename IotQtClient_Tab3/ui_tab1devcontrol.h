/********************************************************************************
** Form generated from reading UI file 'tab1devcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB1DEVCONTROL_H
#define UI_TAB1DEVCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab1DevControl
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pPBtimerStart;
    QComboBox *pCBtimerValue;
    QPushButton *pPBappQuit;
    QHBoxLayout *horizontalLayout_2;
    QDial *pDialLed;
    QLCDNumber *pLcdNumberLed;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *pProgressBarLed;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *pCBkey1;
    QCheckBox *pCBkey2;
    QCheckBox *pCBkey3;
    QCheckBox *pCBkey4;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *pCBkey5;
    QCheckBox *pCBkey6;
    QCheckBox *pCBkey7;
    QCheckBox *pCBkey8;
    QLCDNumber *pLcdNumberKey;

    void setupUi(QWidget *Tab1DevControl)
    {
        if (Tab1DevControl->objectName().isEmpty())
            Tab1DevControl->setObjectName(QStringLiteral("Tab1DevControl"));
        Tab1DevControl->resize(414, 267);
        verticalLayout_2 = new QVBoxLayout(Tab1DevControl);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pPBtimerStart = new QPushButton(Tab1DevControl);
        pPBtimerStart->setObjectName(QStringLiteral("pPBtimerStart"));
        pPBtimerStart->setCheckable(true);
        pPBtimerStart->setChecked(false);

        horizontalLayout->addWidget(pPBtimerStart);

        pCBtimerValue = new QComboBox(Tab1DevControl);
        pCBtimerValue->setObjectName(QStringLiteral("pCBtimerValue"));

        horizontalLayout->addWidget(pCBtimerValue);

        pPBappQuit = new QPushButton(Tab1DevControl);
        pPBappQuit->setObjectName(QStringLiteral("pPBappQuit"));

        horizontalLayout->addWidget(pPBappQuit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pDialLed = new QDial(Tab1DevControl);
        pDialLed->setObjectName(QStringLiteral("pDialLed"));
        pDialLed->setMaximum(15);
        pDialLed->setPageStep(3);
        pDialLed->setWrapping(true);
        pDialLed->setNotchesVisible(true);

        horizontalLayout_2->addWidget(pDialLed);

        pLcdNumberLed = new QLCDNumber(Tab1DevControl);
        pLcdNumberLed->setObjectName(QStringLiteral("pLcdNumberLed"));
        pLcdNumberLed->setDigitCount(1);
        pLcdNumberLed->setMode(QLCDNumber::Hex);
        pLcdNumberLed->setSegmentStyle(QLCDNumber::Filled);

        horizontalLayout_2->addWidget(pLcdNumberLed);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pProgressBarLed = new QProgressBar(Tab1DevControl);
        pProgressBarLed->setObjectName(QStringLiteral("pProgressBarLed"));
        pProgressBarLed->setMaximum(15);
        pProgressBarLed->setValue(0);

        horizontalLayout_3->addWidget(pProgressBarLed);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pCBkey1 = new QCheckBox(Tab1DevControl);
        pCBkey1->setObjectName(QStringLiteral("pCBkey1"));

        horizontalLayout_5->addWidget(pCBkey1);

        pCBkey2 = new QCheckBox(Tab1DevControl);
        pCBkey2->setObjectName(QStringLiteral("pCBkey2"));

        horizontalLayout_5->addWidget(pCBkey2);

        pCBkey3 = new QCheckBox(Tab1DevControl);
        pCBkey3->setObjectName(QStringLiteral("pCBkey3"));

        horizontalLayout_5->addWidget(pCBkey3);

        pCBkey4 = new QCheckBox(Tab1DevControl);
        pCBkey4->setObjectName(QStringLiteral("pCBkey4"));

        horizontalLayout_5->addWidget(pCBkey4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pCBkey5 = new QCheckBox(Tab1DevControl);
        pCBkey5->setObjectName(QStringLiteral("pCBkey5"));

        horizontalLayout_6->addWidget(pCBkey5);

        pCBkey6 = new QCheckBox(Tab1DevControl);
        pCBkey6->setObjectName(QStringLiteral("pCBkey6"));

        horizontalLayout_6->addWidget(pCBkey6);

        pCBkey7 = new QCheckBox(Tab1DevControl);
        pCBkey7->setObjectName(QStringLiteral("pCBkey7"));

        horizontalLayout_6->addWidget(pCBkey7);

        pCBkey8 = new QCheckBox(Tab1DevControl);
        pCBkey8->setObjectName(QStringLiteral("pCBkey8"));

        horizontalLayout_6->addWidget(pCBkey8);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_4->addLayout(verticalLayout);

        pLcdNumberKey = new QLCDNumber(Tab1DevControl);
        pLcdNumberKey->setObjectName(QStringLiteral("pLcdNumberKey"));
        pLcdNumberKey->setDigitCount(2);
        pLcdNumberKey->setMode(QLCDNumber::Hex);

        horizontalLayout_4->addWidget(pLcdNumberKey);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 5);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 3);

        retranslateUi(Tab1DevControl);
        QObject::connect(pDialLed, SIGNAL(valueChanged(int)), pLcdNumberLed, SLOT(display(int)));

        QMetaObject::connectSlotsByName(Tab1DevControl);
    } // setupUi

    void retranslateUi(QWidget *Tab1DevControl)
    {
        Tab1DevControl->setWindowTitle(QApplication::translate("Tab1DevControl", "Form", 0));
        pPBtimerStart->setText(QApplication::translate("Tab1DevControl", "TimerStart", 0));
        pCBtimerValue->clear();
        pCBtimerValue->insertItems(0, QStringList()
         << QApplication::translate("Tab1DevControl", "100", 0)
         << QApplication::translate("Tab1DevControl", "500", 0)
         << QApplication::translate("Tab1DevControl", "1000", 0)
         << QApplication::translate("Tab1DevControl", "2000", 0)
        );
        pPBappQuit->setText(QApplication::translate("Tab1DevControl", "Quit", 0));
        pCBkey1->setText(QApplication::translate("Tab1DevControl", "1", 0));
        pCBkey2->setText(QApplication::translate("Tab1DevControl", "2", 0));
        pCBkey3->setText(QApplication::translate("Tab1DevControl", "3", 0));
        pCBkey4->setText(QApplication::translate("Tab1DevControl", "4", 0));
        pCBkey5->setText(QApplication::translate("Tab1DevControl", "5", 0));
        pCBkey6->setText(QApplication::translate("Tab1DevControl", "6", 0));
        pCBkey7->setText(QApplication::translate("Tab1DevControl", "7", 0));
        pCBkey8->setText(QApplication::translate("Tab1DevControl", "8", 0));
    } // retranslateUi

};

namespace Ui {
    class Tab1DevControl: public Ui_Tab1DevControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB1DEVCONTROL_H

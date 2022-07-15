#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <tab1devcontrol.h>
#include <tab2socketclinet.h>
#include <tab3controlpannel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = NULL);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab1DevControl* pTab1DevControl;
    Tab2SocketClinet* pTab2SocketClinet;
    Tab3ControlPannel* pTab3ControlPannel;
};
#endif // MAINWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'HAS_main_GUI.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAS_MAIN_GUI_H
#define UI_HAS_MAIN_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HAS_Main_GUI
{
public:
    QWidget *centralwidget;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuHosbital;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *HAS_Main_GUI)
    {
        if (HAS_Main_GUI->objectName().isEmpty())
            HAS_Main_GUI->setObjectName("HAS_Main_GUI");
        HAS_Main_GUI->resize(838, 532);
        centralwidget = new QWidget(HAS_Main_GUI);
        centralwidget->setObjectName("centralwidget");
        HAS_Main_GUI->setCentralWidget(centralwidget);
        toolBar = new QToolBar(HAS_Main_GUI);
        toolBar->setObjectName("toolBar");
        HAS_Main_GUI->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);
        menuBar = new QMenuBar(HAS_Main_GUI);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 838, 23));
        menuHosbital = new QMenu(menuBar);
        menuHosbital->setObjectName("menuHosbital");
        HAS_Main_GUI->setMenuBar(menuBar);
        toolBar_2 = new QToolBar(HAS_Main_GUI);
        toolBar_2->setObjectName("toolBar_2");
        HAS_Main_GUI->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar_2);

        menuBar->addAction(menuHosbital->menuAction());

        retranslateUi(HAS_Main_GUI);

        QMetaObject::connectSlotsByName(HAS_Main_GUI);
    } // setupUi

    void retranslateUi(QMainWindow *HAS_Main_GUI)
    {
        HAS_Main_GUI->setWindowTitle(QCoreApplication::translate("HAS_Main_GUI", "HAS_Main_GUI", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("HAS_Main_GUI", "toolBar", nullptr));
        menuHosbital->setTitle(QCoreApplication::translate("HAS_Main_GUI", "Hosbital", nullptr));
        toolBar_2->setWindowTitle(QCoreApplication::translate("HAS_Main_GUI", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HAS_Main_GUI: public Ui_HAS_Main_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAS_MAIN_GUI_H

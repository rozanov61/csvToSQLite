/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_CSV;
    QAction *actionOpen_SQLite_Table;
    QAction *actionExit;
    QAction *actionSave_To_SQLite;
    QAction *actionSave_To_CSV;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen;
    QMenu *menuConvert_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(713, 537);
        actionOpen_CSV = new QAction(MainWindow);
        actionOpen_CSV->setObjectName(QStringLiteral("actionOpen_CSV"));
        actionOpen_SQLite_Table = new QAction(MainWindow);
        actionOpen_SQLite_Table->setObjectName(QStringLiteral("actionOpen_SQLite_Table"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave_To_SQLite = new QAction(MainWindow);
        actionSave_To_SQLite->setObjectName(QStringLiteral("actionSave_To_SQLite"));
        actionSave_To_CSV = new QAction(MainWindow);
        actionSave_To_CSV->setObjectName(QStringLiteral("actionSave_To_CSV"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 713, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOpen = new QMenu(menuFile);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        menuConvert_2 = new QMenu(menuFile);
        menuConvert_2->setObjectName(QStringLiteral("menuConvert_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuOpen->menuAction());
        menuFile->addAction(menuConvert_2->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOpen->addAction(actionOpen_CSV);
        menuOpen->addAction(actionOpen_SQLite_Table);
        menuConvert_2->addAction(actionSave_To_CSV);
        menuConvert_2->addAction(actionSave_To_SQLite);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CSV/SQL viewer/saver", Q_NULLPTR));
        actionOpen_CSV->setText(QApplication::translate("MainWindow", "Open CSV...", Q_NULLPTR));
        actionOpen_SQLite_Table->setText(QApplication::translate("MainWindow", "Open SQLite Table...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionSave_To_SQLite->setText(QApplication::translate("MainWindow", "Save To SQLite", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_To_SQLite->setToolTip(QApplication::translate("MainWindow", "Save To SQLite", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_To_CSV->setText(QApplication::translate("MainWindow", "SaveToCSV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_To_CSV->setToolTip(QApplication::translate("MainWindow", "Save To CSV", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        menuConvert_2->setTitle(QApplication::translate("MainWindow", "Convert", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

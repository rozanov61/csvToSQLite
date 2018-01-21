/********************************************************************************
** Form generated from reading UI file 'savetosqldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVETOSQLDIALOG_H
#define UI_SAVETOSQLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SaveToSqlDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *pathLineEdit;
    QPushButton *pushButton;
    QComboBox *tableNameComboBox;
    QLabel *label_2;

    void setupUi(QDialog *SaveToSqlDialog)
    {
        if (SaveToSqlDialog->objectName().isEmpty())
            SaveToSqlDialog->setObjectName(QStringLiteral("SaveToSqlDialog"));
        SaveToSqlDialog->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SaveToSqlDialog->sizePolicy().hasHeightForWidth());
        SaveToSqlDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(SaveToSqlDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(SaveToSqlDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 70, 31, 16));
        pathLineEdit = new QLineEdit(SaveToSqlDialog);
        pathLineEdit->setObjectName(QStringLiteral("pathLineEdit"));
        pathLineEdit->setGeometry(QRect(50, 70, 281, 21));
        pushButton = new QPushButton(SaveToSqlDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(340, 70, 31, 23));
        tableNameComboBox = new QComboBox(SaveToSqlDialog);
        tableNameComboBox->setObjectName(QStringLiteral("tableNameComboBox"));
        tableNameComboBox->setGeometry(QRect(80, 160, 291, 22));
        tableNameComboBox->setEditable(true);
        label_2 = new QLabel(SaveToSqlDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 160, 71, 16));

        retranslateUi(SaveToSqlDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SaveToSqlDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SaveToSqlDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SaveToSqlDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveToSqlDialog)
    {
        SaveToSqlDialog->setWindowTitle(QApplication::translate("SaveToSqlDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SaveToSqlDialog", "Path:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SaveToSqlDialog", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("SaveToSqlDialog", "Table name:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SaveToSqlDialog: public Ui_SaveToSqlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVETOSQLDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *modeSelectorComboBox;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLineEdit *num1LineEdit;
    QLineEdit *num2LineEdit;
    QComboBox *operationComboBox;
    QComboBox *repTypeComboBox;
    QSpinBox *bitWidthSpinBox;
    QPushButton *computeButton;
    QLabel *resultLabel_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *errorLabel;
    QLabel *label_6;
    QWidget *page_2;
    QLineEdit *inputNumberLineEdit;
    QFontComboBox *fromBaseComboBox;
    QFontComboBox *toBaseComboBox;
    QPushButton *convertButton;
    QLabel *resultLabel;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 668);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        modeSelectorComboBox = new QComboBox(centralwidget);
        modeSelectorComboBox->setObjectName("modeSelectorComboBox");
        modeSelectorComboBox->setGeometry(QRect(310, 30, 181, 28));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(160, 80, 461, 521));
        page = new QWidget();
        page->setObjectName("page");
        num1LineEdit = new QLineEdit(page);
        num1LineEdit->setObjectName("num1LineEdit");
        num1LineEdit->setGeometry(QRect(170, 90, 141, 28));
        num2LineEdit = new QLineEdit(page);
        num2LineEdit->setObjectName("num2LineEdit");
        num2LineEdit->setGeometry(QRect(170, 140, 141, 28));
        operationComboBox = new QComboBox(page);
        operationComboBox->setObjectName("operationComboBox");
        operationComboBox->setGeometry(QRect(130, 300, 221, 28));
        repTypeComboBox = new QComboBox(page);
        repTypeComboBox->setObjectName("repTypeComboBox");
        repTypeComboBox->setGeometry(QRect(130, 230, 221, 28));
        bitWidthSpinBox = new QSpinBox(page);
        bitWidthSpinBox->setObjectName("bitWidthSpinBox");
        bitWidthSpinBox->setGeometry(QRect(170, 40, 131, 29));
        computeButton = new QPushButton(page);
        computeButton->setObjectName("computeButton");
        computeButton->setGeometry(QRect(190, 350, 90, 29));
        resultLabel_2 = new QLabel(page);
        resultLabel_2->setObjectName("resultLabel_2");
        resultLabel_2->setGeometry(QRect(140, 390, 191, 51));
        resultLabel_2->setStyleSheet(QString::fromUtf8("resultLabel_2{\n"
"	text-align: center;\n"
"}"));
        resultLabel_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 200, 111, 20));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 270, 81, 20));
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 40, 71, 31));
        errorLabel = new QLabel(page);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(40, 470, 411, 31));
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(80, 400, 63, 20));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        inputNumberLineEdit = new QLineEdit(page_2);
        inputNumberLineEdit->setObjectName("inputNumberLineEdit");
        inputNumberLineEdit->setGeometry(QRect(180, 10, 113, 28));
        fromBaseComboBox = new QFontComboBox(page_2);
        fromBaseComboBox->setObjectName("fromBaseComboBox");
        fromBaseComboBox->setGeometry(QRect(140, 70, 202, 28));
        toBaseComboBox = new QFontComboBox(page_2);
        toBaseComboBox->setObjectName("toBaseComboBox");
        toBaseComboBox->setGeometry(QRect(140, 120, 202, 28));
        convertButton = new QPushButton(page_2);
        convertButton->setObjectName("convertButton");
        convertButton->setGeometry(QRect(200, 170, 90, 29));
        resultLabel = new QLabel(page_2);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(170, 220, 151, 51));
        resultLabel->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(42, 80, 81, 20));
        label_4 = new QLabel(page_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 120, 81, 20));
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        computeButton->setText(QCoreApplication::translate("MainWindow", "Compute", nullptr));
        resultLabel_2->setText(QCoreApplication::translate("MainWindow", "OUTPUT:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Representation:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Operation:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Bit Width:", nullptr));
        errorLabel->setText(QString());
        label_6->setText(QString());
        inputNumberLineEdit->setText(QString());
        convertButton->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        resultLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "From base:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "To base:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

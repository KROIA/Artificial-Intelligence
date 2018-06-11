/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *NetControlFrame;
    QSlider *LeftSpeedSlider;
    QSlider *RightSpeedSlder;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *net_control_toggle_button;
    QLabel *net_control_left_label;
    QLabel *net_control_right_label;
    QSlider *net_control_stepMultiplayer;
    QLabel *label;
    QLabel *tod_label;
    QLabel *activeAnimal_label;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *net_score_label;
    QPushButton *net_control_kill_button;
    QLabel *label_7;
    QLabel *generation_label;
    QPushButton *net_control_speedMultiplayerToOne_button;
    QSlider *net_control_beamLength_slider;
    QLabel *label_15;
    QLabel *net_control_beamLength_label;
    QSlider *net_control_obsticleAmount_slider;
    QLabel *label_16;
    QLabel *net_control_obsticleAmount_label;
    QSlider *net_control_addSpeed_slider;
    QLabel *label_17;
    QLabel *net_control_addSpeed_label;
    QCheckBox *net_control_improve_checkBox;
    QPushButton *net_control_speedMultiplayerTo10_button;
    QPushButton *net_control_speedMultiplayerTo100_button;
    QPushButton *net_control_speedMultiplayerTo30_button;
    QPushButton *net_control_speedMultiplayerTo60_button;
    QLabel *label_19;
    QLabel *ticksPerSecond_label;
    QFrame *NetAdjustFrame;
    QSlider *net_draw_colorMultipliyer_slider;
    QLabel *label_4;
    QSlider *MutationFactor_Slider;
    QLabel *label_8;
    QLabel *MutationFactor_label;
    QSlider *drawNetXDistance_slider;
    QSlider *drawNetYDistance_slider;
    QSlider *drawNeuronSize_slider;
    QSlider *drawConnectionSize_slider;
    QSlider *drawAnimal_slider;
    QLabel *label_9;
    QLabel *drawAnimal_label;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QSlider *robotPathSize_slider;
    QLabel *label_14;
    QLabel *label_18;
    QLabel *MutationDivisor_label;
    QSlider *MutationDivisor_Slider;
    QCheckBox *drawAnimal_checkBox;
    QCheckBox *displayInputValue_checkBox;
    QCheckBox *displayHiddenValue_checkBox;
    QCheckBox *displayOutputValue_checkBox;
    QLabel *label_20;
    QLabel *version_label;
    QPushButton *pushButton;
    QLabel *startPath_label;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1513, 881);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        NetControlFrame = new QFrame(centralWidget);
        NetControlFrame->setObjectName(QStringLiteral("NetControlFrame"));
        NetControlFrame->setGeometry(QRect(1050, 30, 421, 311));
        NetControlFrame->setFrameShape(QFrame::StyledPanel);
        NetControlFrame->setFrameShadow(QFrame::Raised);
        LeftSpeedSlider = new QSlider(NetControlFrame);
        LeftSpeedSlider->setObjectName(QStringLiteral("LeftSpeedSlider"));
        LeftSpeedSlider->setGeometry(QRect(130, 130, 22, 160));
        LeftSpeedSlider->setMinimum(-100);
        LeftSpeedSlider->setMaximum(100);
        LeftSpeedSlider->setOrientation(Qt::Vertical);
        RightSpeedSlder = new QSlider(NetControlFrame);
        RightSpeedSlder->setObjectName(QStringLiteral("RightSpeedSlder"));
        RightSpeedSlder->setGeometry(QRect(162, 130, 20, 160));
        RightSpeedSlder->setMinimum(-100);
        RightSpeedSlder->setMaximum(100);
        RightSpeedSlder->setOrientation(Qt::Vertical);
        label_1 = new QLabel(NetControlFrame);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(170, 100, 41, 21));
        label_2 = new QLabel(NetControlFrame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 100, 31, 21));
        label_2->setLayoutDirection(Qt::RightToLeft);
        label_3 = new QLabel(NetControlFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 50, 61, 16));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);
        net_control_toggle_button = new QPushButton(NetControlFrame);
        net_control_toggle_button->setObjectName(QStringLiteral("net_control_toggle_button"));
        net_control_toggle_button->setGeometry(QRect(10, 10, 75, 31));
        net_control_left_label = new QLabel(NetControlFrame);
        net_control_left_label->setObjectName(QStringLiteral("net_control_left_label"));
        net_control_left_label->setGeometry(QRect(120, 90, 51, 16));
        net_control_right_label = new QLabel(NetControlFrame);
        net_control_right_label->setObjectName(QStringLiteral("net_control_right_label"));
        net_control_right_label->setGeometry(QRect(170, 90, 51, 16));
        net_control_right_label->setMouseTracking(false);
        net_control_right_label->setLayoutDirection(Qt::RightToLeft);
        net_control_stepMultiplayer = new QSlider(NetControlFrame);
        net_control_stepMultiplayer->setObjectName(QStringLiteral("net_control_stepMultiplayer"));
        net_control_stepMultiplayer->setGeometry(QRect(240, 130, 22, 160));
        net_control_stepMultiplayer->setMinimum(1);
        net_control_stepMultiplayer->setMaximum(1000);
        net_control_stepMultiplayer->setValue(10);
        net_control_stepMultiplayer->setOrientation(Qt::Vertical);
        label = new QLabel(NetControlFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 100, 81, 20));
        tod_label = new QLabel(NetControlFrame);
        tod_label->setObjectName(QStringLiteral("tod_label"));
        tod_label->setGeometry(QRect(200, 40, 91, 41));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        tod_label->setFont(font1);
        activeAnimal_label = new QLabel(NetControlFrame);
        activeAnimal_label->setObjectName(QStringLiteral("activeAnimal_label"));
        activeAnimal_label->setGeometry(QRect(350, 70, 41, 21));
        QFont font2;
        font2.setPointSize(11);
        activeAnimal_label->setFont(font2);
        label_5 = new QLabel(NetControlFrame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(300, 70, 31, 21));
        QFont font3;
        font3.setPointSize(12);
        label_5->setFont(font3);
        label_6 = new QLabel(NetControlFrame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 90, 41, 21));
        label_6->setFont(font3);
        net_score_label = new QLabel(NetControlFrame);
        net_score_label->setObjectName(QStringLiteral("net_score_label"));
        net_score_label->setGeometry(QRect(350, 90, 91, 21));
        net_score_label->setFont(font2);
        net_control_kill_button = new QPushButton(NetControlFrame);
        net_control_kill_button->setObjectName(QStringLiteral("net_control_kill_button"));
        net_control_kill_button->setGeometry(QRect(10, 60, 75, 31));
        label_7 = new QLabel(NetControlFrame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(300, 110, 41, 21));
        label_7->setFont(font3);
        generation_label = new QLabel(NetControlFrame);
        generation_label->setObjectName(QStringLiteral("generation_label"));
        generation_label->setGeometry(QRect(350, 110, 47, 20));
        generation_label->setFont(font2);
        net_control_speedMultiplayerToOne_button = new QPushButton(NetControlFrame);
        net_control_speedMultiplayerToOne_button->setObjectName(QStringLiteral("net_control_speedMultiplayerToOne_button"));
        net_control_speedMultiplayerToOne_button->setGeometry(QRect(260, 280, 31, 23));
        net_control_beamLength_slider = new QSlider(NetControlFrame);
        net_control_beamLength_slider->setObjectName(QStringLiteral("net_control_beamLength_slider"));
        net_control_beamLength_slider->setGeometry(QRect(90, 130, 22, 160));
        net_control_beamLength_slider->setMaximum(2000);
        net_control_beamLength_slider->setValue(1000);
        net_control_beamLength_slider->setOrientation(Qt::Vertical);
        label_15 = new QLabel(NetControlFrame);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(80, 100, 31, 21));
        label_15->setLayoutDirection(Qt::RightToLeft);
        net_control_beamLength_label = new QLabel(NetControlFrame);
        net_control_beamLength_label->setObjectName(QStringLiteral("net_control_beamLength_label"));
        net_control_beamLength_label->setGeometry(QRect(80, 90, 41, 16));
        net_control_obsticleAmount_slider = new QSlider(NetControlFrame);
        net_control_obsticleAmount_slider->setObjectName(QStringLiteral("net_control_obsticleAmount_slider"));
        net_control_obsticleAmount_slider->setGeometry(QRect(40, 130, 22, 160));
        net_control_obsticleAmount_slider->setMaximum(100);
        net_control_obsticleAmount_slider->setPageStep(1);
        net_control_obsticleAmount_slider->setValue(20);
        net_control_obsticleAmount_slider->setOrientation(Qt::Vertical);
        label_16 = new QLabel(NetControlFrame);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(30, 100, 41, 20));
        label_16->setLayoutDirection(Qt::RightToLeft);
        net_control_obsticleAmount_label = new QLabel(NetControlFrame);
        net_control_obsticleAmount_label->setObjectName(QStringLiteral("net_control_obsticleAmount_label"));
        net_control_obsticleAmount_label->setGeometry(QRect(40, 90, 41, 16));
        net_control_addSpeed_slider = new QSlider(NetControlFrame);
        net_control_addSpeed_slider->setObjectName(QStringLiteral("net_control_addSpeed_slider"));
        net_control_addSpeed_slider->setGeometry(QRect(200, 200, 20, 91));
        net_control_addSpeed_slider->setMinimum(-100);
        net_control_addSpeed_slider->setMaximum(100);
        net_control_addSpeed_slider->setOrientation(Qt::Vertical);
        label_17 = new QLabel(NetControlFrame);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(180, 170, 51, 21));
        net_control_addSpeed_label = new QLabel(NetControlFrame);
        net_control_addSpeed_label->setObjectName(QStringLiteral("net_control_addSpeed_label"));
        net_control_addSpeed_label->setGeometry(QRect(180, 150, 51, 16));
        net_control_addSpeed_label->setMouseTracking(false);
        net_control_addSpeed_label->setLayoutDirection(Qt::RightToLeft);
        net_control_improve_checkBox = new QCheckBox(NetControlFrame);
        net_control_improve_checkBox->setObjectName(QStringLiteral("net_control_improve_checkBox"));
        net_control_improve_checkBox->setGeometry(QRect(90, 20, 101, 21));
        net_control_improve_checkBox->setChecked(true);
        net_control_speedMultiplayerTo10_button = new QPushButton(NetControlFrame);
        net_control_speedMultiplayerTo10_button->setObjectName(QStringLiteral("net_control_speedMultiplayerTo10_button"));
        net_control_speedMultiplayerTo10_button->setGeometry(QRect(260, 250, 31, 23));
        net_control_speedMultiplayerTo100_button = new QPushButton(NetControlFrame);
        net_control_speedMultiplayerTo100_button->setObjectName(QStringLiteral("net_control_speedMultiplayerTo100_button"));
        net_control_speedMultiplayerTo100_button->setGeometry(QRect(260, 130, 31, 23));
        net_control_speedMultiplayerTo30_button = new QPushButton(NetControlFrame);
        net_control_speedMultiplayerTo30_button->setObjectName(QStringLiteral("net_control_speedMultiplayerTo30_button"));
        net_control_speedMultiplayerTo30_button->setGeometry(QRect(260, 210, 31, 23));
        net_control_speedMultiplayerTo60_button = new QPushButton(NetControlFrame);
        net_control_speedMultiplayerTo60_button->setObjectName(QStringLiteral("net_control_speedMultiplayerTo60_button"));
        net_control_speedMultiplayerTo60_button->setGeometry(QRect(260, 170, 31, 23));
        label_19 = new QLabel(NetControlFrame);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(300, 130, 31, 21));
        label_19->setFont(font3);
        ticksPerSecond_label = new QLabel(NetControlFrame);
        ticksPerSecond_label->setObjectName(QStringLiteral("ticksPerSecond_label"));
        ticksPerSecond_label->setGeometry(QRect(350, 130, 47, 20));
        ticksPerSecond_label->setFont(font2);
        NetAdjustFrame = new QFrame(centralWidget);
        NetAdjustFrame->setObjectName(QStringLiteral("NetAdjustFrame"));
        NetAdjustFrame->setGeometry(QRect(1050, 340, 421, 341));
        NetAdjustFrame->setFocusPolicy(Qt::NoFocus);
        NetAdjustFrame->setLayoutDirection(Qt::LeftToRight);
        NetAdjustFrame->setAutoFillBackground(false);
        NetAdjustFrame->setFrameShape(QFrame::StyledPanel);
        NetAdjustFrame->setFrameShadow(QFrame::Raised);
        net_draw_colorMultipliyer_slider = new QSlider(NetAdjustFrame);
        net_draw_colorMultipliyer_slider->setObjectName(QStringLiteral("net_draw_colorMultipliyer_slider"));
        net_draw_colorMultipliyer_slider->setGeometry(QRect(370, 50, 22, 160));
        net_draw_colorMultipliyer_slider->setMinimum(1);
        net_draw_colorMultipliyer_slider->setMaximum(1000);
        net_draw_colorMultipliyer_slider->setSingleStep(1);
        net_draw_colorMultipliyer_slider->setPageStep(10);
        net_draw_colorMultipliyer_slider->setValue(10);
        net_draw_colorMultipliyer_slider->setOrientation(Qt::Vertical);
        label_4 = new QLabel(NetAdjustFrame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(370, 20, 71, 20));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        MutationFactor_Slider = new QSlider(NetAdjustFrame);
        MutationFactor_Slider->setObjectName(QStringLiteral("MutationFactor_Slider"));
        MutationFactor_Slider->setGeometry(QRect(330, 50, 22, 160));
        MutationFactor_Slider->setMaximum(1000);
        MutationFactor_Slider->setOrientation(Qt::Vertical);
        label_8 = new QLabel(NetAdjustFrame);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(320, 0, 71, 20));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        MutationFactor_label = new QLabel(NetAdjustFrame);
        MutationFactor_label->setObjectName(QStringLiteral("MutationFactor_label"));
        MutationFactor_label->setGeometry(QRect(320, 20, 71, 20));
        sizePolicy.setHeightForWidth(MutationFactor_label->sizePolicy().hasHeightForWidth());
        MutationFactor_label->setSizePolicy(sizePolicy);
        drawNetXDistance_slider = new QSlider(NetAdjustFrame);
        drawNetXDistance_slider->setObjectName(QStringLiteral("drawNetXDistance_slider"));
        drawNetXDistance_slider->setGeometry(QRect(0, 10, 160, 22));
        drawNetXDistance_slider->setMinimum(1);
        drawNetXDistance_slider->setMaximum(300);
        drawNetXDistance_slider->setValue(130);
        drawNetXDistance_slider->setOrientation(Qt::Horizontal);
        drawNetYDistance_slider = new QSlider(NetAdjustFrame);
        drawNetYDistance_slider->setObjectName(QStringLiteral("drawNetYDistance_slider"));
        drawNetYDistance_slider->setGeometry(QRect(0, 40, 160, 22));
        drawNetYDistance_slider->setMinimum(1);
        drawNetYDistance_slider->setMaximum(100);
        drawNetYDistance_slider->setValue(30);
        drawNetYDistance_slider->setOrientation(Qt::Horizontal);
        drawNeuronSize_slider = new QSlider(NetAdjustFrame);
        drawNeuronSize_slider->setObjectName(QStringLiteral("drawNeuronSize_slider"));
        drawNeuronSize_slider->setGeometry(QRect(0, 70, 160, 22));
        drawNeuronSize_slider->setMinimum(1);
        drawNeuronSize_slider->setValue(12);
        drawNeuronSize_slider->setOrientation(Qt::Horizontal);
        drawConnectionSize_slider = new QSlider(NetAdjustFrame);
        drawConnectionSize_slider->setObjectName(QStringLiteral("drawConnectionSize_slider"));
        drawConnectionSize_slider->setGeometry(QRect(0, 100, 160, 22));
        drawConnectionSize_slider->setMinimum(1);
        drawConnectionSize_slider->setMaximum(40);
        drawConnectionSize_slider->setValue(2);
        drawConnectionSize_slider->setOrientation(Qt::Horizontal);
        drawAnimal_slider = new QSlider(NetAdjustFrame);
        drawAnimal_slider->setObjectName(QStringLiteral("drawAnimal_slider"));
        drawAnimal_slider->setGeometry(QRect(0, 130, 160, 22));
        drawAnimal_slider->setPageStep(1);
        drawAnimal_slider->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(NetAdjustFrame);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(170, 130, 31, 21));
        label_9->setFont(font);
        drawAnimal_label = new QLabel(NetAdjustFrame);
        drawAnimal_label->setObjectName(QStringLiteral("drawAnimal_label"));
        drawAnimal_label->setGeometry(QRect(200, 130, 41, 21));
        drawAnimal_label->setFont(font);
        label_10 = new QLabel(NetAdjustFrame);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(170, 100, 101, 21));
        label_10->setFont(font);
        label_11 = new QLabel(NetAdjustFrame);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(170, 70, 81, 21));
        label_11->setFont(font);
        label_12 = new QLabel(NetAdjustFrame);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 40, 81, 21));
        label_12->setFont(font);
        label_13 = new QLabel(NetAdjustFrame);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(170, 10, 81, 21));
        label_13->setFont(font);
        robotPathSize_slider = new QSlider(NetAdjustFrame);
        robotPathSize_slider->setObjectName(QStringLiteral("robotPathSize_slider"));
        robotPathSize_slider->setGeometry(QRect(0, 170, 160, 22));
        robotPathSize_slider->setMinimum(0);
        robotPathSize_slider->setMaximum(10000);
        robotPathSize_slider->setValue(1000);
        robotPathSize_slider->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(NetAdjustFrame);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(170, 170, 71, 21));
        label_14->setFont(font);
        label_18 = new QLabel(NetAdjustFrame);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(270, 0, 71, 20));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        MutationDivisor_label = new QLabel(NetAdjustFrame);
        MutationDivisor_label->setObjectName(QStringLiteral("MutationDivisor_label"));
        MutationDivisor_label->setGeometry(QRect(270, 20, 41, 20));
        sizePolicy.setHeightForWidth(MutationDivisor_label->sizePolicy().hasHeightForWidth());
        MutationDivisor_label->setSizePolicy(sizePolicy);
        MutationDivisor_Slider = new QSlider(NetAdjustFrame);
        MutationDivisor_Slider->setObjectName(QStringLiteral("MutationDivisor_Slider"));
        MutationDivisor_Slider->setGeometry(QRect(280, 50, 22, 160));
        MutationDivisor_Slider->setMinimum(500);
        MutationDivisor_Slider->setMaximum(10000);
        MutationDivisor_Slider->setValue(3000);
        MutationDivisor_Slider->setOrientation(Qt::Vertical);
        drawAnimal_checkBox = new QCheckBox(NetAdjustFrame);
        drawAnimal_checkBox->setObjectName(QStringLiteral("drawAnimal_checkBox"));
        drawAnimal_checkBox->setGeometry(QRect(200, 130, 101, 21));
        drawAnimal_checkBox->setChecked(false);
        displayInputValue_checkBox = new QCheckBox(NetAdjustFrame);
        displayInputValue_checkBox->setObjectName(QStringLiteral("displayInputValue_checkBox"));
        displayInputValue_checkBox->setGeometry(QRect(20, 240, 91, 17));
        displayInputValue_checkBox->setChecked(false);
        displayHiddenValue_checkBox = new QCheckBox(NetAdjustFrame);
        displayHiddenValue_checkBox->setObjectName(QStringLiteral("displayHiddenValue_checkBox"));
        displayHiddenValue_checkBox->setGeometry(QRect(20, 260, 91, 17));
        displayHiddenValue_checkBox->setChecked(false);
        displayOutputValue_checkBox = new QCheckBox(NetAdjustFrame);
        displayOutputValue_checkBox->setObjectName(QStringLiteral("displayOutputValue_checkBox"));
        displayOutputValue_checkBox->setGeometry(QRect(20, 280, 91, 17));
        displayOutputValue_checkBox->setChecked(false);
        label_20 = new QLabel(NetAdjustFrame);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 220, 47, 13));
        version_label = new QLabel(centralWidget);
        version_label->setObjectName(QStringLiteral("version_label"));
        version_label->setGeometry(QRect(1350, 20, 151, 61));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1340, 790, 161, 41));
        startPath_label = new QLabel(centralWidget);
        startPath_label->setObjectName(QStringLiteral("startPath_label"));
        startPath_label->setGeometry(QRect(840, 0, 591, 16));
        QFont font4;
        font4.setUnderline(false);
        font4.setKerning(true);
        startPath_label->setFont(font4);
        startPath_label->setLayoutDirection(Qt::RightToLeft);
        startPath_label->setAutoFillBackground(false);
        startPath_label->setTextFormat(Qt::AutoText);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1513, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AI robot simulator", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "rechts", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "links", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Motoren", nullptr));
        net_control_toggle_button->setText(QApplication::translate("MainWindow", "KI control", nullptr));
        net_control_left_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        net_control_right_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        label->setText(QApplication::translate("MainWindow", "step multiplayer", nullptr));
        tod_label->setText(QString());
        activeAnimal_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Tier", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "score", nullptr));
        net_score_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        net_control_kill_button->setText(QApplication::translate("MainWindow", "KILL", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "gen", nullptr));
        generation_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        net_control_speedMultiplayerToOne_button->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "beam", nullptr));
        net_control_beamLength_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "obsticle", nullptr));
        net_control_obsticleAmount_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "AddSpeed", nullptr));
        net_control_addSpeed_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        net_control_improve_checkBox->setText(QApplication::translate("MainWindow", "improve", nullptr));
        net_control_speedMultiplayerTo10_button->setText(QApplication::translate("MainWindow", "10", nullptr));
        net_control_speedMultiplayerTo100_button->setText(QApplication::translate("MainWindow", "100", nullptr));
        net_control_speedMultiplayerTo30_button->setText(QApplication::translate("MainWindow", "30", nullptr));
        net_control_speedMultiplayerTo60_button->setText(QApplication::translate("MainWindow", "60", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "T/s", nullptr));
        ticksPerSecond_label->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "colorMulti", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "mut. fac.", nullptr));
        MutationFactor_label->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Tier", nullptr));
        drawAnimal_label->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "ConnectionSize", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "NeuronSize", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "yDistance", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "xDistance", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "PathSize", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "mut. div.", nullptr));
        MutationDivisor_label->setText(QString());
        drawAnimal_checkBox->setText(QApplication::translate("MainWindow", "clipToBest", nullptr));
        displayInputValue_checkBox->setText(QApplication::translate("MainWindow", "input values", nullptr));
        displayHiddenValue_checkBox->setText(QApplication::translate("MainWindow", "hidden values", nullptr));
        displayOutputValue_checkBox->setText(QApplication::translate("MainWindow", "output values", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "display:", nullptr));
        version_label->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Save Net", nullptr));
        startPath_label->setText(QApplication::translate("MainWindow", "PATH", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

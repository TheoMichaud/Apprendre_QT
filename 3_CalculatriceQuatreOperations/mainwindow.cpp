#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_signe , SIGNAL(released()), this, SLOT(on_unary_operation_pressed()));
    connect(ui->pushButton_percent , SIGNAL(released()), this, SLOT(on_unary_operation_pressed()));

    connect(ui->pushButton_div , SIGNAL(released()), this, SLOT(on_binary_operation_pressed()));
    connect(ui->pushButton_mult , SIGNAL(released()), this, SLOT(on_binary_operation_pressed()));
    connect(ui->pushButton_plus , SIGNAL(released()), this, SLOT(on_binary_operation_pressed()));
    connect(ui->pushButton_sub , SIGNAL(released()), this, SLOT(on_binary_operation_pressed()));

    ui->pushButton_div->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_sub->setCheckable(true);
    secondNumber = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    double labelNumber;
    QString newLabel;

    if((ui->pushButton_div->isChecked() || ui->pushButton_mult->isChecked()
            || ui->pushButton_plus->isChecked() || ui->pushButton_sub->isChecked()) && !secondNumber)
    {
        labelNumber = button->text().toDouble();
        secondNumber =true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if (ui->label->text().contains(".") && button->text()=="0"){
            newLabel = ui->label->text() + button->text();
        }
        else{
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }

    }


    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dot_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::on_unary_operation_pressed()
{
    QPushButton *button = (QPushButton *)sender();
    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber *= -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    if (button->text() == "%"){
        labelNumber = ui->label->text().toDouble();
        labelNumber *= 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }


}

void MainWindow::on_binary_operation_pressed()
{
        QPushButton *button = (QPushButton *)sender();
        button->setChecked(true);
        accumulateur = ui->label->text().toDouble();


}

void MainWindow::on_pushButton_C_released()
{
    ui->pushButton_div->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_sub->setChecked(false);

    secondNumber = false;
    ui->label->setText("0");

}

void MainWindow::on_pushButton_equal_released()
{
    double secondNum, result;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if (ui->pushButton_div->isChecked()){
        result = accumulateur / secondNum;
        newLabel = QString::number(result, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_div->setChecked(false);

    }
    else if (ui->pushButton_mult->isChecked()){
        result = accumulateur * secondNum;
        newLabel = QString::number(result, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_mult->setChecked(false);
    }
    else if (ui->pushButton_plus->isChecked()){
        result = accumulateur + secondNum;
        newLabel = QString::number(result, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_sub->isChecked()){
        result = accumulateur - secondNum;
        newLabel = QString::number(result, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_sub->setChecked(false);
    }
    secondNumber = false;

}

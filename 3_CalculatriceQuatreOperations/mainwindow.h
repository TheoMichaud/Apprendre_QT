#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void digit_pressed();
    void on_pushButton_dot_released();
    void on_unary_operation_pressed();
    void on_binary_operation_pressed();

    void on_pushButton_C_released();

    void on_pushButton_equal_released();

private:
    Ui::MainWindow *ui;
    double accumulateur;
    bool secondNumber;
};

#endif // MAINWINDOW_H

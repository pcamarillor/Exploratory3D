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

private:
    Ui::MainWindow *ui;
private slots:
    void Mousse_current_pos();
    void Mousse_Pressed();
    void Mousse_left();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);
    void on_spinBox_4_valueChanged(int arg1);
    void on_spinBox_5_valueChanged(int arg1);
    void on_spinBox_6_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_btnIniciarAnimacion_clicked();
    void on_btnIniciarAnimacion3D_clicked();
    void on_btnDetenerAnimacion3D_clicked();
    void on_btnEjecutarSET_clicked();
    void on_btnIniciarAnimacionSET_clicked();
    void on_btnSiguiente_clicked();
    void on_btnDetenerAnimacion_clicked();
};

#endif // MAINWINDOW_H

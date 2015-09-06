#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(Mouse_Pos()), this, SLOT(Mousse_current_pos()));
    connect(ui->widget, SIGNAL(Mousse_Pressed()), this, SLOT(Mousse_Pressed()));
    //connect((QObject*)ui->widget->robot, SIGNAL(Avanzar(int)),ui->progressBar,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Mousse_current_pos()
{
    ui->widget->updateGL();
}

void MainWindow::Mousse_Pressed()
{
   // std::cout<<"Mouse pressed" << std::endl;
    ui->widget->updateGL();
}

void MainWindow::Mousse_left()
{
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->widget->robot->setArt1(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{

    ui->widget->robot->setArt2(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{

    ui->widget->robot->setArt3(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{

    ui->widget->robot->setArt4(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{

    ui->widget->robot->setArt5(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_spinBox_6_valueChanged(int arg1)
{

    ui->widget->robot->setArt6(arg1);
    ui->widget->robot->CinematicaDirecta();
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_clicked()
{
//    float px, py, pz;
//    px = ui->textEdit->toPlainText().toFloat();
//    py = ui->textEdit_2->toPlainText().toFloat();
//    pz = ui->textEdit_3->toPlainText().toFloat();
//    ui->widget->robot->CinematicaInversa(px,py,pz);

//    ui->textEdit->setText(QString::number(ui->widget->robot->posX));
//    ui->textEdit_2->setText(QString::number(ui->widget->robot->posY));
//    ui->textEdit_3->setText(QString::number(ui->widget->robot->posZ));
//    ui->widget->updateGL();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->Explorar();
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_3_clicked()
{
    int IMax = ui->txtIMax3D->toPlainText().toInt();
    int KMax = ui->txtKMax3D->toPlainText().toInt();
    float alpha = ui->txtAlpha3D->toPlainText().toFloat();
    float dmin = ui->txtDMin3D->toPlainText().toFloat();
    string s = ui->widget->Exploracion3D_SRT(KMax, IMax, alpha, dmin);
    ui->btnIniciarAnimacion3D->setEnabled(true);
    QString qs;
    qs.fromStdString(s);
    cout << s << endl;
    ui->plainTextEdit->setPlainText(qs);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->VerEscena();
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->widget->VerificarColision();
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_6_clicked()
{
//    punto3d q;
//    q.setX(ui->txtPosX->toPlainText().toFloat());
//    q.setY(ui->txtPosY->toPlainText().toFloat());
//    q.setZ(ui->txtPosZ->toPlainText().toFloat());

//    ui->widget->robot->pionero->Mover(q);
//    ui->widget->robot->TrasladarRobot(q.getX(), q.getY(),q.getZ());
    ui->widget->MoverMovil();
    ui->widget->updateGL();
}

void MainWindow::on_pushButton_7_clicked()
{
    string performance;
    int k3D = ui->txtIteracionesManipulador->toPlainText().toInt();
    int k2D = ui->txtIteracionesMovil->toPlainText().toInt();
    float alpha2d = ui->txtAlphaMovil->toPlainText().toFloat();
    float alpha3d = ui->txtAlpgaManipulador->toPlainText().toFloat();
    float dmin2d = ui->txtDMinMovil->toPlainText().toFloat();
    float dmin3d = ui->txtDMinManipulador->toPlainText().toFloat();
    int imax2d = ui->txtKMovil->toPlainText().toInt();
    int imax3d = ui->txtKManipulador->toPlainText().toInt();

//    ui->btnIniciarAnimacion->setEnabled(false);
//    ui->btnDetenerAnimacion->setEnabled(false);
//    performance = ui->widget->ExploracionHibrida(k2D,k3D,alpha2d,alpha3d,dmin2d,dmin3d,imax2d,imax3d);
//    cout << performance << endl;
//    QString qq;
//    qq.fromStdString(performance);
    performance = ui->widget->Exploracion3D_SRT(k3D,imax3d,alpha3d,dmin3d);
    QString qs = QString::fromStdString(performance);
    ui->plainTextEdit->setPlainText(qs);
    ui->btnIniciarAnimacion->setEnabled(true);
    ui->btnDetenerAnimacion->setEnabled(true);
}

void MainWindow::on_btnIniciarAnimacion_clicked()
{
    //ui->widget->iniciarAnimacion();
     ui->widget->iniciarAnimacion3D();
}

void MainWindow::on_btnIniciarAnimacion3D_clicked()
{
    ui->widget->iniciarAnimacion3D();
    ui->btnDetenerAnimacion3D->setEnabled(true);
}

void MainWindow::on_btnDetenerAnimacion3D_clicked()
{
    ui->widget->detenerAnimacion3D();
}

void MainWindow::on_btnEjecutarSET_clicked()
{
    int KMax = ui->txtIteracionesSET->toPlainText().toInt();
    int estrategia = ui->radioEstrategiaAG->isChecked() ? 1 : 2;
    cout << "estrategia:" << estrategia << endl;
    string performance;
    performance = ui->widget->Exploracion3D_SET(KMax, estrategia);
    QString qs;
    qs.fromStdString(performance);
    ui->plainTextEdit->setPlainText(qs);
    ui->btnIniciarAnimacionSET->setEnabled(true);
    cout << performance << endl;
}

void MainWindow::on_btnIniciarAnimacionSET_clicked()
{
    ui->widget->iniciarAnimacion3D();
    ui->btnDetenerAnimacionSET->setEnabled(true);
}

void MainWindow::on_btnSiguiente_clicked()
{
    string strSiguientePunto;
    int IMAx = ui->txtIteracionesMovil->toPlainText().toInt();
    float dmin = ui->txtDMinMovil->toPlainText().toFloat();
    float alpha = ui->txtAlphaMovil->toPlainText().toFloat();
    strSiguientePunto = ui->widget->ExploracionMovil_Simple(IMAx, alpha,dmin);
    QString qs = QString::fromStdString(strSiguientePunto);
    ui->plainTextEdit->setPlainText(qs);
}

void MainWindow::on_btnDetenerAnimacion_clicked()
{
    ui->widget->detenerAnimacion3D();
}

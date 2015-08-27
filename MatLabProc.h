#ifndef MATLABPROC_H
#define MATLABPROC_H
#include <QProcess>
#include <iostream>

using namespace std;
class MatLabProc :public QObject
{
    QProcess proc;

    //enum State {IDLE, ERROR, CALCSIN};
    //State state;

public:
    MatLabProc();
    bool start();
    bool stop();
    bool calcSin();
signals:
    void sinFinished(QVector<double> data);
private slots:
    void sin_stream();
    void sin_err();

};

#endif // MATLABPROC_H

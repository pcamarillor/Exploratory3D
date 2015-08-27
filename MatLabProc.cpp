#include "MatLabProc.h"


MatLabProc::MatLabProc()
{
  //state = IDLE;
}


 //start process
bool MatLabProc::start()
{
  proc.start("matlab.exe");
  return proc.waitForStarted();
}

//stop process
bool MatLabProc::stop() {return true;}

bool MatLabProc::calcSin()
{
  //if (state != IDLE) return false;
  //state = CALCSIN;

  QByteArray script = "clear;\n"
    "x = [0 1];\n"
    "y = sin(x);\n"
    "y\n";

  proc.write(script);
  proc.closeWriteChannel();
  connect(&proc, SIGNAL(readyReadStandardOutput()), SLOT(sin_stream()));
  connect(&proc, SIGNAL(readyReadStandardError()), SLOT(sin_err()));

  return true;
 }



 void MatLabProc::sin_stream()
 {
/* Ouptut like this
y =

 Columns 1 through 6:

   1.5932e-01   7.9915e-02   3.9989e-02   1.9999e-02   1.3000e-02   6.9999e-03

 Columns 7 through 10:

   4.0000e-03   2.0000e-03   1.0000e-03   8.0000e-04
*/
  if (proc.canReadLine()) {
   QByteArray data = proc.readAllStandardOutput();
   //read numbers from data
   cout << data.toInt() << endl;

    //proc.closeReadChannel();
    proc.disconnect();
    //state = IDLE;
    //emit sinFinished(vecOfSinResults);
   }
  }



void MatLabProc::sin_err()
{
  if (proc.canReadLine()) {
   QByteArray data = proc.readAllStandardError();
   //process errors in data
   //proc.closeReadChannel();
   proc.disconnect();
   //state = ERROR;
  }
}



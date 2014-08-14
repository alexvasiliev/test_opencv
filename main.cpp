#include <QtWidgets/QApplication>
#include <MainWindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PManager manager = PManager (new CManager(0,0)); //= CreateManager ( 1, 0);
    //manager->CreateGUI();
    //manager->CreateNonPtzThread();
    CMainWindow mainWinow;
    mainWinow.Start();
    return a.exec();
}


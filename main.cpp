#include "mainwindow.h"
#include <QApplication>
#include "fabricagladiadores.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    cout<<"hola"<<endl;
    FabricaGladiadores *F1 = new FabricaGladiadores(2);

    return a.exec();
}

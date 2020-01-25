#include "mainwindow.hpp"
#include "settings/logger.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    create_logger();
    logger("--- MAIN BEGINNING ---");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include <QApplication>
#include "mainWindow.h"


/**
 * @brief Application entry point.
 * @param argc Number of input arguments.
 * @param argv Array of input arguments.
 * @return Exit code.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Open welcome screen
    QPixmap pixmap(":/logos/resources/Innerspec_full.png");
    QSplashScreen splash(pixmap);
    splash.show();

    // Wait 3 seconds and hide the splash screen
    QThread::sleep(3);
    splash.hide();

    // Open wain window
    MainWindow w;
    w.show();

    return app.exec();
}

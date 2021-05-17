#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QThread>
#include <QTime>
#include "evolutionmachine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("HAJ");
    app.setApplicationName("Drawin");

    QTranslator translator;
    if (translator.load(QLocale::system(), ""))
        app.installTranslator(&translator);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    EvolutionMachine *evolutionMachine = new EvolutionMachine;

#ifdef USE_THREAD
    QThread workerThread;
    evolutionMachine->moveToThread(&workerThread);
    workerThread.start();
#endif

    MainWindow window;

    QObject::connect(evolutionMachine, SIGNAL(newSolutionGenerated(QImage)),
                     &window,          SLOT  (updateImage         (QImage)));

    QObject::connect(&window,          SIGNAL(mutationRateChanged(double)),
                     evolutionMachine, SLOT  (setMutationRate    (double)));

    QObject::connect(&window,          SIGNAL(requestNewSolution                (QString)),
                     evolutionMachine, SLOT  (resetAndStartNewSolutionGeneration(QString)));
    window.show();

    int returnCode = app.exec();

#ifdef USE_THREAD
    workerThread.quit();
    workerThread.wait();
#endif

    delete evolutionMachine; evolutionMachine = Q_NULLPTR;

    return returnCode;
}

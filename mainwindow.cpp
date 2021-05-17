#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QSettings>

const char *settingsLastDir("lastDir");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonLoadReference, SIGNAL(clicked()), this, SLOT(resetAndStartNewSolutionGeneration()));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(mutationRateChanged(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetAndStartNewSolutionGeneration()
{
    QSettings settings;
    QString lastDir(settings.value(settingsLastDir).toString());
    QString fileName(QFileDialog::getOpenFileName(this, "", lastDir));

    if (fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);
    if (fileInfo.absolutePath() != lastDir) {
        settings.setValue(settingsLastDir, fileInfo.absolutePath());
        settings.sync();
    }

    emit requestNewSolution(fileName);
}

void MainWindow::updateImage(QImage newImage)
{
    QPixmap pixmap;
    pixmap.convertFromImage(newImage);
    ui->label->setPixmap(pixmap);
}

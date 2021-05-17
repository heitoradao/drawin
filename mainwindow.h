#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>


namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void requestNewSolution(QString fileName);
    void mutationRateChanged(double);

public slots:
    void updateImage(QImage newImage);

protected slots:
    void resetAndStartNewSolutionGeneration();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

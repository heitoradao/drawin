#include "evolutionmachine.h"
#include <QTimer>
#include <QColor>
#include <QVariant>
#include <cmath>

const double bestFitnessPossible = 0.0;
const double worstFitnessPossible = 999999999999999.0;

EvolutionMachine::EvolutionMachine(QObject *parent)
    : QObject(parent)
    , bestFitnessSoFar(bestFitnessPossible)
    //, mutationRate(0.1)
    , candidatesGenerated(0)
    , candidatesGood(0)
{
    setMutationRate(0.1);
    //setProperty("mutationRate", 0.1);
}

double EvolutionMachine::mutationRate()
{
    //return property("mutationRate").toDouble();
    return _mutationRate;
}

void EvolutionMachine::resetAndStartNewSolutionGeneration(QString referencePath)
{
    if (!reference.load(referencePath)) {
        return;
        //throw ?
    }

    bestImageSoFar = QImage(reference.size(), QImage::Format_RGB888); // empty
    bestFitnessSoFar = worstFitnessPossible;
    QTimer::singleShot(0, this, SLOT(generateNewSolution()));
}

/*!
 * \todo Create a stop criteria
 * \todo Reduce the feedback rate using a timer.
 */
void EvolutionMachine::generateNewSolution()
{
    // create a new image, based on the best known solution
    candidatesGenerated++;
    QImage newImage(reference.size(), QImage::Format_RGB888);
    for (int y(0); y < reference.size().height(); ++y) {
        for (int x(0); x < reference.size().width(); ++x) {
#if 1
            if ((qrand() / (double) RAND_MAX) < this->mutationRate()) {
                const int red(qrand() % 256);
                const int green(qrand() % 256);
                const int blue(qrand() % 256);
                newImage.setPixel(x, y, qRgb(red, green, blue));
            } else {
                newImage.setPixel(x, y, bestImageSoFar.pixel(x, y));
            }
#else
            QColor color(bestImageSoFar.pixel(x, y));

            if ((qrand() / (double) RAND_MAX) < mutationRate) {
                const int red(color.red() + ((qrand() % 3) - 1));
                const int green(color.green() + ((qrand() % 3) - 1));
                const int blue(color.blue() + ((qrand() % 3) - 1));
                newImage.setPixel(x, y, qRgb(red, green, blue));
            } else {
                newImage.setPixel(x, y, bestImageSoFar.pixel(x, y));
            }
#endif
        } // for (int x(0); x < reference.size().width(); ++x)
    } // for (int y(0); y < reference.size().height(); ++y) {

    // now we should evaluate the quality of this new proposed solution...
    // and if it's better thes sentinel, update the sentinel.

    // I know we could make things a bit more faster joining this 2 iterations,
    // but even more faster distributing the responsibilities among different proccessors

    // The separation of algorithm is a step to evolve this arch to a more flexible one.
    double sumDistances(0.0); // zero is the best fitness (?)
    for (int y(0); y < reference.size().height(); ++y) {
        for (int x(0); x < reference.size().width(); ++x) {
            QColor c1(newImage.pixel(x, y));
            QColor c2(reference.pixel(x, y));

            const double distanceR(c1.red()   - c2.red()   );
            const double distanceG(c1.green() - c2.green() );
            const double distanceB(c1.blue()  - c2.blue()  );

            sumDistances += std::sqrt(  distanceR * distanceR
                                      + distanceG * distanceG
                                      + distanceB * distanceB);
        }
    }

    // if we found a better image...
    Q_ASSERT(sumDistances != 0.0);
    if (sumDistances < bestFitnessSoFar) { // less is better
        bestFitnessSoFar = sumDistances;
        bestImageSoFar = newImage;
        candidatesGood++;
#if 0
        ui->labelStatistics->setText(QString("best fitness so far: %0\n"
                                             "success rate %1%")
                                     .arg(bestFitnessSoFar)
                                     .arg(((double)candidatesGood/candidatesGenerated)*100));
        QPixmap pixmap;
        pixmap.convertFromImage(bestImageSoFar);
        ui->label->setPixmap(pixmap);
#else
        emit newSolutionGenerated(bestImageSoFar);
#endif
    }

    QTimer::singleShot(0, this, SLOT(generateNewSolution()));
}

void EvolutionMachine::setMutationRate(double newMutationRate)
{
#ifdef USE_PROPERTY_FOR_MUTATION_RATE
    if (newMutationRate != mutationRate()) {
        setProperty("mutationRate", newMutationRate);
#else
    if (_mutationRate != newMutationRate) {
        _mutationRate = newMutationRate;
#endif
        emit mutationRateChanged();
    }
}

#ifndef EVOLUTIONMACHINE_H
#define EVOLUTIONMACHINE_H

#include <QObject>
#include <QImage>

/*!
 * \brief The EvolutionMachine class
 *
 * My first implementation of the evolution machine.
 */
class EvolutionMachine : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(double _mutationRate READ mutationRate WRITE setMutationRate NOTIFY mutationRateChanged);
public:
    explicit EvolutionMachine(QObject *parent = nullptr);
    double mutationRate();

signals:
    void newSolutionGenerated(QImage);
    void mutationRateChanged();

public slots:
    void resetAndStartNewSolutionGeneration(QString referencePath);
    void generateNewSolution();
    void setMutationRate(double newMutationRate);

protected:
    double _mutationRate;
    double bestFitnessSoFar;
    QImage bestImageSoFar;
    QImage reference;
    int candidatesGenerated;
    int candidatesGood;

};

#endif // EVOLUTIONMACHINE_H

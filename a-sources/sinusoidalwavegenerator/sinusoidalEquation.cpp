#include "sinusoidalEquation.h"
#include <QtMath>


SinusoidalEquation::SinusoidalEquation()
    : m_amplitude(1.0),
      m_oscillationFrequency(100.0),
      m_initialDelay(0.0),
      m_numberOfPeriods(1),
      m_samplingFrequency(10000.0),
      m_attenuationFactor(0.0),
      m_data(),
      m_timeVector(),
      m_elongationVector()
{
    // Solve the equation with the default parameters
    solveEquation();
}

void SinusoidalEquation::setAmplitude(double amplitude)
{
    m_amplitude = amplitude;
    solveEquation();
}

void SinusoidalEquation::setOscillationFrequency(double oscillationFrequency)
{
    m_oscillationFrequency = oscillationFrequency;
    solveEquation();
}

void SinusoidalEquation::setInitialDelay(double initialDelay)
{
    m_initialDelay = initialDelay;
    solveEquation();
}

void SinusoidalEquation::setNumberOfPeriods(int numberOfPeriods)
{
    m_numberOfPeriods = numberOfPeriods;
    solveEquation();
}

void SinusoidalEquation::setSamplingFrequency(double samplingFrequency)
{
    m_samplingFrequency = samplingFrequency;
    solveEquation();
}

void SinusoidalEquation::setAttenuationFactor(double attenuationFactor)
{
    m_attenuationFactor = attenuationFactor;
    solveEquation();
}

void SinusoidalEquation::solveEquation()
{
    // Clear vectors
    m_data.clear();
    m_timeVector.clear();
    m_elongationVector.clear();

    // Calculate new values
    double tmax = m_numberOfPeriods * (1.0 / m_oscillationFrequency);
    for (double t = 0.0; t <= tmax; t = t + (1.0 / m_samplingFrequency))
    {
        // Current attenuation
        double currentAttenuationFactor = (1.0 - (m_attenuationFactor * t));
        if (currentAttenuationFactor < 0.0)
            currentAttenuationFactor = 0.0;

        // Current values of time vs elongation
        double currentTimeValue = t;
        double currentElongationValue = m_amplitude * currentAttenuationFactor * qSin(2 * M_PI * m_oscillationFrequency * t + qDegreesToRadians(m_initialDelay));

        // Add values to vectors
        m_data.append(QPointF(currentTimeValue, currentElongationValue));
        m_timeVector.append(currentTimeValue);
        m_elongationVector.append(currentElongationValue);
    }

    // Notify the modification of the wave values
    emit equationChanged();
}

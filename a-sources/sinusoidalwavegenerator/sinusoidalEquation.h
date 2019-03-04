#ifndef SINUSOIDALEQUATION_H
#define SINUSOIDALEQUATION_H

#include <QObject>
#include <QPointF>
#include <QVector>

/**
 * @brief Sinusoidal wave form.
 */
class SinusoidalEquation : public QObject
{
    Q_OBJECT

    /*
     * PROPERTIES
     */
    Q_PROPERTY(double Amplitude READ amplitude WRITE setAmplitude)
    Q_PROPERTY(double OscillationFrequency READ oscillationFrequency WRITE setOscillationFrequency)
    Q_PROPERTY(double InitialDelay READ initialDelay WRITE setInitialDelay)
    Q_PROPERTY(int NumberOfPeriods READ numberOfPeriods WRITE setNumberOfPeriods)
    Q_PROPERTY(double SamplingFrequency READ samplingFrequency WRITE setSamplingFrequency)
    Q_PROPERTY(double AttenuationFactor READ attenuationFactor WRITE setAttenuationFactor)
    Q_PROPERTY(QVector<QPointF> Data READ data)
    Q_PROPERTY(QVector<double> TimeVector READ timeVector)
    Q_PROPERTY(QVector<double> ElongationVector READ elongationVector)

public:
    /**
     * @brief Constructor.
     */
    SinusoidalEquation();

    /**
     * @brief Gets the amplitude of the sinusoidal wave.
     * @return Amplitude of the sinusoidal wave.
     */
    double amplitude() { return m_amplitude; }
    /**
     * @brief Gets the oscillation frequency of the sinusoidal wave, in hertz.
     * @return Oscillation frequency of the sinusoidal wave.
     */
    double oscillationFrequency() { return m_oscillationFrequency; }
    /**
     * @brief Gets the initial delay of the sinusoidal wave, in degrees.
     * @return Initial delay of the sinusoidal wave.
     */
    double initialDelay() { return m_initialDelay; }
    /**
     * @brief Gets the number of periods of the sinusoidal wave.
     * @return Number of periods of the sinusoidal wave.
     */
    int numberOfPeriods() { return m_numberOfPeriods; }
    /**
     * @brief Gets the sampling frequency of the sinusoidal wave, in hertz.
     * @return Sampling frequency of the sinusoidal wave.
     */
    double samplingFrequency() { return m_samplingFrequency; }
    /**
     * @brief Gets the attenuation factor of the sinusoidal wave, in units per second.
     * @return Attenuation factor of the sinusoidal wave.
     */
    double attenuationFactor() { return m_attenuationFactor; }
    /**
     * @brief Gets the vector of 2D points that describe the sinusoidal wave (time vs elongation).
     * @return Vector of 2D points that describe the sinusoidal wave.
     */
    QVector<QPointF> data() { return m_data; }
    /**
     * @brief Gets the vector of samples in the horizontal axis (time, in seconds).
     * @return Vector of time samples.
     */
    QVector<double> timeVector() { return m_timeVector; }
    /**
     * @brief Gets the vector of samples in the vertical axis (elongation).
     * @return Vector of elongation samples.
     */
    QVector<double> elongationVector() { return m_elongationVector; }

signals:
    /**
     * @brief Signal emited when the equation has changed.
     */
    void equationChanged();

public slots:
    /**
     * @brief Sets the amplitude of the sinusoidal wave.
     * @param amplitude Amplitude of the sinusoidal wave.
     */
    void setAmplitude(double amplitude);
    /**
     * @brief Sets the oscillation frequency of the sinusoidal wave.
     * @param oscillationFrequency Oscillation frequency of the sinusoidal wave, in hertz.
     */
    void setOscillationFrequency(double oscillationFrequency);
    /**
     * @brief Sets the initial delay of the sinusoidal wave.
     * @param initialDelay Initial delay of the sinusoidal wave, in degrees.
     */
    void setInitialDelay(double initialDelay);
    /**
     * @brief Sets the number of periods of the sinusoidal wave.
     * @param numberOfPeriods Number of periods of the sinusoidal wave.
     */
    void setNumberOfPeriods(int numberOfPeriods);
    /**
     * @brief Sets the sampling frequency of the sinusoidal wave.
     * @param samplingFrequency Sampling frequency of the sinusoidal wave, in hertz.
     */
    void setSamplingFrequency(double samplingFrequency);
    /**
     * @brief Sets the attenuation factor of the sinusoidal wave.
     * @param attenuationFactor Attenuation factor of the sinusoidal wave.
     */
    void setAttenuationFactor(double attenuationFactor);

private slots:
    /**
     * @brief Solves the equation with the current parameters.
     */
    void solveEquation();

private:
    /**
     * @brief Amplitude of the sinusoidal wave.
     */
    double m_amplitude;
    /**
     * @brief Oscillation frequency of the sinusoidal wave, in hertz.
     */
    double m_oscillationFrequency;
    /**
     * @brief Initial delay of the sinusoidal wave, in degrees.
     */
    double m_initialDelay;
    /**
     * @brief Number of periods of the sinusoidal wave.
     */
    int m_numberOfPeriods;
    /**
     * @brief Sampling frequency of the sinusoidal wave, in hertz.
     */
    double m_samplingFrequency;    
    /**
     * @brief Attenuation factor of the sinusoidal wave, in units per second.
     */
    double m_attenuationFactor;
    /**
     * @brief Vector of 2D points representing the sinusoidal wave (time vs elongation).
     */
    QVector<QPointF> m_data;
    /**
     * @brief Vector of time samples, in seconds.
     */
    QVector<double> m_timeVector;
    /**
     * @brief Vector of elongation samples.
     */
    QVector<double> m_elongationVector;
};

#endif // SINUSOIDALEQUATION_H

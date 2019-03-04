#include <cfloat>
#include <qcustomplot.h>
#include <QtMath>
#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow() :
    m_ui(new Ui::MainWindow),
    m_equation(NULL),
    m_plotWindow(NULL)
{
    m_ui->setupUi(this);

    // Set the initial position
    this->move(0,0);

    // Create the equation with default values
    m_equation = new SinusoidalEquation();

    // Create the PlotWindow to draw the initial equation
    m_plotWindow = new PlotWindow(this);
    m_plotWindow->move(this->width(), 0);

    // Configure the form's controls
    configureFormControls();

    // Load the equation in the widget and draw it
    m_plotWindow->loadEquation(m_equation);
    m_plotWindow->show();

    // Refresh form controls with the current values
    refreshFormValues();

    // Connections between signals and slots
    // 1) Main window user interface signals:
    //  - Wave parameters controls
    connect(m_ui->doubleSpinBox_oscillationFrequency, SIGNAL(valueChanged(double)), m_equation, SLOT(setOscillationFrequency(double)));
    connect(m_ui->spinBox_numberOfPeriods, SIGNAL(valueChanged(int)), m_equation, SLOT(setNumberOfPeriods(int)));
    connect(m_ui->doubleSpinBox_initialDelay, SIGNAL(valueChanged(double)), m_equation, SLOT(setInitialDelay(double)));
    connect(m_ui->doubleSpinBox_samplingFrequency, SIGNAL(valueChanged(double)), m_equation, SLOT(setSamplingFrequency(double)));
    //  - Advanced features controls
    connect(m_ui->groupBox_advancedFeatures, SIGNAL(toggled(bool)), m_ui->widget_advancedFeatures, SLOT(setVisible(bool)));
    connect(m_ui->groupBox_advancedFeatures, SIGNAL(toggled(bool)), m_ui->action_advancedFeatures, SLOT(setChecked(bool)));
    connect(m_ui->doubleSpinBox_amplitude, SIGNAL(valueChanged(double)), m_equation, SLOT(setAmplitude(double)));
    connect(m_ui->doubleSpinBox_attenuationFactor, SIGNAL(valueChanged(double)), m_equation, SLOT(setAttenuationFactor(double)));
    //  - Visualization features controls
    connect(m_ui->groupBox_visualizationFeatures, SIGNAL(toggled(bool)), m_ui->widget_visualizationFeatures, SLOT(setVisible(bool)));
    connect(m_ui->groupBox_visualizationFeatures, SIGNAL(toggled(bool)), m_ui->action_visualizationFeatures, SLOT(setChecked(bool)));
    connect(m_ui->spinBox_dataWindowWidth, SIGNAL(valueChanged(int)), this, SLOT(onDataWindowSizeChanged()));
    connect(m_ui->spinBox_dataWindowHeight, SIGNAL(valueChanged(int)), this, SLOT(onDataWindowSizeChanged()));
    connect(m_ui->comboBox_lineStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectedLineStyleChanged(int)));
    connect(m_ui->pushButton_color, SIGNAL(clicked(bool)), this, SLOT(onSelectColorClicked()));
    //  - Menu bar controls
    connect(m_ui->action_saveToFile, SIGNAL(triggered(bool)), this, SLOT(onSaveToFileTriggered()));
    connect(m_ui->action_advancedFeatures, SIGNAL(toggled(bool)), m_ui->groupBox_advancedFeatures, SLOT(setChecked(bool)));
    connect(m_ui->action_visualizationFeatures, SIGNAL(toggled(bool)), m_ui->groupBox_visualizationFeatures, SLOT(setChecked(bool)));
    // 2) SinusoidalEquation signals
    connect(m_equation, SIGNAL(equationChanged()), this, SLOT(onEquationChanged()));
    // 3) PlotWindow signals
    connect(m_plotWindow, SIGNAL(widgetResized(QSize)), this, SLOT(onPlotWindowResized(QSize)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onDataWindowSizeChanged()
{
    // Read new values from the user interface
    int newWidth = m_ui->spinBox_dataWindowWidth->value();
    int newHeight = m_ui->spinBox_dataWindowHeight->value();
    m_plotWindow->resize(newWidth, newHeight);
}

void MainWindow::onSelectedLineStyleChanged(int option)
{
    // Read new values from the user interface
    switch (option)
    {
    case 0:
        m_plotWindow->changeLineStyle(QCPGraph::lsNone);
        break;
    case 1:
        m_plotWindow->changeLineStyle(QCPGraph::lsLine);
        break;
    }
}

void MainWindow::onSelectColorClicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
        m_plotWindow->changeColor(color);
}

void MainWindow::onSaveToFileTriggered()
{
    // Open a file dialog to let the user choose where to save the file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save to file"), QCoreApplication::applicationDirPath(), tr("Images (*.png)"));
    if (!fileName.isEmpty())
    {
        if (m_plotWindow->saveToFile(fileName))
            m_ui->statusBar->showMessage("Graph saved to " + fileName, 5000);
        else
            m_ui->statusBar->showMessage("Error trying to save graph to " + fileName, 5000);
    }
}

void MainWindow::onEquationChanged()
{
    m_plotWindow->loadEquation(m_equation);
}

void MainWindow::onPlotWindowResized(const QSize &size)
{
    // Refresh the values of data window size in the form
    m_ui->spinBox_dataWindowWidth->setValue(size.width());
    m_ui->spinBox_dataWindowHeight->setValue(size.height());
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Clean tasks
    if (m_plotWindow != NULL)
    {
        m_plotWindow->close();
        delete m_plotWindow;
    }

    if (m_equation != NULL)
        delete m_equation;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        qApp->quit();
        break;
    }
}

void MainWindow::configureFormControls()
{
    // Wave parameters controls
    m_ui->doubleSpinBox_oscillationFrequency->setMaximum(DBL_MAX);
    m_ui->spinBox_numberOfPeriods->setMaximum(INT_MAX);
    m_ui->doubleSpinBox_initialDelay->setMaximum(qRadiansToDegrees(2 * M_PI));
    m_ui->doubleSpinBox_samplingFrequency->setMaximum(DBL_MAX);

    // Advanced features controls
    m_ui->widget_advancedFeatures->hide();
    m_ui->doubleSpinBox_amplitude->setMaximum(DBL_MAX);
    m_ui->doubleSpinBox_attenuationFactor->setMaximum(DBL_MAX);

    // Visualization features controls
    m_ui->widget_visualizationFeatures->hide();
    // Set minimum and maximum values for the data window size spinboxes
    // depending on the minimum and maximum size values of the plot window
    m_ui->spinBox_dataWindowWidth->setMinimum(m_plotWindow->minimumWidth());
    m_ui->spinBox_dataWindowWidth->setMaximum(m_plotWindow->maximumWidth());
    m_ui->spinBox_dataWindowHeight->setMinimum(m_plotWindow->minimumHeight());
    m_ui->spinBox_dataWindowHeight->setMaximum(m_plotWindow->maximumHeight());
    // Fill comboBox_lineStyle with available line styles (enumeration)
    m_ui->comboBox_lineStyle->addItem("None", QCPGraph::lsNone);
    m_ui->comboBox_lineStyle->addItem("Line", QCPGraph::lsLine);
}

void MainWindow::refreshFormValues()
{
    // Wave parameters controls: read values from the initial equation
    m_ui->doubleSpinBox_oscillationFrequency->setValue(m_equation->oscillationFrequency());
    m_ui->spinBox_numberOfPeriods->setValue(m_equation->numberOfPeriods());
    m_ui->doubleSpinBox_initialDelay->setValue(m_equation->initialDelay());
    m_ui->doubleSpinBox_samplingFrequency->setValue(m_equation->samplingFrequency());

    // Advanced features controls: read values from the initial equation
    m_ui->doubleSpinBox_amplitude->setValue(m_equation->amplitude());
    m_ui->doubleSpinBox_attenuationFactor->setValue(m_equation->attenuationFactor());

    // Visulization features controls
    // Set data window size to the minimum possible value
    m_ui->spinBox_dataWindowWidth->setValue(m_plotWindow->width());
    m_ui->spinBox_dataWindowHeight->setValue(m_plotWindow->height());
}

#include "plotWindow.h"
#include "ui_plotWindow.h"
#include <QDebug>


PlotWindow::PlotWindow(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PlotWindow)
{
    m_ui->setupUi(this);

    // Set some flags to hide maximize, minimize and close buttons
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Window);

    // Follow the QCustomPlot library instructions to create a graph and draw on it:
    // Create graph
    if (m_ui->widget_plot->graphCount() == 0)
        m_ui->widget_plot->addGraph();
    // Set the style of the graph
    m_ui->widget_plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    m_ui->widget_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    m_ui->widget_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    m_ui->widget_plot->graph(0)->setName("Equation");
    // Set axes labels
    m_ui->widget_plot->xAxis->setLabel("time [seconds]");
    m_ui->widget_plot->yAxis->setLabel("elongation [units]");
}

PlotWindow::~PlotWindow()
{
    delete m_ui;
}

bool PlotWindow::saveToFile(QString &fileName)
{
    return m_ui->widget_plot->savePng(fileName);
}

QCPGraph::LineStyle PlotWindow::getLineStyle()
{
    QCPGraph::LineStyle lineStyle = QCPGraph::lsNone;

    if (m_ui->widget_plot->graphCount() > 0)
        m_ui->widget_plot->graph(0)->lineStyle();

    return lineStyle;
}

void PlotWindow::loadEquation(SinusoidalEquation *equation)
{
    if (m_ui->widget_plot->graphCount() > 0)
    {
        // Assign the data of the equation to the graph
        m_ui->widget_plot->graph(0)->setData(equation->timeVector(), equation->elongationVector());
        // Set axes ranges, so we see all data
        m_ui->widget_plot->graph(0)->rescaleAxes();
        // Refresh graph
        m_ui->widget_plot->replot();
    }
}

void PlotWindow::changeLineStyle(QCPGraph::LineStyle style)
{
    if (m_ui->widget_plot->graphCount() > 0)
    {
        m_ui->widget_plot->graph(0)->setLineStyle(style);
        m_ui->widget_plot->replot();
    }
}

void PlotWindow::changeColor(QColor &color)
{
    if (m_ui->widget_plot->graphCount() > 0)
    {
        m_ui->widget_plot->graph(0)->setPen(QPen(color));
        m_ui->widget_plot->replot();
    }
}

void PlotWindow::resizeEvent(QResizeEvent *event)
{
    emit widgetResized(event->size());
}

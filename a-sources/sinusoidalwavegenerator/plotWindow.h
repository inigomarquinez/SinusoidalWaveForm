#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <qcustomplot.h>
#include <QWidget>
#include "sinusoidalEquation.h"


namespace Ui {
class PlotWindow;
}

/**
 * @brief Auxiliary widget used to show the graph of an equation.
 */
class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent widget.
     */
    PlotWindow(QWidget *parent = 0);
    /**
     * @brief Destructor.
     */
    ~PlotWindow();
    /**
     * @brief Saves the graph to a PNG file.
     * @param fileName Full path of the file where the graph will be saved.
     * @return true if the file is correctly saved, or false otherwise.
     */
    bool saveToFile(QString &fileName);
    /**
     * @brief Gets the line style used to draw the graph.
     * @return Line style currently being used.
     */
    QCPGraph::LineStyle getLineStyle();

signals:
    /**
     * @brief Signal emitted when the widget is resized.
     * @param size New size.
     */
    void widgetResized(const QSize &size);

public slots:
    /**
     * @brief Loads the equation to be drawn in the widget.
     * @param equation Equation to be drawn.
     */
    void loadEquation(SinusoidalEquation *equation);
    /**
     * @brief Changes the line style of the graph.
     * @param style New line style.
     */
    void changeLineStyle(QCPGraph::LineStyle style);
    /**
     * @brief Changes the color of the graph.
     * @param color New color.
     */
    void changeColor(QColor &color);

protected:
    /**
     * @brief Overrides the resizeEvent.
     * @param event Event parameters.
     */
    void resizeEvent(QResizeEvent *event);

private:
    /**
     * @brief Widget's user interface definition.
     */
    Ui::PlotWindow *m_ui;
};

#endif // PLOTWINDOW_H

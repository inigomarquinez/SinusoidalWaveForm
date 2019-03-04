#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotWindow.h"
#include "sinusoidalEquation.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief The main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     */
    MainWindow();
    /**
     * @brief Destructor.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Handles the event fired when the user changes the desired size of the visualization window.
     */
    void onDataWindowSizeChanged();
    /**
     * @brief Handles the event fired when the user selects a new line style from the combobox.
     * @param option Option selected in the combobox.
     */
    void onSelectedLineStyleChanged(int option);
    /**
     * @brief Handles the event fired when the users clicks the button to select a color.
     */
    void onSelectColorClicked();
    /**
     * @brief Handles the event fired when the user selects the 'Save to file' menu option.
     */
    void onSaveToFileTriggered();
    /**
     * @brief Handles the event fired when the equation has changed and needs to be redrawn.
     */
    void onEquationChanged();
    /**
     * @brief Handles the event fired when the user resizes the PlotWindow.
     * @param size New size of the window.
     */
    void onPlotWindowResized(const QSize &size);

protected:
    /**
     * @brief Overrides the closeEvent method.
     * @param event Event parameters.
     */
    void closeEvent(QCloseEvent*);
    /**
     * @brief Overrides the keyPressEvent method.
     * @param event Event parameters.
     */
    void keyPressEvent(QKeyEvent *event);

private:
    /**
     * @brief Configures the behaviour of the form controls.
     */
    void configureFormControls();
    /**
     * @brief Refreshes the values shown in the form controls.
     */
    void refreshFormValues();

    /**
     * @brief Widget's user interface definition.
     */
    Ui::MainWindow *m_ui;
    /**
     * @brief Equation to be drawn.
     */
    SinusoidalEquation *m_equation;
    /**
     * @brief Widget used to draw the equation.
     */
    PlotWindow *m_plotWindow;
};

#endif // MAINWINDOW_H

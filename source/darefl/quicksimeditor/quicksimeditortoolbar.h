// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H

#include <QToolBar>

class QProgressBar;
class QCheckBox;

//! Toolbar for QuickSimEditor.
//! Contains live simulation button, cancel button, simulation progress bar and settings buttons.

class QuickSimEditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit QuickSimEditorToolBar(QWidget* parent = nullptr);

signals:
    void realTimeRequest(bool);
    void runSimulationRequest();
    void cancelPressed();
    void instrumentSettingsRequest();
    void resetViewRequest();
    void plotSettingsRequest();

public slots:
    void onProgressChanged(int value);

private:
    void add_wide_separator();
    void setup_simulation_elements();
    void setup_plot_elements();

    QCheckBox* m_liveCheckbox{nullptr};
    QProgressBar* m_progressBar{nullptr}; //! Simulation progressbar.
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMEDITORTOOLBAR_H

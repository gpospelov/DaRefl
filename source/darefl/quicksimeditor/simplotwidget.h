// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_SIMPLOTWIDGET_H
#define DAREFL_QUICKSIMEDITOR_SIMPLOTWIDGET_H

#include <QWidget>

namespace ModelView
{
class GraphCanvas;
} // namespace ModelView

class ApplicationModels;

//! Presents simulation results together with reference experimental data on two canvas.
//! The top canvas contains graphs itself, bottom canvas their relative difference.

class SimPlotWidget : public QWidget
{
    Q_OBJECT

public:
    SimPlotWidget(QWidget* parent = nullptr);
    ~SimPlotWidget();

    void setModels(ApplicationModels* models);

    void updateViewport();

    void updateDiffPlot();

private:
    ApplicationModels* m_models{nullptr};
    ModelView::GraphCanvas* m_specularCanvas{nullptr};
    ModelView::GraphCanvas* m_diffCanvas{nullptr};
};

#endif // DAREFL_QUICKSIMEDITOR_SIMPLOTWIDGET_H

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/quicksimeditor/simplotwidget.h>

SimPlotWidget::SimPlotWidget(QWidget* parent) : QWidget(parent) {}

void SimPlotWidget::setModels(ApplicationModels* models)
{
    m_models = models;
}

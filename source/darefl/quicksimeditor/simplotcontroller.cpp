// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/quicksimeditor/simplotcontroller.h>

SimPlotController::SimPlotController(QObject* parent) {}

void SimPlotController::setModels(ApplicationModels* models)
{
    m_models = models;
}

SimPlotController::~SimPlotController() = default;

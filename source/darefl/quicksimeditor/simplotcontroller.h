// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H
#define DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H

#include <QObject>

class ApplicationModels;

//! Updates reference curve in JobItem when BemItem is changed.

class SimPlotController : public QObject
{
    Q_OBJECT
public:
    SimPlotController(QObject* parent = nullptr);
    ~SimPlotController();

    void setModels(ApplicationModels* models);

private:
    ApplicationModels* m_models{nullptr};
};

#endif // DAREFL_QUICKSIMEDITOR_SIMPLOTCONTROLLER_H

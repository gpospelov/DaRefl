// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMOPTIONSWIDGET_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMOPTIONSWIDGET_H

#include <QWidget>

//! Widget with specular settings (Q-scan etc) for QuickSimulationWidget.
//! Located under QuickSimulationEditor.

class QuickSimOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    QuickSimOptionsWidget(QWidget* parent = nullptr);
    ~QuickSimOptionsWidget();
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMOPTIONSWIDGET_H

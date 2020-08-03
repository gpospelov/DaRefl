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

namespace ModelView
{
class PropertyTreeView;
}

class ApplicationModels;

#include <QWidget>

//! Widget with specular settings (Q-scan etc) for QuickSimulationWidget.
//! Located under QuickSimulationEditor.

class QuickSimOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    QuickSimOptionsWidget(QWidget* parent = nullptr);
    ~QuickSimOptionsWidget();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    ModelView::PropertyTreeView* m_beamPropertyEditor{nullptr};

};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMOPTIONSWIDGET_H

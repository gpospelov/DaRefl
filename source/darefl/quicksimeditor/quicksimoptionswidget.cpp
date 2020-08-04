// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/quicksimeditor/quicksimoptionswidget.h>
#include <mvvm/widgets/propertytreeview.h>

QuickSimOptionsWidget::QuickSimOptionsWidget(QWidget* parent)
    : QWidget(parent), m_beamPropertyEditor(new ModelView::PropertyTreeView)

{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_beamPropertyEditor);
}

QuickSimOptionsWidget::~QuickSimOptionsWidget() = default;

void QuickSimOptionsWidget::setModels(ApplicationModels* models)
{
    auto instrument = models->instrumentModel()->topItem<SpecularInstrumentItem>();
    m_beamPropertyEditor->setItem(
        instrument->item<SpecularBeamItem>(SpecularInstrumentItem::P_BEAM));
}

QSize QuickSimOptionsWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize QuickSimOptionsWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

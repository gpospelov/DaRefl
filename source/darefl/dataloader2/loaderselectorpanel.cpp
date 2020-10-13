// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/dataloader2/importfilewidget_v2.h>
#include <darefl/dataloader2/loaderselectorpanel.h>

LoaderSelectorPanel::LoaderSelectorPanel(QWidget* parent)
    : QWidget(parent), m_fileSelectorWidget(new ImportFileWidgetV2)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_fileSelectorWidget);
}

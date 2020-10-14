// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/dataloader2/importtextview_v2.h>
#include <darefl/dataloader2/loaderpreviewpanel.h>

LoaderPreviewPanel::LoaderPreviewPanel(QWidget* parent)
    : QWidget(parent), m_textView(new ImportTextViewV2)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_textView);
}

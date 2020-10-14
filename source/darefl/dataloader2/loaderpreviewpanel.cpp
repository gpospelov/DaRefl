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

//! Sets raw text to the TextView.

void LoaderPreviewPanel::setTextData(const std::vector<std::string>& textData)
{
    m_textView->clear();
    for (const auto& str : textData)
        m_textView->appendPlainText(QString::fromStdString(str));
}

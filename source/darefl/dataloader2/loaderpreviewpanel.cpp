// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <QDebug>
#include <QVBoxLayout>
#include <darefl/dataloader2/importtextview_v2.h>
#include <darefl/dataloader2/loaderpreviewpanel.h>
#include <darefl/dataloader2/parserinterface.h>
#include <darefl/dataloader2/parseutils.h>

namespace
{
const std::string gray = ("#aab7b8");
const std::string blue = ("#1b4f72");

} // namespace

LoaderPreviewPanel::LoaderPreviewPanel(QWidget* parent)
    : QWidget(parent), m_textView(new ImportTextViewV2)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_textView);
}

//! Sets raw text to the TextView.

void LoaderPreviewPanel::setTextData(const std::vector<std::string>& )
{
}

void LoaderPreviewPanel::showData(const DataLoader::ParserInterface* parser)
{
    m_textView->clear();
    for (size_t index = 0; index < parser->totalLineCount(); ++index) {
        auto line_data = parser->getLine(index);

        auto parts = parser->parseResults(index);
        auto string_to_show = QString::fromStdString(
            DataLoader::AddHtmlColorTagToParts(line_data.first, parts, blue, gray));

        m_textView->appendHtml(string_to_show);
    }
    m_textView->moveCursor(QTextCursor::Start);
}

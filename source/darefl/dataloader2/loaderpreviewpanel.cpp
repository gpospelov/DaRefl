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

//! Returns text wrapped into colored tag.
QString get_colored_line(const QColor& color, const QString& text)
{
    QString result = QString("<div><font color=\"%1\">%2</font></div>").arg(color.name(), text);
    return result;
}

std::string line_color(DataLoader::ParserInterface::LineType line_type)
{
    return line_type == DataLoader::ParserInterface::DATA ? blue : gray;
}

} // namespace

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
    for (const auto& str : textData) {
        auto text = QString::fromStdString(str);

        m_textView->appendHtml(get_colored_line(QColor(Qt::red), text));
    }
    m_textView->moveCursor(QTextCursor::Start);
}

void LoaderPreviewPanel::showData(const DataLoader::ParserInterface* parser)
{
    m_textView->clear();
    for (size_t index = 0; index < parser->totalLineCount(); ++index) {
        auto line_data = parser->getLine(index);
        auto color = line_color(line_data.second);
        auto colored_line = DataLoader::AddHtmlColorTag(line_data.first, color);
        m_textView->appendHtml(QString::fromStdString(colored_line));
    }
    m_textView->moveCursor(QTextCursor::Start);
}

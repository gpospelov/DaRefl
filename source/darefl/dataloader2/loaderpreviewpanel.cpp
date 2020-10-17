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

namespace
{

//! Returns text wrapped into colored tag.
QString get_colored_line(const QColor& color, const QString& text)
{
    QString result = QString("<div><font color=\"%1\">%2</font></div>").arg(color.name(), text);
    return result;
}

QColor line_color(DataLoader::ParserInterface::LineType line_type)
{
    return line_type == DataLoader::ParserInterface::DATA ? QColor(Qt::black) : QColor(Qt::gray);
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
        QColor color = line_color(line_data.second);
        m_textView->appendHtml(get_colored_line(color, QString::fromStdString(line_data.first)));
    }
    m_textView->moveCursor(QTextCursor::Start);
}

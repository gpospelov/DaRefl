// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <darefl/dataloader2/parsingpropertywidget.h>
#include <mvvm/widgets/widgetutils.h>

namespace {
QLabel* createBoldLabel(const QString& text)
{
    auto result = new QLabel(text);
    QFont font = result->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.05);
//    font.setBold(true);
    result->setFont(font);
    return result;
}
}

ParsingPropertyWidget::ParsingPropertyWidget(QWidget* parent)
    : QWidget(parent), m_customSeparatorLineEdit(new QLineEdit)
{
    auto layout = new QVBoxLayout(this);

    auto grid_layout = new QGridLayout;

    auto automaticRadio = new QRadioButton;
    automaticRadio->setText("Automatic");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    auto customRadio = new QRadioButton;
    customRadio->setText("Custom");


    grid_layout->addWidget(createBoldLabel("Separator"), 0, 0, 1, 3, Qt::AlignLeft);

    grid_layout->addWidget(automaticRadio, 1, 0, Qt::AlignLeft);
    grid_layout->addWidget(spaceRadio, 1, 1, Qt::AlignLeft);
    grid_layout->addWidget(commaRadio, 1, 2, Qt::AlignLeft);

    grid_layout->addWidget(customRadio, 2, 0, Qt::AlignLeft);
    m_customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM()*3);
    grid_layout->addWidget(m_customSeparatorLineEdit, 2, 1, Qt::AlignLeft);

    // ---
    grid_layout->addWidget(createBoldLabel("Ignore lines"), 3, 0, 1, 3, Qt::AlignLeft);

    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Starting from");
    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setText("Line numbers");
    auto lineNumbersTextEdit = new QLineEdit;

    grid_layout->addWidget(startingFromRadio, 4, 0, Qt::AlignLeft);
    grid_layout->addWidget(lineNumbersRadio, 5, 0, Qt::AlignLeft);
    grid_layout->addWidget(lineNumbersTextEdit, 5, 1, Qt::AlignLeft);

    layout->addLayout(grid_layout);
}

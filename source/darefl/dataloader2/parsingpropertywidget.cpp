// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <darefl/dataloader2/parsingpropertywidget.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{
QLabel* createBoldLabel(const QString& text)
{
    auto result = new QLabel(text);
    QFont font = result->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.05);
    //    font.setBold(true);
    result->setFont(font);
    return result;
}
} // namespace

ParsingPropertyWidget::ParsingPropertyWidget(QWidget* parent)
    : QWidget(parent), m_customSeparatorLineEdit(new QLineEdit)
{
    auto layout = new QVBoxLayout(this);

    layout->addLayout(createGridLayout());
    layout->addStretch(1);
}

QGridLayout* ParsingPropertyWidget::createGridLayout()
{
    auto grid_layout = new QGridLayout;

    addSectionLabel("Separator", grid_layout);
    addSeparatorBlock(grid_layout);
    addSectionLabel("Ignore lines", grid_layout);
    addIgnoreLinesBlock(grid_layout);
    addSectionLabel("Import targed", grid_layout);
    addImportToBlock(grid_layout);

    return grid_layout;
}

void ParsingPropertyWidget::addSectionLabel(const QString& text, QGridLayout* layout)
{
    int row = layout->rowCount();
    layout->addWidget(createBoldLabel(text), row, 0, 1, 3, Qt::AlignLeft);
}

void ParsingPropertyWidget::addSeparatorBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto automaticRadio = new QRadioButton;
    automaticRadio->setText("Automatic");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(automaticRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(spaceRadio, row, 2, Qt::AlignLeft);
    layout->addWidget(commaRadio, row, 3, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto customRadio = new QRadioButton;
    customRadio->setText("Custom");
    m_customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM() * 4);

    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(customRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(m_customSeparatorLineEdit, row, 2, Qt::AlignLeft);
}

void ParsingPropertyWidget::addIgnoreLinesBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Starting from");
    auto startingFromTextEdit = new QLineEdit;
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(startingFromRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(startingFromTextEdit, row, 2, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setText("Line numbers");
    auto lineNumbersTextEdit = new QLineEdit;
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(lineNumbersRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(lineNumbersTextEdit, row, 2, Qt::AlignLeft);
}

void ParsingPropertyWidget::addImportToBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto newCanvasRadio = new QRadioButton;
    newCanvasRadio->setText("New canvas");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(newCanvasRadio, row, 1, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto existingCanvasRadio = new QRadioButton;
    existingCanvasRadio->setText("Existing canvas");
    auto existingCanvasCombo = new QComboBox;
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(existingCanvasRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(existingCanvasCombo, row, 2, Qt::AlignLeft);
}

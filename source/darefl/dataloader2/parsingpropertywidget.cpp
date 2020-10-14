// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QButtonGroup>
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

ParsingPropertyWidget::ParsingPropertyWidget(QWidget* parent) : QWidget(parent)
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
    automaticRadio->setToolTip("Try to guess column separator");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    spaceRadio->setToolTip("Use empty space as column separator");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    commaRadio->setToolTip("Use comma as column separator");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(automaticRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(spaceRadio, row, 2, Qt::AlignLeft);
    layout->addWidget(commaRadio, row, 3, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto customRadio = new QRadioButton;
    customRadio->setText("Custom");
    customRadio->setToolTip("Use given symbols as column separator");
    auto customSeparatorLineEdit = new QLineEdit;
    customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM() * 4);
    customSeparatorLineEdit->setToolTip("Use given symbols as column separator");

    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(customRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(customSeparatorLineEdit, row, 2, Qt::AlignLeft);

    auto buttonGroup = new QButtonGroup;
    buttonGroup->addButton(automaticRadio);
    buttonGroup->addButton(spaceRadio);
    buttonGroup->addButton(commaRadio);
    buttonGroup->addButton(customRadio);
}

void ParsingPropertyWidget::addIgnoreLinesBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Starting from");
    startingFromRadio->setAutoExclusive(false);
    startingFromRadio->setChecked(true);
    startingFromRadio->setToolTip("All lines starting from a given character(s) will be ignored");
    auto startingFromTextEdit = new QLineEdit;
    startingFromTextEdit->setText("#");
    startingFromTextEdit->setToolTip(
        "All lines starting from a given character(s) will be ignored");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(startingFromRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(startingFromTextEdit, row, 2, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setAutoExclusive(false);
    lineNumbersRadio->setText("Line numbers");
    lineNumbersRadio->setToolTip("All lines with numbers matching the pattern will be ignored");
    auto lineNumbersTextEdit = new QLineEdit;
    lineNumbersTextEdit->setPlaceholderText("Example: 1-5,42");
    lineNumbersTextEdit->setToolTip("All lines with numbers matching the pattern will be ignored");
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
    newCanvasRadio->setChecked(true);
    newCanvasRadio->setToolTip("Data will be imported into the new canvas");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(newCanvasRadio, row, 1, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto existingCanvasRadio = new QRadioButton;
    existingCanvasRadio->setText("Existing canvas");
    existingCanvasRadio->setToolTip("Data will be imported into existing canvas");
    auto existingCanvasCombo = new QComboBox;
    existingCanvasCombo->setToolTip("Data will be imported into existing canvas");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(existingCanvasRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(existingCanvasCombo, row, 2, Qt::AlignLeft);

    auto buttonGroup = new QButtonGroup;
    buttonGroup->addButton(newCanvasRadio);
    buttonGroup->addButton(existingCanvasRadio);
}

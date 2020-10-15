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
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/parsingpropertywidget.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{

//! Creates widget with label and little space above. Intended fro grid layouts.
QWidget* createSectionWidget(const QString& text)
{
    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);
    layout->addSpacing(10);
    auto label = new QLabel(text);
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.05);
    //    font.setBold(true);
    label->setFont(font);
    layout->addWidget(label);
    return widget;
}

} // namespace

ParsingPropertyWidget::ParsingPropertyWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(createGridLayout());
    layout->addStretch(1);
}

DataLoader::ParsingOptions ParsingPropertyWidget::parsingOptions() const
{
    return m_options;
}

void ParsingPropertyWidget::onParsingPropertiesChange()
{
    qDebug() << "option"
             << "header:" << QString::fromStdString(m_options.m_header_prefix)
             << "separator:" << QString::fromStdString(m_options.m_separator) << "pattern"
             << QString::fromStdString(m_options.m_skip_index_pattern);
    emit parsingPropertiesHaveChanged();
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

    // make first colum with invisible label fixed
    for (int col = 0; col < grid_layout->columnCount(); ++col)
        grid_layout->setColumnStretch(col, 10);
    grid_layout->setColumnStretch(0, 0);

    return grid_layout;
}

void ParsingPropertyWidget::addSectionLabel(const QString& text, QGridLayout* layout)
{
    int row = layout->rowCount();
    layout->addWidget(createSectionWidget(text), row, 0, 1, 3, Qt::AlignLeft);
}

void ParsingPropertyWidget::addSeparatorBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto automaticRadio = new QRadioButton;
    automaticRadio->setChecked(true);
    automaticRadio->setText("Automatic");
    automaticRadio->setToolTip("Try to guess column separator");
    connect(automaticRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator.clear();
        onParsingPropertiesChange();
    });

    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    spaceRadio->setToolTip("Use empty space as column separator");
    connect(spaceRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = " ";
        onParsingPropertiesChange();
    });

    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    commaRadio->setToolTip("Use comma as column separator");
    connect(commaRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = ",";
        onParsingPropertiesChange();
    });

    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(automaticRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(spaceRadio, row, 2, Qt::AlignLeft);
    layout->addWidget(commaRadio, row, 3, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto customSeparatorLineEdit = new QLineEdit;
    auto customRadio = new QRadioButton;

    customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM() * 4);
    customSeparatorLineEdit->setToolTip("Use given symbols as column separator");
    auto on_custom_lineedit = [this, customSeparatorLineEdit, customRadio]() {
        if (customRadio->isChecked())
            m_options.m_separator = customSeparatorLineEdit->text().toStdString();
        onParsingPropertiesChange();
    };
    connect(customSeparatorLineEdit, &QLineEdit::editingFinished, on_custom_lineedit);

    customRadio->setText("Custom");
    customRadio->setToolTip("Use given symbols as column separator");
    auto on_custom_separator = [this, customSeparatorLineEdit](auto) {
        m_options.m_separator = customSeparatorLineEdit->text().toStdString();
        onParsingPropertiesChange();
    };
    connect(customRadio, &QRadioButton::clicked, on_custom_separator);

    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(customRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(customSeparatorLineEdit, row, 2, Qt::AlignLeft);

    auto buttonGroup = new QButtonGroup;
    buttonGroup->addButton(automaticRadio, AUTOMATIC);
    buttonGroup->addButton(spaceRadio, SPACE);
    buttonGroup->addButton(commaRadio, COMMA);
    buttonGroup->addButton(customRadio, CUSTOM);

    auto on_button_group = [this](int id) { qDebug() << "id" << id; };
    connect(buttonGroup, &QButtonGroup::idClicked, on_button_group);
}

void ParsingPropertyWidget::addIgnoreLinesBlock(QGridLayout* layout)
{
    // row
    int row = layout->rowCount();
    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Starting from");
    startingFromRadio->setAutoExclusive(false);
    startingFromRadio->setChecked(true);
    startingFromRadio->setToolTip("Ignore lines starting from a given character(s)");
    auto startingFromTextEdit = new QLineEdit;
    startingFromTextEdit->setText("#");
    startingFromTextEdit->setToolTip("Ignore lines starting from a given character(s)");
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(startingFromRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(startingFromTextEdit, row, 2, Qt::AlignLeft);

    // row
    row = layout->rowCount();
    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setAutoExclusive(false);
    lineNumbersRadio->setText("Line numbers");
    lineNumbersRadio->setToolTip("Ignore lines with line numbers matching the pattern");
    auto lineNumbersTextEdit = new QLineEdit;
    lineNumbersTextEdit->setPlaceholderText("Example: 1-5,42");
    lineNumbersTextEdit->setToolTip("Ignore lines with line numbers matching the pattern");
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

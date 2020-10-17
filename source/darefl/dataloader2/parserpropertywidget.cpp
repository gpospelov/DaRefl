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
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <darefl/dataloader2/parserpropertywidget.h>
#include <darefl/dataloader2/defaultparser.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{

//! Creates widget with label and little space above. Intended for grid layouts.
QWidget* createSectionWidget(const QString& text)
{
    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);
    layout->addSpacing(10);
    auto label = new QLabel(text);
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.05);
    label->setFont(font);
    layout->addWidget(label);
    return widget;
}

} // namespace

ParserPropertyWidget::ParserPropertyWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(createGridLayout());
    layout->addStretch(1);
}

ParserPropertyWidget::~ParserPropertyWidget() = default;

std::unique_ptr<DataLoader::ParserInterface> ParserPropertyWidget::createParser() const
{
    return std::make_unique<DataLoader::DefaultParser>(m_options);
}

void ParserPropertyWidget::onParserPropertyChange()
{
    qDebug() << "option"
             << "header:" << QString::fromStdString(m_options.m_header_prefix)
             << "separator:" << QString::fromStdString(m_options.m_separator) << "pattern"
             << QString::fromStdString(m_options.m_skip_index_pattern);
    emit parserPropertyChanged();
}

QGridLayout* ParserPropertyWidget::createGridLayout()
{
    auto grid_layout = new QGridLayout;

    addSectionLabel("Separator", grid_layout);
    auto buttonGroup = new QButtonGroup;
    addStandardSeparatorRow(grid_layout, buttonGroup);
    addCustomSeparatorRow(grid_layout, buttonGroup);

    addSectionLabel("Ignore lines", grid_layout);
    addIgnoreStringPatternRow(grid_layout);
    addIgnoreNumbersPatternRow(grid_layout);

    addSectionLabel("Import targed", grid_layout);
    addImportToBlock(grid_layout);

    // make first colum with invisible label fixed
    for (int col = 0; col < grid_layout->columnCount(); ++col)
        grid_layout->setColumnStretch(col, 10);
    grid_layout->setColumnStretch(0, 0);

    return grid_layout;
}

void ParserPropertyWidget::addSectionLabel(const QString& text, QGridLayout* layout)
{
    int row = layout->rowCount();
    layout->addWidget(createSectionWidget(text), row, 0, 1, 3, Qt::AlignLeft);
}

//! Adds row to the grid: elements with standard separator settings.

void ParserPropertyWidget::addStandardSeparatorRow(QGridLayout* layout, QButtonGroup* group)
{
    // automatic separator
    int row = layout->rowCount();
    auto automaticRadio = new QRadioButton;
    automaticRadio->setChecked(true);
    automaticRadio->setText("Automatic");
    automaticRadio->setToolTip("Try to guess column separator");
    connect(automaticRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator.clear();
        onParserPropertyChange();
    });

    // space separator
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    spaceRadio->setToolTip("Use empty space as column separator");
    connect(spaceRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = " ";
        onParserPropertyChange();
    });

    // comma separator
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    commaRadio->setToolTip("Use comma as column separator");
    connect(commaRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = ",";
        onParserPropertyChange();
    });

    // adding all to layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(automaticRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(spaceRadio, row, 2, Qt::AlignLeft);
    layout->addWidget(commaRadio, row, 3, Qt::AlignLeft);
    group->addButton(automaticRadio);
    group->addButton(spaceRadio);
    group->addButton(commaRadio);
}

//! Adds row to the grid: elements with custom separator settings.

void ParserPropertyWidget::addCustomSeparatorRow(QGridLayout* layout, QButtonGroup* group)
{
    int row = layout->rowCount();
    auto customSeparatorLineEdit = new QLineEdit;
    auto customRadio = new QRadioButton;

    // custom separator radio
    customRadio->setText("Custom");
    customRadio->setToolTip("Use given symbols as column separator");
    auto on_custom_separator = [this, customSeparatorLineEdit](auto) {
        m_options.m_separator = customSeparatorLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(customRadio, &QRadioButton::clicked, on_custom_separator);

    // custom separator text
    customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM() * 4);
    customSeparatorLineEdit->setToolTip("Use given symbols as column separator");
    auto on_custom_lineedit = [this, customSeparatorLineEdit, customRadio]() {
        if (customRadio->isChecked())
            m_options.m_separator = customSeparatorLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(customSeparatorLineEdit, &QLineEdit::editingFinished, on_custom_lineedit);

    // adding to the layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(customRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(customSeparatorLineEdit, row, 2, Qt::AlignLeft);
    group->addButton(customRadio);
}

//! Adds row to the grid: elements with pattern to ignore lines.

void ParserPropertyWidget::addIgnoreStringPatternRow(QGridLayout* layout)
{
    auto startingFromRadio = new QRadioButton;
    auto startingFromLineEdit = new QLineEdit;

    // radio settings
    int row = layout->rowCount();
    startingFromRadio->setText("Starting from");
    startingFromRadio->setAutoExclusive(false);
    startingFromRadio->setChecked(true);
    startingFromRadio->setToolTip("Ignore lines starting from a given character(s)");
    auto on_startingfrom_radio = [this, startingFromLineEdit](auto checked) {
        m_options.m_header_prefix =
            checked ? startingFromLineEdit->text().toStdString() : std::string();
        onParserPropertyChange();
    };
    connect(startingFromRadio, &QRadioButton::clicked, on_startingfrom_radio);

    // line edit settings
    startingFromLineEdit->setText("#");
    startingFromLineEdit->setToolTip("Ignore lines starting from a given character(s)");
    auto on_startingfrom_lineedit = [this, startingFromRadio, startingFromLineEdit]() {
        if (startingFromRadio->isChecked())
            m_options.m_header_prefix = startingFromLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(startingFromLineEdit, &QLineEdit::editingFinished, on_startingfrom_lineedit);

    // adding to layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(startingFromRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(startingFromLineEdit, row, 2, Qt::AlignLeft);
}

//! Adds row to the grid: elements with pattern to ignore line numbers.

void ParserPropertyWidget::addIgnoreNumbersPatternRow(QGridLayout* layout)
{
    auto lineNumbersRadio = new QRadioButton;
    auto lineNumbersLineEdit = new QLineEdit;

    // radio settings
    int row = layout->rowCount();
    lineNumbersRadio->setAutoExclusive(false);
    lineNumbersRadio->setText("Line numbers");
    lineNumbersRadio->setToolTip("Ignore lines with line numbers matching the pattern");
    auto on_linenumbers_radio = [this, lineNumbersLineEdit](auto checked) {
        m_options.m_skip_index_pattern =
            checked ? lineNumbersLineEdit->text().toStdString() : std::string();
        onParserPropertyChange();
    };
    connect(lineNumbersRadio, &QRadioButton::clicked, on_linenumbers_radio);

    // line edit settings
    lineNumbersLineEdit->setPlaceholderText("Example: 1-5,42");
    lineNumbersLineEdit->setToolTip("Ignore lines with line numbers matching the pattern");
    auto on_linenumbers_lineedit = [this, lineNumbersRadio, lineNumbersLineEdit]() {
        if (lineNumbersRadio->isChecked())
            m_options.m_skip_index_pattern = lineNumbersLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(lineNumbersLineEdit, &QLineEdit::editingFinished, on_linenumbers_lineedit);

    // adding to the layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(lineNumbersRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(lineNumbersLineEdit, row, 2, Qt::AlignLeft);
}

//! Adds row to the grid: elements related to the import target.

void ParserPropertyWidget::addImportToBlock(QGridLayout* layout)
{
    auto newCanvasRadio = new QRadioButton;
    auto existingCanvasRadio = new QRadioButton;

    // radio settings
    newCanvasRadio->setText("New canvas");
    newCanvasRadio->setChecked(true);
    newCanvasRadio->setToolTip("Data will be imported into the new canvas");

    // combo settings
    existingCanvasRadio->setText("Existing canvas");
    existingCanvasRadio->setToolTip("Data will be imported into existing canvas");
    auto existingCanvasCombo = new QComboBox;
    existingCanvasCombo->setToolTip("Data will be imported into existing canvas");

    // adding to the layout
    int row = layout->rowCount();
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(newCanvasRadio, row, 1, Qt::AlignLeft);
    row = layout->rowCount();
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(existingCanvasRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(existingCanvasCombo, row, 2, Qt::AlignLeft);
    auto buttonGroup = new QButtonGroup;
    buttonGroup->addButton(newCanvasRadio);
    buttonGroup->addButton(existingCanvasRadio);
}

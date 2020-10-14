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
#include <QComboBox>
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

    layout->addLayout(createGridLayout());
//    layout->addWidget(createGroup());
    layout->addLayout(createSeparatorLayout());
    layout->addSpacing(20);
    layout->addLayout(createLinesLayout());
    layout->addStretch(1);
}

QGridLayout* ParsingPropertyWidget::createGridLayout()
{
    auto grid_layout = new QGridLayout;

    // row 0
    grid_layout->addWidget(createBoldLabel("Separator"), 0, 0, 1, 3, Qt::AlignLeft);

    // row 1
    auto automaticRadio = new QRadioButton;
    automaticRadio->setText("Automatic");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    grid_layout->addWidget(new QLabel("  "), 1, 0, Qt::AlignLeft);
    grid_layout->addWidget(automaticRadio, 1, 1, Qt::AlignLeft);
    grid_layout->addWidget(spaceRadio, 1, 2, Qt::AlignLeft);
    grid_layout->addWidget(commaRadio, 1, 3, Qt::AlignLeft);

    // row 2
    auto customRadio = new QRadioButton;
    customRadio->setText("Custom");
    m_customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM()*4);

    grid_layout->addWidget(new QLabel("  "), 2, 0, Qt::AlignLeft);
    grid_layout->addWidget(customRadio, 2, 1, Qt::AlignLeft);
    grid_layout->addWidget(m_customSeparatorLineEdit, 2, 2, Qt::AlignLeft);

    // row 3
    grid_layout->addWidget(createBoldLabel("Ignore lines"), 3, 0, 1, 3, Qt::AlignLeft);

    // row 4
    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Starting from");
    auto startingFromTextEdit = new QLineEdit;
    grid_layout->addWidget(new QLabel("  "), 4, 0, Qt::AlignLeft);
    grid_layout->addWidget(startingFromRadio, 4, 1, Qt::AlignLeft);
    grid_layout->addWidget(startingFromTextEdit, 4, 2, Qt::AlignLeft);

    // row 5
    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setText("Line numbers");
    auto lineNumbersTextEdit = new QLineEdit;
    grid_layout->addWidget(new QLabel("  "), 5, 0, Qt::AlignLeft);
    grid_layout->addWidget(lineNumbersRadio, 5, 1, Qt::AlignLeft);
    grid_layout->addWidget(lineNumbersTextEdit, 5, 2, Qt::AlignLeft);

    // row 6
    grid_layout->addWidget(createBoldLabel("Import targed"), 6, 0, 1, 3, Qt::AlignLeft);

    // row 7
    auto newCanvasRadio = new QRadioButton;
    newCanvasRadio->setText("New canvas");
    grid_layout->addWidget(new QLabel("  "), 7, 0, Qt::AlignLeft);
    grid_layout->addWidget(newCanvasRadio, 7, 1, Qt::AlignLeft);

    // row 8
    auto existingCanvasRadio = new QRadioButton;
    existingCanvasRadio->setText("Existing canvas");
    auto existingCanvasCombo = new QComboBox;
    grid_layout->addWidget(new QLabel("  "), 8, 0, Qt::AlignLeft);
    grid_layout->addWidget(existingCanvasRadio, 8, 1, Qt::AlignLeft);
    grid_layout->addWidget(existingCanvasCombo, 8, 2, Qt::AlignLeft);

    return grid_layout;
}

QWidget* ParsingPropertyWidget::createGroup()
{
    auto result = new QGroupBox("Separator");
    auto layout = new QHBoxLayout(result);

    auto automaticRadio = new QRadioButton;
    automaticRadio->setText("Automatic");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");

    layout->addWidget(automaticRadio);
    layout->addWidget(spaceRadio);
    layout->addWidget(commaRadio);

    return result;

}

QBoxLayout* ParsingPropertyWidget::createSeparatorLayout()
{
    auto result = new QVBoxLayout;

    result->addWidget(createBoldLabel("Separator"), 0, Qt::AlignLeft);

    auto hlayout0 = new QHBoxLayout;
    hlayout0->addSpacing(20);

    auto grid = new QGridLayout;
    hlayout0->addLayout(grid);

    auto automaticRadio = new QRadioButton;
    automaticRadio->setText("Automatic");
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");

    grid->addWidget(automaticRadio, 0, 0);
    grid->addWidget(spaceRadio, 0, 1);
    grid->addWidget(commaRadio, 0, 2);

    // ---
    auto customRadio = new QRadioButton;
    customRadio->setText("Custom");

    auto customEdit = new QLineEdit();

    grid->addWidget(customRadio, 1, 0);
    grid->addWidget(customEdit,1, 1);

    result->addLayout(hlayout0);
    return result;
}

QBoxLayout* ParsingPropertyWidget::createLinesLayout()
{
    auto result = new QVBoxLayout;

    result->addWidget(createBoldLabel("Ignore lines"), 0, Qt::AlignLeft);

    auto hlayout0 = new QHBoxLayout;
    hlayout0->addSpacing(20);

    auto grid = new QGridLayout;
    hlayout0->addLayout(grid);

    auto startingFromRadio = new QRadioButton;
    startingFromRadio->setText("Staring from");
    auto startingFromText = new QLineEdit;
    grid->addWidget(startingFromRadio, 0, 0);
    grid->addWidget(startingFromText, 0, 1);
    grid->addWidget(new QLabel(" "), 0, 2);

    auto lineNumbersRadio = new QRadioButton;
    lineNumbersRadio->setText("Line numbers");
    auto lineNumbersText = new QLineEdit;

    grid->addWidget(lineNumbersRadio, 1, 0);
    grid->addWidget(lineNumbersText, 1, 1);

    auto spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    grid->addWidget(spacer, 1, 2);

    result->addLayout(hlayout0);
    return result;
}

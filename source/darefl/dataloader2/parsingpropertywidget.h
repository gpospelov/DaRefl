// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H
#define DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H

#include <QWidget>

class QLineEdit;
class QBoxLayout;
class QLayout;
class QGridLayout;

//! Panel or ASCII parser properties.

class ParsingPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    ParsingPropertyWidget(QWidget* parent = nullptr);

private:
    QGridLayout* createGridLayout();

    void addSectionLabel(const QString& text, QGridLayout* layout);
    void addSeparatorBlock(QGridLayout* layout);
    void addIgnoreLinesBlock(QGridLayout* layout);
    void addImportToBlock(QGridLayout* layout);

    QLineEdit* m_customSeparatorLineEdit{nullptr};
};

#endif // DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H

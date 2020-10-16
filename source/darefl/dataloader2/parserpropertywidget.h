// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_PARSERPROPERTYWIDGET_H
#define DAREFL_DATALOADER2_PARSERPROPERTYWIDGET_H

#include <QWidget>
#include <darefl/dataloader2/dataloader_types.h>

class QGridLayout;
class QButtonGroup;

//! Panel for ASCII parser properties.
//! Contains selection of separator symbols, patterns to skip lines, and import target settings.

class ParserPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    ParserPropertyWidget(QWidget* parent = nullptr);

    DataLoader::ParserOptions parsingOptions() const;

signals:
    void parsingPropertiesHaveChanged();

private slots:
    void onParsingPropertiesChange();

private:
    QGridLayout* createGridLayout();

    void addSectionLabel(const QString& text, QGridLayout* layout);
    void addStandardSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addCustomSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addIgnoreStringPatternRow(QGridLayout* layout);
    void addIgnoreNumbersPatternRow(QGridLayout* layout);
    void addImportToBlock(QGridLayout* layout);

    DataLoader::ParserOptions m_options;
};

#endif // DAREFL_DATALOADER2_PARSERPROPERTYWIDGET_H
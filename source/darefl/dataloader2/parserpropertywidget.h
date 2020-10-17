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
#include <memory>
#include <darefl/dataloader2/dataloader_types.h>

namespace DataLoader {
class ParserInterface;
}

class QGridLayout;
class QButtonGroup;

//! Panel to setup ASCII parser. Intended to configure DefaultParser: contains selection of
//! separator symbols, patterns to ignore lines, and import target settings.

class ParserPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    ParserPropertyWidget(QWidget* parent = nullptr);
    ~ParserPropertyWidget();

    std::unique_ptr<DataLoader::ParserInterface> createParser() const;

signals:
    void parserPropertyChanged();

private slots:
    void onParserPropertyChange();

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

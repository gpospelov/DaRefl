// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H
#define DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H

#include <QWidget>
#include <darefl/dataloader/dataloader_types.h>
#include <memory>

namespace DataLoader
{
class ParserInterface;
}

class QGridLayout;
class QButtonGroup;
class QComboBox;
class QLineEdit;

//! Panel to setup ASCII parser. Intended for concrete class DefaultParser.
//! Contains selection of separator symbols, patterns to ignore lines, and import target settings.

class ParserPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    enum SeparatorButtonId { AUTOMATIC, SPACE, COMMA, CUSTOM };

    ParserPropertyWidget(QWidget* parent = nullptr);
    ~ParserPropertyWidget();

    std::unique_ptr<DataLoader::ParserInterface> createParser() const;

    void setTargetCanvas(const QStringList& canvas_names, int current_index);

signals:
    void parserPropertyChanged();
    int targetCanvasChanged(int canvas_index);

private slots:
    void onParserPropertyChange();

private:
    void readSettings();
    void writeSettings();
    QGridLayout* createGridLayout();

    void addSectionLabel(const QString& text, QGridLayout* layout);
    void addStandardSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addCustomSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addIgnoreStringPatternRow(QGridLayout* layout);
    void addIgnoreNumbersPatternRow(QGridLayout* layout);
    void addImportToBlock(QGridLayout* layout);

    DataLoader::ParserOptions m_options;
    QButtonGroup* m_separatorButtonGroup{nullptr};
    QComboBox* m_targetCanvasCombo{nullptr};
    QLineEdit* m_customSeparatorLineEdit{nullptr};
};

#endif // DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H

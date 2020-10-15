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
#include <darefl/dataloader2/dataloader_types.h>

class QLineEdit;
class QBoxLayout;
class QLayout;
class QGridLayout;

//! Panel or ASCII parser properties.

class ParsingPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    enum ButtonID {
        AUTOMATIC,
        SPACE,
        COMMA,
        CUSTOM,
        STARTINGFROM,
        LINENUMBERS,
        NEWCANVAS,
        EXISTINGCANVAS
    };

    ParsingPropertyWidget(QWidget* parent = nullptr);

    DataLoader::ParsingOptions parsingOptions() const;

signals:
    void parsingPropertiesHaveChanged();

private slots:
    void onParsingPropertiesChange();

private:
    QGridLayout* createGridLayout();

    void addSectionLabel(const QString& text, QGridLayout* layout);
    void addSeparatorBlock(QGridLayout* layout);
    void addIgnoreLinesBlock(QGridLayout* layout);
    void addImportToBlock(QGridLayout* layout);

    DataLoader::ParsingOptions m_options;
};

#endif // DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H

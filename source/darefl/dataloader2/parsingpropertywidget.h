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

//! Panel or ASCII parser properties.

class ParsingPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    ParsingPropertyWidget(QWidget* parent = nullptr);

private:
    QLineEdit* m_customSeparatorLineEdit{nullptr};
};

#endif // DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H

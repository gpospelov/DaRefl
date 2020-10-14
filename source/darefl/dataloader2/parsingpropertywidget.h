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

//! Panel with settings for ASCII multi-column file parsing.

class ParsingPropertyWidget : public QWidget
{
    Q_OBJECT

public:
    ParsingPropertyWidget(QWidget* parent = nullptr);
};

#endif // DAREFL_DATALOADER2_PARSINGPROPERTYWIDGET_H

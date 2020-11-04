// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H

#include <QWidget>

class ApplicationModels;

//! Main window to import user data.

class ImportDataView : public QWidget
{
    Q_OBJECT
public:
    ImportDataView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    ApplicationModels* m_models{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAVIEW_H

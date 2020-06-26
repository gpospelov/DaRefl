// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/mainwindow/importwindow.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/importdatawidgets/importdataeditor.h>
#include <QVBoxLayout>

ImportWindow::ImportWindow(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), models(models)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor(models->realDataModel()));
}

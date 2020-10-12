// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTFILTERWIDGET_H
#define DAREFL_FAMOUSLOADER_IMPORTFILTERWIDGET_H

#include <QWidget>
#include <vector>

#include <darefl/dataloader/importlogic.h>

QT_BEGIN_NAMESPACE
class QListWidget;
class QSettings;
QT_END_NAMESPACE

namespace DataImportLogic
{
class ImportLogic;
}

namespace DataImportGui
{

class LineFilterWidget;

//! This is the main dialog for the data loader
class ImportFilterWidget : public QWidget
{
    Q_OBJECT

public:
    ImportFilterWidget(DataImportLogic::ImportLogic* import_logic, QWidget* parent = nullptr);
    ~ImportFilterWidget() = default;

    void addLineFilter();
    void removeLineFilter();

    void readSettings();
    void writeSettings();

signals:
    void parameterChanged();
    void namesChanged();
    void typesChanged();

private slots:
    void processNameChanged(std::string name, LineFilterWidget* widget);
    void processTypeChanged(std::string type, LineFilterWidget* widget);

private:
    void setLayout();
    void initialise();
    void connectAll();
    void resetFromLineFilters() const;
    void handleInternalMoveEvent();

private:
    DataImportLogic::ImportLogic* m_importLogic;

    std::vector<LineFilterWidget*> m_lineFilterWidgets;

    // --------------------------------
    // --DEVELOP-- (Can be changed again to revert all functionalities)
    // To revert: remove non commented code and uncomment commented code

    // QListWidget* p_list_widget;
    
    // --------------------------------
};

} // End of namespace DataImportGui

#endif // DAREFL_FAMOUSLOADER_IMPORTFILTERWIDGET_H

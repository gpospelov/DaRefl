// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SETTINGSVIEW_SETTINGSVIEW_H
#define DAREFL_SETTINGSVIEW_SETTINGSVIEW_H

#include <QWidget>

class QTabWidget;
class ApplicationModels;

//! Settings view. Most right tab of MainWindow.

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView(ApplicationModels* models, QWidget* parent = nullptr);

private:
    void init_tabs();

    QTabWidget* m_tabWidget{nullptr};
    ApplicationModels* m_models{nullptr};
};

#endif // DAREFL_SETTINGSVIEW_SETTINGSVIEW_H

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

//! Settings view. Most right tab of MainWindow

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView(QWidget* parent = nullptr);
};

#endif // DAREFL_SETTINGSVIEW_SETTINGSVIEW_H

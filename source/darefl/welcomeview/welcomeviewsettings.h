// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_WELCOMEVIEWSETTINGS_H
#define DAREFL_WELCOMEVIEW_WELCOMEVIEWSETTINGS_H

#include <QString>
#include <QStringList>

//! Collection of settings for WelcomeView. Used to save last directory selected by the user,
//! and similar. Relies on QSettings machinery.

class WelcomeViewSettings
{
public:
    WelcomeViewSettings();
    ~WelcomeViewSettings();

    QString currentWorkdir() const;

    void updateWorkdirFromSelection(const QString& dirname);

    QStringList recentProjects();

    void addToRecentProjects(const QString& dirname);

private:
    void writeSettings();
    void readSettings();

    QString m_current_workdir;
    QStringList m_recent_projects;
};

#endif  // DAREFL_WELCOMEVIEW_WELCOMEVIEWSETTINGS_H

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_WELCOMEVIEW_H
#define DAREFL_WELCOMEVIEW_WELCOMEVIEW_H

#include <QWidget>
#include <memory>

class ApplicationModels;
class ProjectHandler;
class RecentProjectWidget;
class OpenProjectWidget;
class RecentProjectSettings;

//! Welcome view. Main widget on first tab of MainWindow.

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    WelcomeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~WelcomeView();

    bool canCloseProject() const;

    void updateNames();

signals:
    void recentProjectsListModified(const QStringList& projects);

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();
    void onClearRecentProjectsList();

private:
    void setup_connections();
    void update_current_project_name();
    void update_recent_project_names();

    ApplicationModels* m_models{nullptr};
    ProjectHandler* m_projectHandler{nullptr};
    RecentProjectWidget* m_recentProjectWidget{nullptr};
    OpenProjectWidget* m_openProjectWidget{nullptr};
};

#endif // DAREFL_WELCOMEVIEW_WELCOMEVIEW_H

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_WELCOMEVIEW2_H
#define DAREFL_WELCOMEVIEW_WELCOMEVIEW2_H

#include <QWidget>
#include <memory>

class ApplicationModels;
class ProjectHandler;
class RecentProjectWidget;
class OpenProjectWidget;
class WelcomeViewSettings;

//! Welcome view. Main widget on first tab of MainWindow.

class WelcomeView2 : public QWidget
{
    Q_OBJECT
public:
    WelcomeView2(ApplicationModels* models, QWidget* parent = nullptr);
    ~WelcomeView2();

    bool canCloseProject() const;

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void setup_connections();
    void update_current_project_name();
    void update_recent_project_names();

    ApplicationModels* m_models{nullptr};
    ProjectHandler* m_projectHandler{nullptr};
    RecentProjectWidget* m_recent_project_widget{nullptr};
    OpenProjectWidget* m_open_project_widget{nullptr};
    std::unique_ptr<WelcomeViewSettings> m_settings;
};

#endif // DAREFL_WELCOMEVIEW_WELCOMEVIEW2_H
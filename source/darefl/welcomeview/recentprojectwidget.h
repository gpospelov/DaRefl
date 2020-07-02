// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_RECENTPROJECTWIDGET_H
#define DAREFL_WELCOMEVIEW_RECENTPROJECTWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>

class QBoxLayout;
class ProjectPaneWidget;

//! Widget with the name of current project and collection of recent projects.
//! Occupies left part of WelcomeView.

class RecentProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecentProjectWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void setCurrentProject(const QString& project_dir, bool is_modified);

    void setRecentProjectsList(const QStringList& projects);

signals:
    void projectSelected(const QString& project_dir);

private:
    QBoxLayout* createCurrentProjectLayout() const;
    QBoxLayout* createRecentProjectLayout();
    QWidget* createRecentProjectScrollArea();

    ProjectPaneWidget* m_currentProjectPane;
    std::vector<ProjectPaneWidget*> m_recentProjectPanes;
};

#endif // DAREFL_WELCOMEVIEW_RECENTPROJECTWIDGET_H

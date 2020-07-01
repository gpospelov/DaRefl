// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/welcomeview/projectpanewidget.h>
#include <darefl/welcomeview/recentprojectwidget.h>
#include <darefl/welcomeview/adjustingscrollarea.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{
int max_recent_project_count = 10;
}

RecentProjectWidget::RecentProjectWidget(QWidget* parent)
    : QWidget(parent), m_currentProjectPane(new ProjectPaneWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 0, 10, 0);
    layout->addLayout(createCurrentProjectLayout());
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addWidget(createRecentProjectScrollArea());
    layout->addStretch(1);
}

QSize RecentProjectWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize RecentProjectWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

//! Set current project title and label on appropriate widget.
void RecentProjectWidget::setCurrentProject(const QString& project_dir, bool is_modified)
{
    m_currentProjectPane->setCurrentProject(project_dir, is_modified);
    m_currentProjectPane->setActive(false);
}

//! Set name of all recent projects to appropriate widgets.
void RecentProjectWidget::setRecentProjectsList(const QStringList& projects)
{
    int widget_index{0};
    for (auto widget : m_recentProjectPanes) {
        if (widget_index < projects.size())
            widget->setCurrentProject(projects.at(widget_index), false);
        else
            widget->clear();

        ++widget_index;
    }
}

QBoxLayout* RecentProjectWidget::createCurrentProjectLayout() const
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Current Project");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);
    result->addWidget(m_currentProjectPane);
    return result;
}

QBoxLayout* RecentProjectWidget::createRecentProjectLayout()
{
    auto result = new QVBoxLayout;
    auto label = new QLabel("Recent Projects");
    label->setFont(StyleUtils::sectionFont());
    result->addWidget(label);

    for (int i = 0; i < max_recent_project_count; ++i) {
        auto widget = new ProjectPaneWidget;
        connect(widget, &ProjectPaneWidget::projectSelected, this,
                &RecentProjectWidget::projectSelected);
        m_recentProjectPanes.push_back(widget);
        result->addWidget(widget);
    }
    return result;
}

QWidget* RecentProjectWidget::createRecentProjectScrollArea()
{
    auto result = new AdjustingScrollArea;

    auto content = new QWidget;
    content->setLayout(createRecentProjectLayout());
    result->setWidget(content);
    return result;
}

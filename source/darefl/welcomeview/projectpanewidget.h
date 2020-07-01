// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_PROJECTPANEWIDGET_H
#define DAREFL_WELCOMEVIEW_PROJECTPANEWIDGET_H

#include <QWidget>

class QLabel;

//! Holds project name and project dir. Part of RecentProjectsWidget.

class ProjectPaneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectPaneWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void setCurrentProject(const QString& project_dir, bool is_modified = false);

    void clear();

    void setActive(bool value);

signals:
    void projectSelected(const QString& project_dir);

protected:
    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* m_currentProjectTitle{nullptr};
    QLabel* m_currentProjectDir{nullptr};
    QColor m_widgetColor;
    bool m_active{false};
    QString m_projectDir;
};

#endif // DAREFL_WELCOMEVIEW_PROJECTPANEWIDGET_H

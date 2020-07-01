// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/welcomeview/openprojectwidget.h>
#include <mvvm/core/version.h>

OpenProjectWidget::OpenProjectWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString::fromStdString(ModelView::ProjectVersion())));
    layout->addLayout(createButtonLayout());
}

QSize OpenProjectWidget::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize OpenProjectWidget::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

QBoxLayout* OpenProjectWidget::createButtonLayout()
{
    auto result = new QHBoxLayout;

    m_newProjectButton = new QPushButton("New");
    m_newProjectButton->setMinimumHeight(StyleUtils::LargeButtonHeight());
    m_newProjectButton->setMinimumWidth(200);
    m_newProjectButton->setFont(StyleUtils::sectionFont());
    connect(m_newProjectButton, &QPushButton::pressed, this,
            &OpenProjectWidget::createNewProjectRequest);

    m_openProjectButton = new QPushButton("Open");
    m_openProjectButton->setMinimumHeight(StyleUtils::LargeButtonHeight());
    m_openProjectButton->setMinimumWidth(200);
    m_openProjectButton->setFont(StyleUtils::sectionFont());
    connect(m_openProjectButton, &QPushButton::pressed, this,
            &OpenProjectWidget::openExistingProjectRequest);

    result->addStretch(1);
    result->addWidget(m_newProjectButton);
    result->addWidget(m_openProjectButton);
    result->addStretch(1);

    return result;
}

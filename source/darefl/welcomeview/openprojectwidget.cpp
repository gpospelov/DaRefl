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
#include <mvvm/widgets/widgetutils.h>

namespace
{
int widget_height()
{
    return ModelView::Utils::SizeOfLetterM().height() * 40;
}
} // namespace


OpenProjectWidget::OpenProjectWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    QPixmap logo(":/icons/F-letter_1000x.png");
    auto label = new QLabel;
    label->setPixmap(logo.scaled(widget_height(), widget_height(), Qt::KeepAspectRatio));

    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height()*1.5);
    layout->addWidget(label);
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addLayout(createButtonLayout());
    layout->addStretch();


//    result->addWidget(label);
//    result->addStretch(1);
//    result->setContentsMargins(5, 5, 5, 5);

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

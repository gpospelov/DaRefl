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
#include <QDebug>

namespace
{
int logo_width()
{
    return ModelView::Utils::SizeOfLetterM().height() * 40;
}

void set_font(QLabel* label)
{
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.25);
    label->setFont(font);
}

const QString str_open = "Open";
const QString str_new = "New";

QString link_text(const QString& text)
{
    return QString("<a href=\"%1\">%2</a>").arg(text, text);
}

} // namespace

OpenProjectWidget::OpenProjectWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    QPixmap logo(":/icons/F-letter_1000x.png");
    auto label = new QLabel;
    label->setPixmap(logo.scaled(logo_width(), logo_width(), Qt::KeepAspectRatio));

    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height() * 1.5);
    layout->addWidget(label, 0, Qt::AlignHCenter);
    layout->addSpacing(ModelView::Utils::SizeOfLetterM().height());
    layout->addLayout(createButtonLayout());
    layout->addLayout(createLabelLayout());
    layout->addStretch();
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

QBoxLayout* OpenProjectWidget::createLabelLayout()
{
    auto result = new QHBoxLayout;

    m_newProjectLabel = new QLabel(link_text(str_new));
    connect(m_newProjectLabel, &QLabel::linkActivated, [this](auto) {createNewProjectRequest();});
    set_font(m_newProjectLabel);

    m_openProjectLabel = new QLabel(link_text(str_open));
    connect(m_openProjectLabel, &QLabel::linkActivated, [this](auto) {openExistingProjectRequest();});
    set_font(m_openProjectLabel);

    result->addStretch(1);
    result->addWidget(m_newProjectLabel);
    result->addSpacing(ModelView::Utils::WidthOfLetterM());
    result->addWidget(m_openProjectLabel);
    result->addStretch(1);

    return result;
}

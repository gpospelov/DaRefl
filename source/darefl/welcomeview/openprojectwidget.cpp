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
#include <darefl/core/version.h>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/welcomeview/openprojectwidget.h>
#include <mvvm/core/version.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{
int logo_width()
{
    return ModelView::Utils::SizeOfLetterM().height() * 40;
}

void set_font(QLabel* label, double scale = 1.25)
{
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * scale);
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
    layout->addLayout(createProjectTitleLayout());
    layout->addLayout(createLinkedLabelLayout());
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

QBoxLayout* OpenProjectWidget::createProjectTitleLayout()
{
    auto result = new QHBoxLayout;
    QString title = QString("DaRefl: reflectometry simulations, v%1").arg(QString::fromStdString(DaRefl::ProjectVersion()));
    auto label = new QLabel(title);
    set_font(label, 1.25);

    result->addWidget(label, 0, Qt::AlignHCenter);
    return result;
}

QBoxLayout* OpenProjectWidget::createLinkedLabelLayout()
{
    auto result = new QHBoxLayout;

    m_newProjectLabel = new QLabel(link_text(str_new));
    m_newProjectLabel->setToolTip("Create new project");
    connect(m_newProjectLabel, &QLabel::linkActivated, [this](auto) { createNewProjectRequest(); });
    set_font(m_newProjectLabel);

    m_openProjectLabel = new QLabel(link_text(str_open));
    m_openProjectLabel->setToolTip("Open existing project");
    connect(m_openProjectLabel, &QLabel::linkActivated,
            [this](auto) { openExistingProjectRequest(); });
    set_font(m_openProjectLabel);

    result->addStretch(1);
    result->addWidget(m_newProjectLabel);
    result->addSpacing(ModelView::Utils::WidthOfLetterM());
    result->addWidget(m_openProjectLabel);
    result->addStretch(1);

    return result;
}

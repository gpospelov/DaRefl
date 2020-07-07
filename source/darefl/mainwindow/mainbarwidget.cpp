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
#include <QStackedWidget>
#include <QVBoxLayout>
#include <darefl/mainwindow/fancytab.h>
#include <darefl/mainwindow/mainbarwidget.h>

namespace
{
const int buttonHeight = 60;
}

MainBarWidget::MainBarWidget(QWidget* parent)
    : QWidget(parent), stacked_widget(new QStackedWidget), button_layout(new QHBoxLayout),
      label_layout(new QHBoxLayout)
{
    button_layout->setContentsMargins(0, 0, 0, 0);

    auto layout = new QVBoxLayout;
    layout->addLayout(button_layout);
    layout->addLayout(label_layout);
    layout->addWidget(stacked_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

MainBarWidget::~MainBarWidget() = default;

void MainBarWidget::addWidget(QWidget* widget, const QString& title)
{
    auto button = new QPushButton(title);
    button->setMinimumHeight(buttonHeight);

    QFont font = button->font();
    font.setPointSize(font.pointSize() * 1.25);
    button->setFont(font);

    int index = stacked_widget->addWidget(widget);
    auto on_button_pressed = [this, index]() { setCurrentIndex(index); };
    connect(button, &QPushButton::pressed, on_button_pressed);

    button_layout->addWidget(button);
    index_to_button[index] = button;

    auto tab = new FancyTab(title);
    index_to_tab[index] = tab;
    label_layout->addWidget(tab);
}

void MainBarWidget::setCurrentIndex(int index)
{
//    auto it = index_to_button.find(index);
//    if (it != index_to_button.end()) {
//        auto button = it->second;
//        button->pressed();
//    }

    for (auto it : index_to_tab)
        it.second->setActive(it.first == index);

    stacked_widget->setCurrentIndex(index);
}

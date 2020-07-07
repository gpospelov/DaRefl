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

MainBarWidget::MainBarWidget(QWidget* parent)
    : QWidget(parent), stacked_widget(new QStackedWidget), label_layout(new QHBoxLayout)
{
    label_layout->setContentsMargins(0, 0, 0, 0);

    auto layout = new QVBoxLayout;
    layout->addLayout(label_layout);
    layout->addWidget(stacked_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

MainBarWidget::~MainBarWidget() = default;

void MainBarWidget::addWidget(QWidget* widget, const QString& title, bool is_enabled)
{
    int index = stacked_widget->addWidget(widget);

    auto tab = new FancyTab(title);
    tab->setEnabled(is_enabled);
    auto on_tab_clicked = [this, index]() { setCurrentIndex(index); };
    connect(tab, &FancyTab::clicked, on_tab_clicked);

    index_to_tab[index] = tab;
    label_layout->addWidget(tab);
}

void MainBarWidget::setCurrentIndex(int index)
{
    for (auto it : index_to_tab)
        it.second->setSelected(it.first == index);

    stacked_widget->setCurrentIndex(index);
}

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <darefl/dataloader2/dataloadertoolbar.h>
#include <darefl/mainwindow/styleutils.h>
#include <mvvm/widgets/widgetutils.h>

DataLoaderToolBar::DataLoaderToolBar(QWidget* parent) : QToolBar(parent)
{
    StyleUtils::SetToolBarStyleTextBesides(this);

    // add files
    auto action = new QAction("Add files", this);
    action->setIcon(QIcon(":/icons/import.svg"));
    action->setToolTip("Adds more files to the list.\n "
                       "All of them will be parsed in the same way.");
    connect(action, &QAction::triggered, [this]() { this->addFilesRequest(); });
    addAction(action);

    // remove files
    action = new QAction("Remove files", this);
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Remove selected files from the list.");
    connect(action, &QAction::triggered, [this]() { this->removeFilesRequest(); });
    addAction(action);

    addSeparator();

    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    auto combo = new QComboBox;
    combo->addItems(QStringList() << "aaa"
                                  << "bbb");
    combo->setMinimumWidth(ModelView::Utils::WidthOfLetterM()*12);

    addWidget(new QLabel("Insert into "));
    addWidget(combo);
}

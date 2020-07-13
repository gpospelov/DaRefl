// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QMessageBox>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/importdataview/importdataeditortoolbal.h>
#include <darefl/mainwindow/styleutils.h>

ImportDataEditorToolBar::ImportDataEditorToolBar(ImportDataEditorActions* editorActions,
                                                 QWidget* parent)
    : QToolBar(parent), m_editorActions(editorActions)
{
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto add_group_action = new QAction("Add a data group", this);
    add_group_action->setToolTip("Add a data group to manage loaded items.");
    add_group_action->setIcon(QIcon(":/icons/plus-box-outline.svg"));

    auto merge_group_action = new QAction("Merge data groups", this);
    merge_group_action->setToolTip("Merge selected data groups into one.");
    merge_group_action->setIcon(QIcon(":/icons/set-merge.svg"));
    merge_group_action->setObjectName("merge_group_action");

    auto load_action = new QAction("Data Loader", this);
    load_action->setToolTip("Opens the data loading dialog ...");
    load_action->setIcon(QIcon(":/icons/import.svg"));

    auto delete_action = new QAction("Delete selected", this);
    delete_action->setToolTip("Remove the currently selected item.");
    delete_action->setIcon(QIcon(":/icons/file-remove.svg"));

    auto reset_action = new QAction("Reset loaded", this);
    reset_action->setToolTip("Reset all the loaded items.");
    reset_action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));

    auto undo_action = new QAction("Undo data action", this);
    undo_action->setToolTip("Undo the action last performed.");
    undo_action->setIcon(QIcon(":/icons/undo.svg"));

    auto redo_action = new QAction("Redo data action", this);
    redo_action->setToolTip("Redo the action just performed.");
    redo_action->setIcon(QIcon(":/icons/redo.svg"));

    auto reset_graph_action = new QAction("Reset Aspect ratio", this);
    reset_graph_action->setToolTip("Reset the graph aspect ratio");
    reset_graph_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));

    setIconSize(StyleUtils::ToolBarIconSize());
    setOrientation(Qt::Horizontal);

    addAction(add_group_action);
    addAction(merge_group_action);
    addAction(load_action);
    addSeparator();
    addAction(delete_action);
    addAction(reset_action);
    addSeparator();
    addAction(undo_action);
    addAction(redo_action);

    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);
    addAction(reset_graph_action);

    connect(add_group_action, &QAction::triggered, [this]() { m_editorActions->addDataGroup(); });
    connect(merge_group_action, &QAction::triggered,
            [this]() { m_editorActions->mergeDataGroups(); });
    connect(load_action, &QAction::triggered, this, &ImportDataEditorToolBar::invokeImportDialog);
    connect(delete_action, &QAction::triggered, [this]() { m_editorActions->deleteItem(); });
    connect(reset_action, &QAction::triggered, this, &ImportDataEditorToolBar::resetAll);
    connect(reset_graph_action, &QAction::triggered, this,
            &ImportDataEditorToolBar::update_viewport);
}

void ImportDataEditorToolBar::resetAll()
{
    QMessageBox* reset_message = new QMessageBox;
    reset_message->setIcon(QMessageBox::Warning);
    reset_message->setText("You are about to clear all the loaded data.");
    reset_message->setInformativeText("Are you sure you want to proceed ?");
    reset_message->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    reset_message->setDefaultButton(QMessageBox::Cancel);
    int ret = reset_message->exec();

    if (ret == QMessageBox::Yes)
        m_editorActions->resetAll();
}

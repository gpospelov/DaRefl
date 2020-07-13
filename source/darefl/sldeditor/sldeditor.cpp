// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/sldeditor.h>

#include <darefl/model/applicationmodels.h>
#include <darefl/sldeditor/graphicsscene.h>
#include <darefl/sldeditor/sldeditoractions.h>
#include <darefl/sldeditor/sldeditortoolbar.h>
#include <darefl/sldeditor/sldviewwidget.h>

#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <mvvm/plotting/graphcanvas.h>

//! The constructor
SLDEditor::SLDEditor(QWidget* parent)
    : QWidget(parent), p_view_widget(new SLDViewWidget(this)),
      p_editor_actions(new SLDEditorActions(this)),
      p_editor_tollbar(new SLDEditorToolBar(p_editor_actions))
{
    setWindowTitle("SLD editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(p_editor_tollbar);
    layout->addWidget(p_view_widget);
    setLayout(layout);

    connect(p_editor_tollbar, &SLDEditorToolBar::resetViewport, [this]() {
        GraphicsScene* scene_item = dynamic_cast<GraphicsScene*>(p_view_widget->scene());
        if (!scene_item)
            return;
        scene_item->graphCanvas()->update_viewport();
    });
}

//! The destructor
SLDEditor::~SLDEditor() = default;

void SLDEditor::setModels(ApplicationModels* models)
{
    p_view_widget->setModels(models);
    p_editor_actions->setModel(models->sldViewModel());
}

QSize SLDEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

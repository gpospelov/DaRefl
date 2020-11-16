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
    : QWidget(parent)
    , m_editorActions(new SLDEditorActions(this))
    , m_viewWidget(new SLDViewWidget(this))
    , m_toolBar(new SLDEditorToolBar(m_editorActions))
{
    setWindowTitle("SLD editor");
    auto layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_viewWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    connect(dynamic_cast<SLDEditorToolBar*>(m_toolBar), &SLDEditorToolBar::resetViewport, [this]() {
        GraphicsScene* scene_item = dynamic_cast<GraphicsScene*>(m_viewWidget->scene());
        if (!scene_item)
            return;
        scene_item->graphCanvas()->update_viewport();
    });
}

//! The destructor
SLDEditor::~SLDEditor() = default;

void SLDEditor::setModels(ApplicationModels* models)
{
    m_viewWidget->setModels(models);
    m_editorActions->setModel(models->sldViewModel());
}

QSize SLDEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

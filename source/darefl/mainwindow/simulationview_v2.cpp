// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/layereditor/layereditor.h>
#include <darefl/mainwindow/collapsiblelistwidget.h>
#include <darefl/mainwindow/simulationview_v2.h>
#include <darefl/materialeditor/materialeditor.h>
#include <darefl/quicksimeditor/instrumentpropertyeditor.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/sldeditor/sldeditor.h>

SimulationViewV2::SimulationViewV2(ApplicationModels* models, QWidget* parent)
    : QMainWindow(parent), m_editorList(new CollapsibleListWidget), m_simEditor(new QuickSimEditor),
      m_models(models)
{
    auto splitter = new QSplitter;

    auto material_editor = new MaterialEditor(this);
    auto layer_editor = new LayerEditor(this);
    auto sld_editor = new SLDEditor(this);
    auto instrument_editor = new InstrumentPropertyEditor(this);

    m_editorList->addWidget(material_editor, "Material editor");
    m_editorList->addWidget(layer_editor, "Layer editor");
    m_editorList->addWidget(instrument_editor, "Instrument editor", true);
    m_editorList->addWidget(sld_editor, "SLD editor", true);

    splitter->addWidget(m_editorList);
    splitter->addWidget(m_simEditor);

    setCentralWidget(splitter);

    material_editor->setModels(models);
    layer_editor->setModels(models);
    sld_editor->setModels(models);
    m_simEditor->setModels(models);
    instrument_editor->setModels(models);
}

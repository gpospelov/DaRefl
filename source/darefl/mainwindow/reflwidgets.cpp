// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/mainwindow/reflwidgets.h>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/sldeditor/sldeditor.h>

//! ---------------------------------------------------------------------------

LayerCanvas::LayerCanvas(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Layer Canvas"));
}

//! ---------------------------------------------------------------------------

InstrumentEditor::InstrumentEditor(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(QString("Instrument Editor"));
}

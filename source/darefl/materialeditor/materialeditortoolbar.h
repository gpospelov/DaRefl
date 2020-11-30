// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
#define DAREFL_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H

#include <QToolBar>
#include <darefl/darefl_export.h>

class MaterialEditorActions;

//! Material editor toolbar.

class DAREFLCORE_EXPORT MaterialEditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent = nullptr);
    ~MaterialEditorToolBar() = default;
};

#endif // DAREFL_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_STYLEUTILS_H
#define DAREFL_MAINWINDOW_STYLEUTILS_H

class QSize;
class QFont;

//! Namespace for central access to all theme styling.

namespace StyleUtils
{

//! Size of tolbar icons for LayerEditor, MaterialEditor and similar.
QSize ToolBarIconSize();

//! Hint on size of docks on main reflectometry window.
QSize DockSizeHint();

//! Hint on minimum size of docks on main reflectometry window.
QSize DockMinimumSizeHint();

}; // namespace StyleUtils

#endif // DAREFL_MAINWINDOW_STYLEUTILS_H

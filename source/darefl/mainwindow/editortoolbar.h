// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_EDITORTOOLBAR_H
#define DAREFL_MAINWINDOW_EDITORTOOLBAR_H

#include <QToolBar>
#include <QSize>
#include <string>
#include <map>

class QWidget;
class QLabel;
class QAction;

enum EditorToolBarMode {
    None    = 0x00,
    Toggle  = 0x02,
    Window  = 0x04,
    Close   = 0x06,
    Title   = 0x08
};

inline EditorToolBarMode operator|(EditorToolBarMode a, EditorToolBarMode b)
{
    return static_cast<EditorToolBarMode>(static_cast<int>(a) | static_cast<int>(b));
}

//! Handles appearance of docked widgets in the QMainWindow context.

class EditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    EditorToolBar(std::string name, QWidget* parent = nullptr);
    ~EditorToolBar();

    QAction* addWidget(QWidget* widget);
    QAction* addSeparator();
    QAction* addAction(QAction* action);
    QAction* tailAction(std::string name);

    void setMode(EditorToolBarMode mode);
    void setToggleWidget(QWidget* widget);
    bool toggleState() const;

private:
    void setHeader(std::string name);
    void setBody();
    void setTail();
    void refreshMode();
    void toggle();

private:
    std::map<std::string, QAction*> m_header_actions;
    std::vector<QAction*> m_body_actions;
    std::map<std::string, QAction*> m_tail_actions;

    QAction* p_empty_action{nullptr};
    EditorToolBarMode m_mode;

    QWidget* p_toggle_widget{nullptr};
    bool m_toggle_state;
    QSize m_toggle_size;

};

#endif //DAREFL_MAINWINDOW_EDITORTOOLBAR_H
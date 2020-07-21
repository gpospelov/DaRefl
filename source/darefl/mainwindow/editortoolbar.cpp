// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QToolButton>
#include <QLabel>
#include <QString>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <darefl/mainwindow/editortoolbar.h>
#include <darefl/mainwindow/editorwidget.h>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/resources/resources.h>

EditorToolBar::EditorToolBar(std::string name, QWidget* parent) : QToolBar(parent), m_mode(EditorToolBarMode::None), m_toggle_state(false) 
{
    InitIconResources();
    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setHeader(name);
    setBody();
    setTail();
}

EditorToolBar::~EditorToolBar() = default;

//! Changed the addWidget method to an insertion
QAction* EditorToolBar::addWidget(QWidget* widget)
{
    auto action = insertWidget(p_empty_action, widget);
    m_body_actions.push_back(action);
    return action;
}

//! Changed the addSeparator method to an insertion
QAction* EditorToolBar::addSeparator()
{
    auto action = insertSeparator(p_empty_action);
    m_body_actions.push_back(action);
    return action;
}

//! Changed the addAction method to an insertion
QAction* EditorToolBar::addAction(QAction* action)
{
    insertAction(p_empty_action, action);
    m_body_actions.push_back(action);
    return action;
}

//! Provide the action associated to the action name in the tail
QAction* EditorToolBar::tailAction(std::string name)
{
    return m_tail_actions[name];
}

//! Set the mode and reprocess
void EditorToolBar::setMode(EditorToolBarMode mode)
{
    m_mode = mode;
    refreshMode();
}

//! Set the widget which will be minimized
void EditorToolBar::setToggleWidget(QWidget* widget)
{
    p_toggle_widget = widget;
}

bool EditorToolBar::toggleState() const
{
    return m_toggle_state;
}

//! Set the header action and widgets
void EditorToolBar::setHeader(std::string name)
{
    auto header_label = QToolBar::addWidget(
        new QLabel(QString::fromStdString(name), this));
    auto header_separator = QToolBar::addSeparator();

    m_header_actions.insert(std::pair<std::string, QAction*>("Title", header_label));
    m_header_actions.insert(std::pair<std::string, QAction*>("Separator", header_separator));
}

//! Set the body action and widgets
void EditorToolBar::setBody()
{
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    p_empty_action = QToolBar::addWidget(empty);
}

//! Set the tail action and widgets
void EditorToolBar::setTail()
{
    QAction* action;

    action = QToolBar::addSeparator();
    m_tail_actions.insert(std::pair<std::string, QAction*>("Separator", action));

    action = new QAction("Toggle", this);
    action->setIcon(QIcon(":/icons/arrow-up-drop-circle-outline.svg"));
    action->setToolTip("Toggle the content");
    QToolBar::addAction(action);
    m_tail_actions.insert(std::pair<std::string, QAction*>("Toggle", action));
    connect(
        action, &QAction::triggered,
        this, &EditorToolBar::toggle
    );

    action = new QAction("Window", this);
    action->setIcon(QIcon(":/icons/arrow-expand-all.svg"));
    action->setToolTip("Make a window of the current view");
    QToolBar::addAction(action);
    m_tail_actions.insert(std::pair<std::string, QAction*>("Window", action));

    action = new QAction("Close", this);
    action->setIcon(QIcon(":/icons/close-circle-outline.svg"));
    action->setToolTip("Close the current window");
    QToolBar::addAction(action);
    m_tail_actions.insert(std::pair<std::string, QAction*>("Close", action));

    refreshMode();
}

//! Set the tail action and widgets
void EditorToolBar::refreshMode()
{
    for (std::map<std::string, QAction*>::iterator it = m_tail_actions.begin(); it != m_tail_actions.end(); ++it){
        it->second->setVisible(false);
    }

    if (m_mode & EditorToolBarMode::None)
        return;
    if (m_mode & EditorToolBarMode::Toggle)
        m_tail_actions["Toggle"]->setVisible(true);
    if (m_mode & EditorToolBarMode::Window)
        m_tail_actions["Window"]->setVisible(true);
    if (m_mode & EditorToolBarMode::Close)
        m_tail_actions["Close"]->setVisible(true);
    if (m_mode > EditorToolBarMode::None)
        m_tail_actions["Separator"]->setVisible(true);

    for (std::map<std::string, QAction*>::iterator it = m_header_actions.begin(); it != m_header_actions.end(); ++it){
        it->second->setVisible(m_mode & EditorToolBarMode::Title);
    }
}

//! Set the tail action and widgets
void EditorToolBar::toggle()
{
    m_toggle_state = !m_toggle_state;
    m_tail_actions["Toggle"]->setIcon( (m_toggle_state)?(QIcon(":/icons/arrow-down-drop-circle-outline.svg")):QIcon((":/icons/arrow-up-drop-circle-outline.svg")));

    for (auto action: m_body_actions){
        action->setVisible(!m_toggle_state);
    }

    if (p_toggle_widget){
        if (m_toggle_state)
            m_toggle_size = p_toggle_widget->size();
            
        emit dynamic_cast<EditorWidget*>(p_toggle_widget->parent())->resized((m_toggle_state)?(-m_toggle_size.height()):(m_toggle_size.height()));
        p_toggle_widget->setVisible(!m_toggle_state);
    }
}
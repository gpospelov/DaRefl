// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_USERINTERACTOR_H
#define DAREFL_WELCOMEVIEW_USERINTERACTOR_H

#include <string>

namespace ModelView
{
enum class SaveChangesAnswer;
}

class QWidget;
class WelcomeViewSettings;

//! Provide save/discard/cancel and similar dialogs on user request.
//! Intended to work in pair with ProjectManagerDecorator.

class UserInteractor
{
public:
    UserInteractor(WelcomeViewSettings* settings, QWidget* parent);

    std::string onSelectDirRequest();

    std::string onCreateDirRequest();

    ModelView::SaveChangesAnswer onSaveChangesRequest();

private:
    std::string selectDir() const;

    WelcomeViewSettings* m_settings{nullptr};
    QWidget* m_parent{nullptr};
};

#endif // DAREFL_WELCOMEVIEW_USERINTERACTOR_H

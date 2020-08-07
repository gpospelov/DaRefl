// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_CUSTOMEDITORFACTORY_H
#define DAREFL_LAYEREDITOR_CUSTOMEDITORFACTORY_H

#include <mvvm/editors/defaulteditorfactory.h>

namespace ModelView
{
class CustomEditor;
}

class ApplicationModels;

//! Editor factory with custom editors.
//! Will create custom material selector for all cells containing ExternalProperty.

class CustomEditorFactory : public ModelView::DefaultEditorFactory
{
public:
    CustomEditorFactory(ApplicationModels* models);
    ~CustomEditorFactory();

    std::unique_ptr<ModelView::CustomEditor> createEditor(const QModelIndex& index) const;

private:
    ApplicationModels* m_models;
};

#endif // DAREFL_LAYEREDITOR_CUSTOMEDITORFACTORY_H

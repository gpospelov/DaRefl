// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_CUSTOMBEAMPROPERTYEDITORFACTORY_H
#define DAREFL_QUICKSIMEDITOR_CUSTOMBEAMPROPERTYEDITORFACTORY_H

#include <mvvm/editors/defaulteditorfactory.h>

class ApplicationModels;

//! Custom editor factory for LayerTreeView. Substitutes default ExternalProperty editor
//! with custom one, which will offer the choice between all defined materials.

class CustomBeamPropertyEditorFactory : public ModelView::DefaultEditorFactory
{
public:
    CustomBeamPropertyEditorFactory(ApplicationModels* models);
    ~CustomBeamPropertyEditorFactory();

    std::unique_ptr<ModelView::CustomEditor> createEditor(const QModelIndex& index) const;

private:
    ApplicationModels* m_models;
};

#endif // DAREFL_QUICKSIMEDITOR_CUSTOMBEAMPROPERTYEDITORFACTORY_H

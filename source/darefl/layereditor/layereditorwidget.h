// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H
#define DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class ViewModelDelegate;
} // namespace ModelView

class ApplicationModels;
class LayerTreeView;
class LayerSelectionModel;
class LayerViewModel;

//! Widget to hold layer tree (LayerTreeView) and all corresponding models and delegates.
//! Belongs to LayerEditor.

class LayerEditorWidget : public QWidget
{
    Q_OBJECT
public:
    LayerEditorWidget(QWidget* parent = nullptr);
    ~LayerEditorWidget();

    void setModels(ApplicationModels* models);

    LayerSelectionModel* selectionModel() const;

private:
    std::unique_ptr<LayerViewModel> view_model;
    LayerSelectionModel* selection_model{nullptr};
    LayerTreeView* layer_view{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QGraphicsView>
#include <memory>

class ApplicationModels;
class SLDElementController;

//! The segment QGraphicsViewItem on the Graphicsscene
class SLDViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    SLDViewWidget(QWidget* parent = nullptr);
    ~SLDViewWidget();

    void setModels(ApplicationModels* models);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    std::unique_ptr<SLDElementController> m_sld_controller;
};

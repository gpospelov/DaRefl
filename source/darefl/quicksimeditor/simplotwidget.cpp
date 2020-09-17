// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/quicksimeditor/simplotwidget.h>
#include <mvvm/plotting/graphcanvas.h>
#include <QSplitter>
#include <QVBoxLayout>
#include <QList>

SimPlotWidget::SimPlotWidget(QWidget* parent)
    : QWidget(parent), m_specularCanvas(new ModelView::GraphCanvas),
      m_diffCanvas(new ModelView::GraphCanvas)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 5, 5, 5);

    auto splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(m_specularCanvas);
    splitter->addWidget(m_diffCanvas);

    splitter->setSizes(QList<int>() << 300 << 100);

    layout->addWidget(splitter);
}

void SimPlotWidget::setModels(ApplicationModels* models)
{
    m_models = models;
}

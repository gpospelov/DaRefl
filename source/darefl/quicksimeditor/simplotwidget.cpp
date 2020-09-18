// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QList>
#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <darefl/quicksimeditor/simplotwidget.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/standarditems/axisitems.h>

// ----------------------------------------------------------------------------

//! Simple model to hold graphs representing relative difference of Data1DItem's

class DiffGraphModel : public ModelView::SessionModel
{
public:
    DiffGraphModel() : ModelView::SessionModel("DiffGraphModel")
    {
        viewport = insertItem<ModelView::GraphViewportItem>();
        diff_data = insertItem<ModelView::Data1DItem>();
        diff_graph = insertItem<ModelView::GraphItem>();

        diff_graph->setDataItem(diff_data);
    }

    void clearGraphs()
    {
//        for (auto graph : viewport->graphItems())
//            ModelView::Utils::DeleteItemFromModel(graph);
    }

    void updateDiffGraph(const ModelView::Data1DItem* g1, const ModelView::Data1DItem* g2)
    {
        assert(g1->binCenters().size() == g2->binCenters().size());

        std::vector<double> centers = g1->binCenters();

        std::vector<double> values1 = g1->binValues();
        std::vector<double> values2 = g2->binValues();
        std::vector<double> diff_values;

        for (size_t i = 0; i< values1.size(); ++i) {
            double v1 = values1[i];
            double v2 = values2[i];
            diff_values.push_back(2*(v1-v2)/(v1+v2));
        }

        diff_data->setAxis(ModelView::PointwiseAxisItem::create(g1->binCenters()));
        diff_data->setContent(diff_values);
    }

    ModelView::GraphViewportItem* viewport{nullptr};
    ModelView::Data1DItem* diff_data{nullptr};
    ModelView::GraphItem* diff_graph{nullptr};
};

// ----------------------------------------------------------------------------

SimPlotWidget::SimPlotWidget(QWidget* parent)
    : QWidget(parent), m_specularCanvas(new ModelView::GraphCanvas),
      m_diffCanvas(new ModelView::GraphCanvas), m_diffModel(std::make_unique<DiffGraphModel>())
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 5, 5, 5);

    auto splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(m_specularCanvas);
    splitter->addWidget(m_diffCanvas);

    //    splitter->setStyleSheet("background-color:white;");
    splitter->setSizes(QList<int>() << 300 << 100);

    layout->addWidget(splitter);

    initDiffModel();
}

SimPlotWidget::~SimPlotWidget() = default;

void SimPlotWidget::setModels(ApplicationModels* models)
{
    m_models = models;

    m_specularCanvas->setItem(m_models->jobModel()->specular_viewport());
    m_diffCanvas->setItem(m_diffModel->viewport);
}

void SimPlotWidget::update_viewport()
{
    m_specularCanvas->update_viewport();
}

//! Init the content of diff model

void SimPlotWidget::initDiffModel() {}

// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDialogButtonBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/dataloader2/dataloaderdialog_v2.h>
#include <darefl/dataloader2/loaderpreviewpanel.h>
#include <darefl/dataloader2/loaderselectorpanel.h>

DataLoaderDialogV2::DataLoaderDialogV2(QWidget* parent)
    : QDialog(parent), m_selectorPanel(new LoaderSelectorPanel),
      m_previewPanel(new LoaderPreviewPanel), m_splitter(new QSplitter)
{
    m_splitter->addWidget(m_selectorPanel);
    m_splitter->addWidget(m_previewPanel);

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    connect(button_box, &QDialogButtonBox::accepted, this, &DataLoaderDialogV2::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &DataLoaderDialogV2::reject);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_splitter);
    layout->addWidget(button_box);
}

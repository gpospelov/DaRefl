// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTLINEFILTERWIDGET_H
#define DAREFL_DATALOADER_IMPORTLINEFILTERWIDGET_H

#include <mvvm/model/customvariants.h>

#include <QGroupBox>
#include <QProxyStyle>
#include <QStyleOption>
#include <QWidget>
#include <memory>

#include <darefl/dataloader/importlogic.h>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
class QLineEdit;
class QTabWidget;
class QGridLayout;
QT_END_NAMESPACE

// Forward declare color editor
namespace ModelView
{
class ColorEditor;
}

// Forward declare switch
namespace SwitchSpace
{
class Switch;
}

namespace DataImportGui
{

// -------------------------------------------------
//! This is the tab widget side style
class CustomTabStyle : public QProxyStyle
{
public:
    CustomTabStyle() : QProxyStyle("fusion"){};
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size,
                           const QWidget* widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter,
                     const QWidget* widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};

// -------------------------------------------------
//! This is the main dialog for the data loader
class LineFilterWidget : public QWidget
{
    Q_OBJECT

public:
    LineFilterWidget(DataImportLogic::LineFilter* line_filter = nullptr, QWidget* parent = nullptr);
    ~LineFilterWidget() = default;
    DataImportLogic::LineFilter* lineFilter() const;
    void grabFromLineFilter();

signals:
    void parameterChanged();
    void nameChanged(std::string name, LineFilterWidget*);
    void typeChanged(std::string type, LineFilterWidget*);

private:
    void setSubwidgetStyles();
    void setSubwidgetNames();
    void setSubwidgetToolTips();
    void setEnabled();
    void typeVariation();
    void startRangeChanged();
    void endRangeChanged();
    void connectSubcomponents();

    void createComponents();
    void initComponents();
    void setLayout();
    void setTypeLayout();
    void setRangeLayout();
    void connectAll();

    void dataChanged();

private:
    DataImportLogic::LineFilter* p_line_filter;
    std::unique_ptr<QProxyStyle> p_style;

    // --------------------------------
    // --DEVELOP-- (Can be changed again to revert all functionalities)
    // To revert: remove non commented code and uncomment commented code

    // QTabWidget* p_tab_widget;
    QWidget* p_tab_widget;

    // --------------------------------

    SwitchSpace::Switch* p_active_checkbox;
    ModelView::ColorEditor* p_color_editor;
    QSpinBox* p_line_start;
    QSpinBox* p_line_end;

    QComboBox* p_type_select;
    QComboBox* p_range_start;
    QComboBox* p_range_end;
    QComboBox* p_separators;

    QLineEdit* p_filter_name;
    QLineEdit* p_ignore_strings;
    QLineEdit* p_ignore_lines;

    QGridLayout* p_type_layout;
    QGridLayout* p_range_layout;
};

} // End of namespace DataImportGui

#endif // DAREFL_DATALOADER_IMPORTLINEFILTERWIDGET_H

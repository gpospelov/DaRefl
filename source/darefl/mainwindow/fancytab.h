// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_FANCYTAB_H
#define DAREFL_MAINWINDOW_FANCYTAB_H

#include <QWidget>

class QLabel;
class QString;

class FancyTab : public QWidget
{
    Q_OBJECT

public:
    FancyTab(const QString& title, QWidget* parent = nullptr);

    void setSelected(bool value);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel* m_label{nullptr};
    bool m_is_selected{false};
};

#endif // DAREFL_MAINWINDOW_FANCYTAB_H

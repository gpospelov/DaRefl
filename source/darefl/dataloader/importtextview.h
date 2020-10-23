// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTTEXTVIEW_H
#define DAREFL_DATALOADER_IMPORTTEXTVIEW_H

//! Based on Qt example "codeeditor"
//! Copyright (C) 2016 The Qt Company Ltd.

#include <QPlainTextEdit>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

//! Text view to show imported data.

class ImportTextView : public QPlainTextEdit
{
    Q_OBJECT

public:
    ImportTextView(QWidget* parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);

private:
    QWidget* lineNumberArea;
};

//! Area with line numbers.

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ImportTextView* editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const override { return QSize(codeEditor->lineNumberAreaWidth(), 0); }

protected:
    void paintEvent(QPaintEvent* event) override { codeEditor->lineNumberAreaPaintEvent(event); }

private:
    ImportTextView* codeEditor;
};

#endif // DAREFL_DATALOADER_IMPORTTEXTVIEW_H

#ifndef Q_SHELL_WINDOW
#define Q_SHELL_WINDOW

#include <QLineEdit>
#include <QTextEdit>
#include <QtGui>
#include <QLabel>
#include <QFrame>
#include "../../TerminalWrapper/TerminalWrapper.h"
#include "../../Common/ThreadPool/ThreadPool.h"

#define INPUT_LINE_EDIT_FIXED_HEIGHT    30
#define INPUT_TIPS_FIXED_WIDTH          30
#define SHELL_FRAME_LINE_WIDTH          2

class QShellWindow : public QFrame
{
public:
    QShellWindow(QWidget* parent = nullptr);
    ~QShellWindow();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    QWidget*            m_pParent;
    QTextEdit*          m_pLogWidget;
    QLineEdit*          m_pInputEdit;
    QLabel*             m_pInputTips;
    TerminalWrapper     m_terminal;
};

#endif  //  Q_SHELL_WINDOW
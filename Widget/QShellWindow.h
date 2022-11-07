#ifndef Q_SHELL_WINDOW
#define Q_SHELL_WINDOW

#include <QLineEdit>
#include <QTextEdit>
#include <QtGui>
#include <QLabel>
#include <QFrame>
#include "qobjectdefs.h"
#include "../../TerminalWrapper/TerminalWrapper.h"
#include "../../Common/ThreadPool/ThreadPool.h"

#define INPUT_LINE_EDIT_FIXED_HEIGHT    30
#define INPUT_TIPS_FIXED_WIDTH          30
#define SHELL_FRAME_LINE_WIDTH          2
#define LOG_FONT_SIZE                   12.5
#define LOG_FONT_WEIGHT                 100
#define GET_TERMINAL_LOG_LOOP_INTERNAL  30000

class QShellWindow : public QFrame
{
    Q_OBJECT

public:
    QShellWindow(const QString& rTempPath, QWidget* parent = nullptr);
    ~QShellWindow();
    static void GetTerminalLog(QShellWindow* pShell);
protected:
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);
private:
    QWidget*            m_pParent;
    QTextEdit*          m_pLogWidget;
    QLineEdit*          m_pInputEdit;
    QLabel*             m_pInputTips;
    QString             m_tempPath;
    TerminalWrapper     m_terminal;
    TerminalLogStream   m_logStream;
    ThreadPool*         m_threadPool;
    bool                m_isClose;

signals:
    void PrintTerminalLogSignal(QString log);
private slots:
    void PrintTerminalLog(QString log);
};

#endif  //  Q_SHELL_WINDOW
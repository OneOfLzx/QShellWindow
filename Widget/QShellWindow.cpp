#include "QShellWindow.h"

QShellWindow::QShellWindow(const QString& rTempPath, QWidget* parent)
    : QFrame(parent)
    , m_pParent(parent)
    , m_pLogWidget(new QTextEdit(this))
    , m_pInputEdit(new QLineEdit(this))
    , m_pInputTips(new QLabel(this))
    , m_threadPool(nullptr)
    , m_isClose(false)
{
    setFrameShape(Box);
    setFrameShadow(Plain);
    setLineWidth(2);

    m_pLogWidget->setReadOnly(true);
    m_pLogWidget->setFrameShape(Box);
    m_pLogWidget->setFrameShadow(Plain);
    m_pLogWidget->setLineWidth(1);
    m_pLogWidget->setFontPointSize(LOG_FONT_SIZE);
    m_pLogWidget->setFontWeight(LOG_FONT_WEIGHT);
    m_pLogWidget->show();

    m_pInputEdit->setFrame(false);
    m_pInputEdit->show();

    m_pInputTips->setStyleSheet("QLabel{background:rgb(255, 255, 255);font-weight:bold;}");
    m_pInputTips->setText(" >_");
    m_pInputTips->show();

    m_tempPath = rTempPath;
    m_terminal.Open(rTempPath.toStdString(), m_logStream);

    connect(this, SIGNAL(PrintTerminalLogSignal(QString)), SLOT(PrintTerminalLog(QString)));

    m_threadPool = new ThreadPool(1);
    m_threadPool->enqueue(GetTerminalLog, this);
}

QShellWindow::~QShellWindow()
{
    m_isClose = true;
    if (nullptr != m_threadPool)
    {
        delete m_threadPool;
        m_threadPool = nullptr;
    }
    if (nullptr != m_pLogWidget)
    {
        delete m_pLogWidget;
        m_pLogWidget = nullptr;
    }
    if (nullptr != m_pInputEdit)
    {
        delete m_pInputEdit;
        m_pInputEdit = nullptr;
    }
    if (nullptr != m_pInputTips)
    {
        delete m_pInputTips;
        m_pInputTips = nullptr;
    }
    m_terminal.Close();
    m_logStream.Close();
}

void QShellWindow::resizeEvent(QResizeEvent *event)
{
    const QSize size    = event->size();
    int         width   = int(size.width()) - 2 * SHELL_FRAME_LINE_WIDTH;
    int         height  = int(size.height()) - 2 * SHELL_FRAME_LINE_WIDTH;
    if (height < INPUT_LINE_EDIT_FIXED_HEIGHT ||
        width < INPUT_TIPS_FIXED_WIDTH)
    {
        m_pLogWidget->setGeometry(0, 0, 0, 0);
        m_pInputEdit->setGeometry(0, 0, 0, 0);
        m_pInputTips->setGeometry(0, 0, 0, 0);
    }
    else
    {
        m_pLogWidget->setGeometry(SHELL_FRAME_LINE_WIDTH, SHELL_FRAME_LINE_WIDTH,
                                width, height - INPUT_LINE_EDIT_FIXED_HEIGHT);
        m_pInputEdit->setGeometry(INPUT_TIPS_FIXED_WIDTH + SHELL_FRAME_LINE_WIDTH, height - INPUT_LINE_EDIT_FIXED_HEIGHT + SHELL_FRAME_LINE_WIDTH,
                                width - INPUT_TIPS_FIXED_WIDTH, INPUT_LINE_EDIT_FIXED_HEIGHT);
        m_pInputTips->setGeometry(SHELL_FRAME_LINE_WIDTH, height - INPUT_LINE_EDIT_FIXED_HEIGHT + SHELL_FRAME_LINE_WIDTH,
                                INPUT_TIPS_FIXED_WIDTH, INPUT_LINE_EDIT_FIXED_HEIGHT);
    }
}

bool QShellWindow::event(QEvent *event)
{
    bool ret = true;

    // Enter key release event
    if (QEvent::KeyRelease == event->type() &&
        (Qt::Key_Return == ((QKeyEvent*)event)->key() || Qt::Key_Enter == ((QKeyEvent*)event)->key()))
    {
        QString cmd = m_pInputEdit->text();
        m_terminal.ExecuteCommand(cmd.toStdString());
        m_pInputEdit->clear();
        return ret;
    }
    // Combination key: Ctrl S, press event
    else if (QEvent::KeyPress == event->type() &&
            (0 != (((QKeyEvent*)event)->modifiers() & Qt::ControlModifier) && Qt::Key_S == ((QKeyEvent*)event)->key()))
    {
        m_terminal.StopCurrentCommand();
        return ret;
    }
    else
    {
        return QWidget::event(event);
    }
}

void QShellWindow::GetTerminalLog(QShellWindow* pShell)
{
    char buf[2048];
    while (!pShell->m_isClose)
    {
        memset(buf, 0, sizeof(buf));
        pShell->m_logStream.Read(buf, sizeof(buf));
        if ('\0' != buf[0])
        {
            QString log(buf);
            emit pShell->PrintTerminalLogSignal(log);
        }
        usleep(GET_TERMINAL_LOG_LOOP_INTERNAL);
    }
}

void QShellWindow::PrintTerminalLog(QString log)
{
    if (!m_isClose)
    {
        m_pLogWidget->insertPlainText(log);
        m_pLogWidget->moveCursor(QTextCursor::End);
    }
}
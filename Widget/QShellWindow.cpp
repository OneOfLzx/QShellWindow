#include "QShellWindow.h"

QShellWindow::QShellWindow(QWidget* parent)
    : QFrame(parent)
    , m_pParent(parent)
    , m_pLogWidget(new QTextEdit(this))
    , m_pInputEdit(new QLineEdit(this))
    , m_pInputTips(new QLabel(this))
{
    setFrameShape(Box);
    setFrameShadow(Plain);
    setLineWidth(2);

    m_pLogWidget->setReadOnly(true);
    m_pLogWidget->setFrameShape(Box);
    m_pLogWidget->setFrameShadow(Plain);
    m_pLogWidget->setLineWidth(1);
    m_pLogWidget->show();

    m_pInputEdit->setFrame(false);
    m_pInputEdit->show();

    m_pInputTips->setStyleSheet("QLabel{background:rgb(255, 255, 255);font-weight:bold;}");
    m_pInputTips->setText(" >_");
    m_pInputTips->show();
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

QShellWindow::~QShellWindow()
{
    delete m_pLogWidget;
}
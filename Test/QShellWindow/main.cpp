#include <stdio.h>

#include <QApplication>
#include <QMainWindow>
#include "../../Widget/QShellWindow.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        const std::string   tempDir = Utils::GetAbsolutePath("~/TerminalWrapperTest");
        Utils::DeleteDir(tempDir);

        m_pShellWindow = new QShellWindow(QString::fromLocal8Bit(tempDir.c_str()), this);
        m_pShellWindow->show();
    };
    ~MainWindow() { delete m_pShellWindow; };
protected:
    void resizeEvent(QResizeEvent *event)
    {
        const QSize size = event->size();
        int x = 10;
        int y = 10;
        int w = int(size.width()) - 2 * x;
        int h = int(size.height()) - 2 * y;
        if (w < 0 || h < 0)
        {
            w = 0; h = 0;
        }
        m_pShellWindow->setGeometry(x, y, w, h);
    }
private:
    QShellWindow*   m_pShellWindow;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setGeometry(100, 100, 1000, 480);
    w.show();

    return a.exec();
}
#include <QApplication>
#include <QMainWindow>

class StartMenu;

class App
{
public:
    App(int argc, char *arbv[]);

    int run();

private:
    QApplication qApplication_;
    StartMenu *startMenu_;
};
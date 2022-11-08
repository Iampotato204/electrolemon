#include "debugtools.h"
#include "lemonade.h"
#include "mainwindow.h"

#include <string>
#include <iostream>
#include <sstream>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

using namespace std;

string get_cwd(QApplication *qapp){return qapp->applicationDirPath().toStdString();}     //std::filesystem::path cwd = std::filesystem::current_path();
QString str2qstr(string s){return QString::fromStdString(s);}

int main(int argc, char *argv[])
{
    //creating app object
    QApplication electrolemon(argc, argv);

    //translating to system language
    DebugTools Debugger;

    QTranslator translator;

    const QStringList uiLanguages = QLocale::system().uiLanguages();
    const QString &locale = uiLanguages.at(0);
        Debugger.strMsg("locale: "+locale.toStdString());
        const QString baseName = "electrolemon_" + QLocale(locale).name();
        Debugger.strMsg("baseName: "+baseName.toStdString());
        Debugger.strMsg("App path: "+get_cwd(&electrolemon));
        exec_dir = get_cwd(&electrolemon);
        Debugger.boolMsg(translator.load(QLocale(locale), baseName, ".", str2qstr(exec_dir),".qm")); //do NOT comment out; translator.load(args[]) call is required!
        electrolemon.installTranslator(&translator);
    MainWindow w;

    w.show();
    return electrolemon.exec();
}

///*! Render data at OpenGL window or widget */
//void render() {
//   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

//   // Draw a Red 1x1 Square centered at origin
//   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
//      glColor3f(1.0f, 0.0f, 0.0f); // Red
//      glVertex2f(-0.5f, -0.5f);    // x, y
//      glVertex2f( 0.5f, -0.5f);
//      glVertex2f( 0.5f,  0.5f);
//      glVertex2f(-0.5f,  0.5f);
//   glEnd();

//   glFlush();  // Render now
//}

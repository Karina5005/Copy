#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QtCore/QTextStream>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QColorDialog>
#include <QDebug>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
    /** Добавление иконок */
    QPixmap newpix("new.png");
    QPixmap savepix("open.png");
    QPixmap quitpix("quit.png");
    QPixmap helppix("help.png");

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction(newpix, "&New", this);
    QAction *open = new QAction(newpix, "&Open", this);
    QAction *save = new QAction(savepix, "&Save", this);
    QAction *quit = new QAction(quitpix, "&Quit", this);
    QAction *about = new QAction("&About", this);
    QAction *color = new QAction("&Color", this);
    QAction *font = new QAction("&Font", this);

    /** Создаём объект класса QMenu (меню) */
    QMenu *file = menuBar()->addMenu("&File");
    QMenu *edit = menuBar()->addMenu("&Edit");
    QMenu *view = menuBar()->addMenu("&View");
    QMenu *tools = menuBar()->addMenu("&Tools");
    QMenu *help = menuBar()->addMenu(helppix, "&Help");

    /** Помещаем действие в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(open);
    file->addAction(save);
    file->addAction(quit);
    help->addAction(about);
    edit->addAction(color);
    edit->addAction(font);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, this, QApplication::quit);
    connect(about, &QAction::triggered, this, &Menu::helpButton);
    connect(color, &QAction::triggered, this, &Menu::colorButton);
    connect(newfile, &QAction::triggered, this, &Menu::newFileButton);
    connect(font, &QAction::triggered, this, &Menu::fontButton);
    connect(open, &QAction::triggered, this, &Menu::openButton);


    /**  Штука, чтобы отображались иконки */
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    /** Сочетание клавиш */
    newfile->setShortcut(tr("CTRL+N"));
    open->setShortcut(tr("CTRL+O"));
    save->setShortcut(tr("CTRL+S"));
    quit->setShortcut(tr("CTRL+Q"));
    color->setShortcut(tr("CTRL+C"));
    font->setShortcut(tr("CTRL+F"));
}

void Menu::newFileButton() {
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}

void Menu::helpButton() {
    QTextStream out(stdout);
    out << "HELP ME" << endl;
}

void Menu::colorButton() {
    mcolor = QColorDialog::getColor(Qt::yellow, this);
    if (mcolor.isValid())
        qDebug() << "Color Choosen : " << mcolor.name();
    changeColor(mcolor);
}

void Menu::changeColor(QColor newColor) {
    scene.setColor(newColor);
}

void Menu::fontButton() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 18), this, tr("Pick a font"));
    if (ok) {
        qDebug() << "font           : " << font;
        qDebug() << "font weight    : " << font.weight();
        qDebug() << "font family    : " << font.family();
        qDebug() << "font style     : " << font.style();
        qDebug() << "font pointSize : " << font.pointSize();
    }
}

void Menu::changeFont(QFont newFont) {
    scene.setFont(newFont);
}

void Menu::openButton() {
    /** Поставить другое расширение */
    QString str = QFileDialog::getExistingDirectory(0, "Open Dialog", "");
}

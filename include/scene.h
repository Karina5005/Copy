#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(QColor newColor);

    QColor color;

    QFont font;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    QGraphicsItem *m_activeItem;
};

#endif

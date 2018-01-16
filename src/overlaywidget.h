#ifndef OVERLAYMAINWINDOW_H
#define OVERLAYMAINWINDOW_H

#include <QGraphicsOpacityEffect>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QWindow>

class OverlayWidget : public QWidget {
  Q_OBJECT

public: // member functions
  // OverlayMainWindow();
  OverlayWidget(QWidget *parent = 0);
  ~OverlayWidget();

  void setBackgroundWidget(QWidget *backGroundWidget);
  virtual void show();
  void setTransparent(bool transparent);
  void setOpacity(const float &opacity = 0.8);

  void frameAction(float dt);

  void startGame() { states = START; }
  void callOutMenu() { states = MENU; }
  void playGame() { states = GAMING; }
  void endGame() { states = END; }

protected: // member functions
  bool eventFilter(QObject *obj, QEvent *event);
  virtual void changeEvent(QEvent *event);
  void paintEvent(QPaintEvent *);

private: // member variables
  QWidget *m_pBackgroundWidget;

  float shootSize = 10;

  enum { START = 0, MENU, GAMING, END } states = START;
  float startOpacity = 0, menuOpacity = 0, gamingOpacity = 0, endOpacity = 0;
};

#endif // OVERLAYMAINWINDOW_H

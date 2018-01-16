#ifndef OVERLAYMAINWINDOW_H
#define OVERLAYMAINWINDOW_H

#include <QGraphicsOpacityEffect>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QWindow>

// class OverlayMainWindow : public QMainWindow
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

protected: // member functions
  bool eventFilter(QObject *obj, QEvent *event);
  virtual void changeEvent(QEvent *event);

private: // member variables
  QWidget *m_pBackgroundWidget;
};

#endif // OVERLAYMAINWINDOW_H

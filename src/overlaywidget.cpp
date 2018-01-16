#include "overlaywidget.h"
#include <QHBoxLayout>
#include <QTime>
#include <QVBoxLayout>
#include <QWindowStateChangeEvent>
#define WAIT_TIME_TO_MAXIMIZE_OVERLAY_MS 300

OverlayWidget::OverlayWidget(QWidget *parent) : QWidget(parent, Qt::SubWindow) {
  setWindowFlags(windowFlags() | Qt::SubWindow);
  setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
  setTransparent(true);
  // setTransparent(false);

  QPushButton *m_modelButton = new QPushButton("Load model");
  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(m_modelButton);
  this->setLayout(layout);
}

OverlayWidget::~OverlayWidget() {}

void OverlayWidget::setBackgroundWidget(QWidget *widget) {
  m_pBackgroundWidget = widget;
  m_pBackgroundWidget->installEventFilter(this);
}

void OverlayWidget::show() {

  setGeometry(m_pBackgroundWidget->geometry());
  QWidget::show();
}

void OverlayWidget::setTransparent(bool transparent) {
  if (transparent) {
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setOpacity();
  } else {
    setAttribute(Qt::WA_TranslucentBackground, false);
    setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
  }
}

void OverlayWidget::setOpacity(const float &opacity) {
  QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
  this->setGraphicsEffect(opacityEffect);
  opacityEffect->setOpacity(opacity);
}

/** receives the events from the event dispatcher before the background widget,
*if returns true the background widget will not receive the events
*	For backgreound to delegate event handling to this we have to call the
*inherited qobject function ==> background->installEventFilter(overlay);
*/
bool OverlayWidget::eventFilter(QObject *obj, QEvent *event) {
  if (obj == m_pBackgroundWidget) {
    if (event->type() == QEvent::Show)
      this->show();
    if (event->type() == QEvent::Close) {
      m_pBackgroundWidget = NULL; // if you dont set is as null the qt refrence
                                  // counter will not let the overlay to close
      this->close();
    }
    if (event->type() == QEvent::Resize)
      setGeometry(m_pBackgroundWidget->geometry());
    if (event->type() == QEvent::Move)
      setGeometry(m_pBackgroundWidget->geometry());
    if (event->type() == QEvent::WindowStateChange) {
      if (!m_pBackgroundWidget->isMinimized()) {

        // wait until window is restored from minimised state
        QWindowStateChangeEvent *e =
            static_cast<QWindowStateChangeEvent *>(event);
        if (e->oldState() & Qt::WindowMinimized) {
          QTime dieTime =
              QTime::currentTime().addMSecs(WAIT_TIME_TO_MAXIMIZE_OVERLAY_MS);
          while (QTime::currentTime() < dieTime)
            ;
        }

        show();
      } else
        hide();
    }

    // if another window from another application is put on top hide overlay
    // (because it is set to alwause stay on top of all windows)
    if (event->type() == QEvent::ActivationChange) {
      if (!m_pBackgroundWidget->isActiveWindow() & !isActiveWindow())
        hide();

      else
        show();
    }
  }

  return false;
}

void OverlayWidget::changeEvent(QEvent *event) {
  if (event->type() == QEvent::ActivationChange) {
    if (!isActiveWindow() & !m_pBackgroundWidget->isActiveWindow())
      hide();
    else
      this->show();
  }
}

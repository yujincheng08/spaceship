#include "overlaywidget.h"
#include "controller.h"
#include <QTime>
#include <QWindowStateChangeEvent>
#define WAIT_TIME_TO_MAXIMIZE_OVERLAY_MS 300

OverlayWidget::OverlayWidget(Controller *controller, QWidget *parent)
    : QWidget(parent, Qt::SubWindow) {
  this->controller = controller;
  setWindowFlags(windowFlags() | Qt::SubWindow);
  setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
  setTransparent(true);

  connect(&timer, &QTimer::timeout, this, &OverlayWidget::frameAction);
  timer.start(100);
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

void OverlayWidget::frameAction() {
  float dt = 0.1;
  Controller::STATE state = controller->getState();
  if (state == Controller::START)
    startOpacity += dt;
  else
    startOpacity -= dt;
  if (state == Controller::MENU)
    menuOpacity += dt;
  else
    menuOpacity -= dt;
  if (state == Controller::GAMING)
    gamingOpacity += dt;
  else
    gamingOpacity -= dt;
  if (state == Controller::END)
    endOpacity += dt;
  else
    endOpacity -= dt;
  if (startOpacity < 0)
    startOpacity = 0;
  if (startOpacity > 1)
    startOpacity = 1;
  if (menuOpacity < 0)
    menuOpacity = 0;
  if (menuOpacity > 1)
    menuOpacity = 1;
  if (gamingOpacity < 0)
    gamingOpacity = 0;
  if (gamingOpacity > 1)
    gamingOpacity = 1;
  if (endOpacity < 0)
    endOpacity = 0;
  if (endOpacity > 1)
    endOpacity = 1;
  repaint();
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

void OverlayWidget::paintEvent(QPaintEvent *) {
  QPainter pter(this);
  pter.setPen(Qt::white);

  // paint start
  pter.setFont(QFont("Arial", 30, 5));
  pter.setOpacity(startOpacity);
  pter.drawText(0, this->height() / 2, this->width(), 30, Qt::AlignCenter,
                "Press Enter to Start Game...");

  // paint menu

  // paint gaming
  pter.setOpacity(gamingOpacity);
  pter.drawLine(this->width() / 2 - shootSize, this->height() / 2,
                this->width() / 2 + shootSize, this->height() / 2);
  pter.drawLine(this->width() / 2, this->height() / 2 - shootSize,
                this->width() / 2, this->height() / 2 + shootSize);

  // paint end
}

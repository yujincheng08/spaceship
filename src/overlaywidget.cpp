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
  setWindowFlags(windowFlags() | Qt::X11BypassWindowManagerHint);
  // setCursor(Qt::BlankCursor);
  setTransparent(true);

  connect(&timer, &QTimer::timeout, this, &OverlayWidget::frameAction);
  timer.start(10);
  setFocusPolicy(Qt::NoFocus);
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
  float dt = 0.01;
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
    if (event->type() == QEvent::CursorChange) {
      qDebug() << "Changed";
      setCursor(m_pBackgroundWidget->cursor());
    }
  }

  return false;
}

void OverlayWidget::changeEvent(QEvent *event) {
  qDebug() << event->type();
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
  pter.setFont(QFont("Arial", 20, 2));
  pter.setOpacity(menuOpacity);
  pter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,
                "Use W / S to move forward / back.\n\n"
                "Use A / D / E / C to turn left / right / up / down.\n\n"
                "Press left button to shoot.\n\n"
                "Shrink your mouse to rotate the view.\n\n"
                "Use Esc to pause / continue the game.");

  // paint gaming
  int cx = this->width() / 2, cy = this->height() * 21 / 40;
  pter.setOpacity(gamingOpacity);
  pter.drawLine(cx - shootSize, cy, cx + shootSize, cy);
  pter.drawLine(cx, cy - shootSize, cx, cy + shootSize);
  pter.setFont(QFont("Arial", 10, 2));
  if (abs(SpaceshipSpeed) < 1e-6)
    setSpeed(0);
  QString st = QString::number(SpaceshipSpeed);
  pter.drawText(0, 0, this->width() / 8, this->height() / 8, Qt::AlignCenter,
                "Speed:" + st);

  // paint end
  pter.setFont(QFont("Arial", 30, 5));
  pter.setOpacity(endOpacity);
  pter.drawText(0, this->height() / 2, this->width(), 30, Qt::AlignCenter,
                "You Lose! Press Esc to Quit Game.");
}

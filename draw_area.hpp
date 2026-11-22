#pragma once

#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <functional>

// Поле для рисования: чёрный фон, белая кисть (как в MNIST).
class DrawArea : public QWidget {
public:
  static constexpr int kSize = 280;     // размер поля в пикселях
  static constexpr int kPenWidth = 15;  // толщина кисти

  explicit DrawArea(QWidget* parent = nullptr)
      : QWidget(parent), image_(kSize, kSize, QImage::Format_RGB32) {
    setFixedSize(kSize, kSize);
    setCursor(Qt::CrossCursor);
    image_.fill(Qt::black);
  }

  const QImage& image() const {
    return image_;
  }

  void clear() {
    image_.fill(Qt::black);
    update();
  }

  // вызывается, когда отпустили кнопку мыши (закончили штрих)
  std::function<void()> on_stroke_finished;

protected:
  void paintEvent(QPaintEvent*) override {
    QPainter painter(this);
    painter.drawImage(0, 0, image_);
  }

  void mousePressEvent(QMouseEvent* event) override {
    if (event->button() == Qt::LeftButton) {
      drawing_ = true;
      last_ = event->position().toPoint();
      draw_line(last_, last_);
    }
  }

  void mouseMoveEvent(QMouseEvent* event) override {
    if (drawing_) {
      QPoint current = event->position().toPoint();
      draw_line(last_, current);
      last_ = current;
    }
  }

  void mouseReleaseEvent(QMouseEvent* event) override {
    if (event->button() == Qt::LeftButton && drawing_) {
      drawing_ = false;
      if (on_stroke_finished) {
        on_stroke_finished();
      }
    }
  }

private:
  void draw_line(const QPoint& from, const QPoint& to) {
    QPainter painter(&image_);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, kPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if (from == to) {
      painter.drawPoint(from);
    } else {
      painter.drawLine(from, to);
    }
    update();
  }

  QImage image_;
  QPoint last_;
  bool drawing_ = false;
};
#include <QApplication>
#include <QDir>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>
#include <vector>

#include "activate_func.hpp"
#include "draw_area.hpp"
#include "layer.hpp"
#include "matrix.hpp"
#include "mlp.hpp"
#include "preprocess.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // файлы весов (w1b1.txt, w2b2.txt) ищем рядом с gui.exe
  QDir::setCurrent(QCoreApplication::applicationDirPath());

  // Сеть той же архитектуры, что и при обучении: 784 -> 128 (ReLU) -> 10 (Softmax).
  // Случайные веса тут перезапишутся загрузкой из файлов.
  Matrix w1(128, 784);
  Matrix b1(128, 1);
  Matrix w2(10, 128);
  Matrix b2(10, 1);

  std::vector<Layer> layers{{w1, b1, RELU}, {w2, b2, SOFTMAX}};
  MLP net(layers);

  if (net.r_layers() != 0) {
    QMessageBox::critical(nullptr, "Ошибка",
                          "Не удалось загрузить веса.\n"
                          "Положите w1b1.txt и w2b2.txt рядом с gui.exe:\n" +
                              QCoreApplication::applicationDirPath());
    return 1;
  }

  // ---- окно ----
  QWidget window;
  window.setWindowTitle("Распознавание цифр (многослойный перцептрон)");

  DrawArea* area = new DrawArea;

  QLabel* answer = new QLabel("Нарисуйте цифру");
  QFont big_font = answer->font();
  big_font.setPointSize(26);
  big_font.setBold(true);
  answer->setFont(big_font);

  QLabel* confidence = new QLabel("");

  QPushButton* clear_button = new QPushButton("Очистить");

  QVBoxLayout* right = new QVBoxLayout;
  right->addWidget(answer);
  right->addWidget(confidence);

  // 10 полосок: вероятность каждой цифры
  std::vector<QProgressBar*> bars;
  for (int digit = 0; digit < 10; digit++) {
    QHBoxLayout* row = new QHBoxLayout;
    QLabel* name = new QLabel(QString::number(digit));
    name->setFixedWidth(14);

    QProgressBar* bar = new QProgressBar;
    bar->setRange(0, 100);
    bar->setValue(0);

    row->addWidget(name);
    row->addWidget(bar);
    right->addLayout(row);
    bars.push_back(bar);
  }

  right->addStretch();
  right->addWidget(clear_button);

  QHBoxLayout* main_layout = new QHBoxLayout(&window);
  main_layout->addWidget(area);
  main_layout->addLayout(right);

  // ---- логика ----
  auto reset_display = [&]() {
    answer->setText("Нарисуйте цифру");
    confidence->setText("");
    for (size_t i = 0; i < bars.size(); i++) {
      bars[i]->setValue(0);
    }
  };

  auto recognize = [&]() {
    Matrix x(784, 1);
    if (!image_to_mnist(area->image(), x)) {
      reset_display();
      return;
    }

    Matrix p = net.forward(x);   // 10x1, вероятности

    size_t best = 0;
    for (size_t i = 1; i < p.row(); i++) {
      if (p.at(i, 0) > p.at(best, 0)) {
        best = i;
      }
    }

    answer->setText(QString("Это: %1").arg(static_cast<int>(best)));
    confidence->setText(QString("Уверенность: %1%").arg(p.at(best, 0) * 100.0, 0, 'f', 1));

    for (size_t i = 0; i < bars.size(); i++) {
      bars[i]->setValue(static_cast<int>(std::lround(p.at(i, 0) * 100.0)));
    }
  };

  // распознаём каждый раз, когда закончили штрих
  area->on_stroke_finished = recognize;

  QObject::connect(clear_button, &QPushButton::clicked, [&]() {
    area->clear();
    reset_display();
  });

  window.show();
  return app.exec();
}
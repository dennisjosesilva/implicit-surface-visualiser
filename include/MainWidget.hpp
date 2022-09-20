#include "GraphicsViewWidget.hpp"
#include <QWidget>

class MainWidget : public QWidget
{
public:
  MainWidget(QWidget *parent=nullptr);

  void resizeEvent(QResizeEvent *e);

private:
  GraphicsViewWidget *gview_;
};
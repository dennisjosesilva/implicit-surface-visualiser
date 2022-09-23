#include "GraphicsViewWidget.hpp"
#include <QWidget>

class QComboBox;

class MainWidget : public QWidget
{
public:
  MainWidget(QWidget *parent=nullptr);

  void resizeEvent(QResizeEvent *e);

protected slots:
  void primitiveComboBox_currentIndexChanged(int index);


private:
  GraphicsViewWidget *gview_;
  QComboBox *primitiveComboBox_;
};
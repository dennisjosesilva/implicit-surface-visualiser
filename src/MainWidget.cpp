#include "MainWidget.hpp"

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QComboBox>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
  :QWidget{parent}
{
  QHBoxLayout *layout = new QHBoxLayout;
  QVBoxLayout *leftLayout = new QVBoxLayout;
  QVBoxLayout *rightLayout = new QVBoxLayout;
  QHBoxLayout *primitiveLayout = new QHBoxLayout;

  QWidget *leftWidget = new QWidget{this};

  QLabel *label = new QLabel{"Primitive: ", leftWidget};
  primitiveLayout->addWidget(label);

  QComboBox *primitivesComboBox = new QComboBox{leftWidget};
  primitivesComboBox->addItem("Sphere");
  primitivesComboBox->addItem("Torus");
  primitivesComboBox->addItem("Skel points");
  primitiveLayout->addWidget(primitivesComboBox);

  leftLayout->addItem(primitiveLayout);  
  leftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  leftWidget->setLayout(leftLayout);
  layout->addWidget(leftWidget);
  leftWidget->setFixedWidth(360);

  GraphicsViewWidget *gview_ = new GraphicsViewWidget{this};  
  layout->addWidget(gview_);
  gview_->setMinimumWidth(720);
  setLayout(layout);  
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
  
}
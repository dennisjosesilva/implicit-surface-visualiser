#include "MainWidget.hpp"

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QComboBox>

#include <QDebug>

#include "ImplicitSurface/Primitives/ImplicitSphere.hpp"
#include "ImplicitSurface/Primitives/ImplicitTorus.hpp"
#include "ImplicitSurface/Primitives/ImplicitTwoSkelPoints.hpp"

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

  primitiveComboBox_ = new QComboBox{leftWidget};
  primitiveComboBox_->addItem("Sphere", ImplicitPrimitiveType::SPHERE);
  primitiveComboBox_->addItem("Torus", ImplicitPrimitiveType::TORUS);
  primitiveComboBox_->addItem("Skel Points", ImplicitPrimitiveType::TWO_SKEL_POINTS);
  primitiveComboBox_->addItem("Skel line", ImplicitPrimitiveType::LINE_SKEL);
  connect(primitiveComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), 
    this, &MainWidget::primitiveComboBox_currentIndexChanged);
  primitiveLayout->addWidget(primitiveComboBox_);


  leftLayout->addItem(primitiveLayout);  
  leftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  leftWidget->setLayout(leftLayout);
  layout->addWidget(leftWidget);
  leftWidget->setFixedWidth(360);

  gview_ = new GraphicsViewWidget{this};  
  layout->addWidget(gview_);
  gview_->setMinimumWidth(720);
  setLayout(layout);  
}

void MainWidget::primitiveComboBox_currentIndexChanged(int index)
{
  ImplicitPrimitiveType primitiveType = 
    static_cast<ImplicitPrimitiveType>(primitiveComboBox_->currentData().toInt());
  gview_->changeImplicitPrimitive(primitiveType);
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
  
}
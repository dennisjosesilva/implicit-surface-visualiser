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
  primitiveComboBox_->addItem("Sphere");
  primitiveComboBox_->addItem("Torus");
  primitiveComboBox_->addItem("Skel Points");
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
  if (primitiveComboBox_->currentText() == "Skel Points") {
    gview_->changeImplicitPrimitive(ImplicitPrimitiveType::TWO_SKEL_POINTS);
  } else if (primitiveComboBox_->currentText() == "Torus") {
    gview_->changeImplicitPrimitive(ImplicitPrimitiveType::TORUS);
  }
  else if (primitiveComboBox_->currentText() == "Sphere") {
    gview_->changeImplicitPrimitive(ImplicitPrimitiveType::SPHERE);
  }
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
  
}
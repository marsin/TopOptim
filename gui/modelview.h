#ifndef MODELVIEW_H
#define MODELVIEW_H
#include <QtOpenGL>
#include <QGLWidget>
#include <part.h>
#include <model.h>
#include <gui/geometry.h>
#include <optimalizationmanager.h>
#include <filemanager.h>
#include <opencv2/highgui/highgui.hpp>
#include <configurations.h>

struct SmMovement
{
  int xRot;
  int yRot;
  int zRot;
  float xMove = 0;
  float yMove = 0;
  float zMove = 0;
  QPoint movePoint{};
  float xPos;
  float yPos;
  float zPos;
  float zoom = 20;
  bool isOn;
};

class ModelView : public QGLWidget, protected QGLFunctions
{
  Q_OBJECT
public:
  explicit ModelView(QWidget *parent = 0);
  void init(const CmModelp model, const configurations& p_config);
  void setUpdateFaces(bool p_isFacesUpdated, const configurations &p_config);
  void setModeCollectionViewer(bool p_isCollectionViewer, const std::vector<std::vector<int> > &p_collection);
  void setCollectionPosition(int p_position);

protected:
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void initializeGL();
  void initShaders();
  void resizeGL(int w, int h);
  void paintGL();
  void drawVertices();


private:
  bool CaptureScreenShot(int nWidth = 800, int nHeight = 800);
  bool m_isFacesUpdated = false;
  bool m_isViewUpdated = false;
  CmModelp m_model;
  QTimer m_RenderTimer;
  SmModelDrawSettings m_settings;
  SmMovement m_movement;
  std::vector<int> m_genome;
  std::vector<int> m_genomeFull;
  int m_windowWidth;
  int m_windowHeight;
  cv::VideoWriter m_videoWriter;
  configurations m_config;
  int m_frameCounter = 0;
  bool m_isCollectionViewer = false;
  int m_collectionPossition = 0;
  std::vector<std::vector<int> > m_collection{};
signals:

public slots:

};



#endif // MODELVIEW_H

#include "modelview.h"
#include <QVector2D>
#include <QVector3D>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QGLShaderProgram>
#include <QGLWidget>
#include <GL/glu.h>
#include <vertex.h>
#include <QImage>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

struct VertexData
{
  QVector3D position;
  QVector2D texCoord;
};

ModelView::ModelView(QWidget *parent) :
  QGLWidget(parent)
{
  connect(&m_RenderTimer, SIGNAL(timeout()), this, SLOT(update()));
  m_RenderTimer.start(600);
  m_model = CmModelp();
  m_settings.drawBCs = true;
  m_settings.drawLoads = true;
  m_settings.drawVertices = true;
  m_settings.drawFaces = true;
  m_settings.drawBorderLines = m_settings.drawFaces;
  m_videoWriter = cv::VideoWriter();
}

void ModelView::init(const CmModelp model, const configurations &p_config)
{
  m_config = p_config;
  m_model = model;
  if(m_model && m_model->Parts().size() > 0)
  {
    int numOfFaces = m_model->Parts()[0]->Faces().size();
    m_genomeFull.assign(numOfFaces, 1);
  }
  m_genome = m_genomeFull;
}

void ModelView::setUpdateFaces(bool p_isFacesUpdated, const configurations& p_config)
{
  m_config = p_config;
  m_isFacesUpdated = p_isFacesUpdated;
  m_isViewUpdated = p_isFacesUpdated;
  m_frameCounter = p_config.intervalBetweenSnapshot;
}

void ModelView::setModeCollectionViewer(bool p_isCollectionViewer, const std::vector<std::vector<int> > &p_collection = {})
{
    m_isCollectionViewer = p_isCollectionViewer;
    if(m_isCollectionViewer)
    {
        m_collection = p_collection;
    }
}

void ModelView::setCollectionPosition(int p_possition)
{
    m_collectionPossition = p_possition;
}

void ModelView::mousePressEvent(QMouseEvent *e)
{
  m_movement.isOn = true;
  m_movement.movePoint = e->pos();
}

void ModelView::mouseReleaseEvent(QMouseEvent *e)
{
  m_movement.isOn = false;
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
  if(m_movement.isOn and m_model)
  {
    m_model->MoveModel((event->pos() - m_movement.movePoint) / 10);
    m_movement.movePoint = event->pos();
  }
}

void ModelView::wheelEvent(QWheelEvent *event)
{
  m_movement.zoom += event->delta()/100;
  m_movement.zoom = abs(m_movement.zoom);
}


void ModelView::initializeGL()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void ModelView::resizeGL(int w, int h)
{
  double xMin = 0, xMax = 10, yMin = 0, yMax = 10;
  //glViewport(0,0,(GLint)w,(GLint)h);
  w = 800;
  h = 800;
  glViewport(0,0,800,800);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1,-1,1);
  if(w < h)
  {
    h = h?h:1;
    double newW = (xMax - xMin) * w / h;
    double difW = newW - (xMax - xMin);
    xMin = 0.0 + difW / 2.0;
    xMax = 10 + difW / 2.0;
  }
  else
  {
    w = w?w:1;
    double newH = (yMax - yMin) * w / h;
    double difH = newH - (yMax - yMin);
    yMin = 0.0 + difH / 2.0;
    yMax = 10 + difH / 2.0;
  }
  gluOrtho2D(xMin,xMax,yMin,yMax);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void ModelView::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslated(5.0,5.0,0.0);
  glLineWidth(1.0);
  glColor3f(0,0.7f,0.7f);

  int sides = 3;
  float radius = 1.0;

  glLineWidth(1);
  glColor3f(0,0,0);

  float zoom = m_movement.zoom;
  if(m_model != 0)
  {
    CmPartp part = m_model->Parts()[0];
    if(m_settings.drawFaces)
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glColor3f(0,1,0);
      std::vector<CmFacep> faces = part->Faces();
      if(m_isFacesUpdated)
      {
        if(m_isCollectionViewer)
        {
            m_genome = m_collection[m_collectionPossition];
        }
        else
        {
            int error = 0;
            std::vector<int> l_genome;

            l_genome = fm::FileManager::OpenGenomeFile("temp.genome", &error);
            if(error == 0)
            {
              if(l_genome.size() >= m_model->Parts()[0]->Faces().size() and l_genome != m_genome)
              {
                  m_genome = l_genome;
                  m_isViewUpdated = true;
              }
            }
        }
      }
      else
      {
        m_genome = m_genomeFull;
      }
      //for(std::vector<CmFacep>::iterator it=faces.begin();it!=faces.end();it++)
      for(int it = 0; it < faces.size(); ++it)
      {
        if(m_genome[it] == 1)
        {
          glBegin(GL_POLYGON);
          vertexp ver = part->Vertices()[faces[it]->BL()];
          glVertex3f(ver->X_pos() / zoom, ver->Y_pos() / zoom,(ver->Z_pos()/zoom));
          ver = part->Vertices()[faces[it]->BR()];
          glVertex3f(ver->X_pos() / zoom, ver->Y_pos() / zoom,(ver->Z_pos()/zoom));
          ver = part->Vertices()[faces[it]->TR()];
          glVertex3f(ver->X_pos() / zoom, ver->Y_pos() / zoom,(ver->Z_pos()/zoom));
          ver = part->Vertices()[faces[it]->TL()];
          glVertex3f(ver->X_pos() / zoom, ver->Y_pos() / zoom,(ver->Z_pos()/zoom));
          glEnd();
        }
      }
    }
    if(m_settings.drawBorderLines)
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glColor3f(0,0,0);
      std::vector<CmFacep> faces = part->Faces();
      for(std::vector<CmFacep>::iterator it=faces.begin();it!=faces.end();it++)
      {
        glBegin(GL_LINE_LOOP);
        vertexp ver = part->Vertices()[(*it)->BL()];
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        ver = part->Vertices()[(*it)->BR()];
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        ver = part->Vertices()[(*it)->TR()];
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        ver = part->Vertices()[(*it)->TL()];
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        glEnd();
      }
    }
    if(m_settings.drawVertices)
    {
      glColor3f(0,0,0);
      glPointSize(2.0);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

      std::vector<vertexp> vertices = part->Vertices();
      for(std::vector<vertexp>::iterator it=vertices.begin();it!=vertices.end();it++)
      {
        glBegin(GL_POINTS);
        glVertex3f(((*it)->X_pos()/zoom),((*it)->Y_pos()/zoom),((*it)->Z_pos()/zoom));
        glEnd();
      }
    }
    if(m_settings.drawBCs)
    {
      glColor3f(0,0,1);
      glPointSize(2.5);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      std::set<unsigned int> bcs = part->GetAllBCsVerticesIndex();
      for(std::set<unsigned int>::iterator it=bcs.begin();it!=bcs.end();it++)
      {
        vertexp ver = part->Vertices()[*it];
        glBegin(GL_POINTS);
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        glEnd();
      }
    }
    if(m_settings.drawLoads)
    {
      glColor3f(1,0,0);
      glPointSize(2.5);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      std::set<unsigned int> loads = part->GetAllLoadsVerticesIndex();
      for(std::set<unsigned int>::iterator it=loads.begin();it!=loads.end();it++)
      {
        vertexp ver = part->Vertices()[*it];
        glBegin(GL_POINTS);
        glVertex3f((ver->X_pos()/zoom),(ver->Y_pos()/zoom),(ver->Z_pos()/zoom));
        glEnd();
      }
    }
    if(m_config.recordVideo and m_isViewUpdated)
    {
        if (m_config.intervalBetweenSnapshot == m_frameCounter)
        {
            CaptureScreenShot();
            m_frameCounter = 0;
        }
        else
        {
            ++m_frameCounter;
        }
        m_isViewUpdated = false;
    }
  }
}


bool ModelView::CaptureScreenShot(int nWidth, int nHeight)
{
    if(m_videoWriter.isOpened())
    {
        glFlush(); glFinish();
        cv::Mat l_mat(nWidth, nHeight, CV_8UC3);
        glReadPixels(0, 0, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, l_mat.data);
        if(l_mat.empty())
            return false;
        cv::flip(l_mat, l_mat, 0);
        m_videoWriter.write(l_mat);
        return true;
    }
    else
    {
        cv::Size l_frameSize(nWidth, nHeight);
        m_videoWriter.open("recordings.avi", -1, m_config.fpsForRecordings, l_frameSize, true);
        bool r = m_videoWriter.isOpened();
        return r;
    }
}

#include "gui/geometry.h"
#include <QVector2D>
#include <QVector3D>
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

CmGeometry::CmGeometry()
{
}

CmGeometry::~CmGeometry()
{
}


void CmGeometry::init(const CmModelp &model, const SmModelDrawSettings &settings)
{
  m_model = model;
  m_settings = settings;
  initializeGLFunctions();
  glGenBuffers(2,m_vboIds);
  initModelGeometry();
}

void CmGeometry::drawGeometry()
{
  float zoom = 10.0;
  float moveOnX = 5.0;
  float moveOnY = 0;
  float moveOnZ = 0;
  if(m_model != 0)
  {
    CmPartp part = m_model->Parts()[0];
    if(m_settings.drawFaces)
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glColor3f(0,1,0);
      std::vector<CmFacep> faces = part->Faces();
      for(std::vector<CmFacep>::iterator it=faces.begin();it!=faces.end();it++)
      {
        glBegin(GL_POLYGON);
        vertexp ver = part->Vertices()[(*it)->BL()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->BR()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->TR()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->TL()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        glEnd();
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
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->BR()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->TR()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        ver = part->Vertices()[(*it)->TL()];
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
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
        glVertex3f(((*it)->X_pos()/zoom)+moveOnX,((*it)->Y_pos()/zoom)+moveOnY,((*it)->Z_pos()/zoom)+moveOnZ);
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
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
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
        glVertex3f((ver->X_pos()/zoom)+moveOnX,(ver->Y_pos()/zoom)+moveOnY,(ver->Z_pos()/zoom)+moveOnZ);
        glEnd();
      }
    }

  }
}

void CmGeometry::initModelGeometry()
{

}

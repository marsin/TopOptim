#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QGLFunctions>
#include <QGLShaderProgram>
#include "part.h"
#include "model.h"

struct SmModelDrawSettings
{
  bool drawFaces;
  bool drawBorderLines;
  bool drawBCs;
  bool drawLoads;
  bool drawVertices;

};


class CmGeometry : protected QGLFunctions
{
public:
  CmGeometry();
  virtual ~CmGeometry();
  void init(const CmModelp& model, const SmModelDrawSettings &settings);
  void drawGeometry();

private:
    void initModelGeometry();
    CmModelp m_model;
    SmModelDrawSettings m_settings;
    GLuint m_vboIds[2];
};
typedef boost::shared_ptr<CmGeometry> CmGeometryp;


#endif // GEOMETRY_H

#include "model.h"

CmModel::CmModel(const std::string &name)
{
    m_name = name;
}

void CmModel::AddPart(const CmPartp &part)
{
    m_parts.push_back(part);
}

void CmModel::Parts(const std::vector<CmPartp> &parts)
{
    m_parts = parts;
}

std::vector<CmPartp> CmModel::Parts()
{
  return m_parts;
}

void CmModel::MoveModel(const QPoint &pos)
{
  for (CmPartp part : m_parts)
  {
    std::vector<vertexp> vertices = part->Vertices();
    for(vertexp vertex : vertices)
    {
      vertex->X_pos(vertex->X_pos() + pos.x());
      vertex->Y_pos(vertex->Y_pos() - pos.y());
    }
    part->Vertices(vertices);
  }
}

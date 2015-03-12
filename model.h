#ifndef MODEL_H
#define MODEL_H
#include <boost/shared_ptr.hpp>
#include <vector>
#include <part.h>
#include <QPoint>

class CmModel
{
public:
    CmModel(const std::string &name);

    void AddPart (const CmPartp &CmPart);


    void Parts (const std::vector<CmPartp> &parts);
    std::vector<CmPartp> Parts();
    void MoveModel(const QPoint &pos);
private:

    std::string m_name;
    std::vector<CmPartp> m_parts;
};
typedef boost::shared_ptr<CmModel> CmModelp;

#endif // MODEL_H

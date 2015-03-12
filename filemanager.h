#ifndef FILESMANAGER_H
#define FILESMANAGER_H
#include <model.h>
#include <part.h>
#include <ga/GA1DArrayGenome.h>
#include <configurations.h>


namespace fm {
const std::string g_collectionExt{".coll"};
class FileManager
{
public:
  enum elemType {other, faceType, verticeType};
  static CmModelp OpenModelFile(const std::string &path, int &error);
  static void SaveTextToFile(const std::string &text,const std::string &fileName, int &error);
  static void SaveGenomeToFile(const GA1DArrayAlleleGenome<int> p_genome, const std::string &p_fileName, const std::string p_comment = "");
  static void SaveGenomeToFile(const std::vector<int> p_genome, const std::string &p_fileName, const std::string p_comment = "");
  static std::vector<int> OpenGenomeFile(const std::string &p_path, int *p_error);
  static void DeleteAnyFile(const std::string &p_path);
  static void CreateFolder(const std::string &p_path);
  static void CopyFileAndReplace(const std::string &p_source, const std::string &p_destination);
  static void SaveConfigurationsToFile(const configurations &p_config, const std::string &p_destination);
  static void AppendToGenomeCollector(const configurations &p_config, const std::string &p_text, const std::string p_comment = "");
  static void AppendToGenomeCollector(const configurations &p_config, const GA1DArrayAlleleGenome<int> &p_genome, const std::string p_comment = "");
  static void AppendToGenomeCollector(const configurations &p_config, const std::vector<int> &p_genome, const std::string p_comment);
  static std::vector<std::vector<int>> OpenGenomeCollectionFile(const std::string &p_path, int p_error);

private:

};
}

#endif // FILESMANAGER_H

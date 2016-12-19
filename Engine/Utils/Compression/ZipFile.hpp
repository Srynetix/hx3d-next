#pragma once

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Core/Types.hpp>

#include <miniz.h>

namespace hx3d {
namespace Utils {
namespace Compression {

class ZipFile {
public:
  class Stat {
  public:
    Stat();
    Stat(const mz_zip_archive_file_stat& p_stat);
    void loadStat(const mz_zip_archive_file_stat& p_stat);

    const char* getFilename() const;
    const char* getComment() const;
    U64 getUncompressedSize() const;
    U64 getCompressedSize() const;

  private:
    mz_zip_archive_file_stat m_stat;
  };

  ZipFile();
  ~ZipFile();

  void loadFromFile(const std::string& p_str);
  U32 getFileCount();

  ZipFile::Stat getFileStat(const U32 p_id);
  Utils::File extractFileById(const U32 p_id);
  Utils::File extractFileByName(const std::string& p_name);

  void close();

private:
  HX3D_PIMPL
};

}
}
}

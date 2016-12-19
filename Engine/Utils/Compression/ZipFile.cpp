#include <Engine/Utils/Compression/ZipFile.hpp>
#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>
#include <Engine/Utils/Compression/Exceptions/ZipFileStatError.hpp>
#include <Engine/Utils/Compression/Exceptions/BadZipFileError.hpp>
#include <Engine/Utils/Compression/Exceptions/ZipFileExtractError.hpp>

namespace hx3d {
namespace Utils {
namespace Compression {

struct ZipFile::Impl {
  mz_zip_archive m_archive;
  Utils::File m_file;
  bool m_deleted;

  Impl():
    m_deleted(true) {
      m_archive = {0};
    }
};

ZipFile::ZipFile():
  HX3D_PIMPL_INIT() {}

ZipFile::~ZipFile() {
  close();
}

void ZipFile::loadFromFile(const std::string& p_str) {
  auto& loader = Root::Instance().getFileLoader();
  m_impl->m_file = loader.syncLoad(p_str, Utils::File::kBinary);

  mz_bool status = mz_zip_reader_init_mem(&m_impl->m_archive, m_impl->m_file.getContent(), m_impl->m_file.getSize(), 0);
  if (status == MZ_FALSE) {
    throw Exceptions::BadZipFileError(p_str);
  }

  HX3D_LOGGER(kUtils).debug("Zip file '{}' loaded.", p_str);
  m_impl->m_deleted = false;
}

void ZipFile::close() {
  if (!m_impl->m_deleted) {
    mz_zip_reader_end(&m_impl->m_archive);
  }
}

U32 ZipFile::getFileCount() {
  return mz_zip_reader_get_num_files(&m_impl->m_archive);
}

ZipFile::Stat ZipFile::getFileStat(const U32 p_id) {
  if (p_id > this->getFileCount()) {
    throw Exceptions::KeyNotFound<ZipFile, U32>(p_id);
  }

  mz_zip_archive_file_stat stat = {0};
  if (!mz_zip_reader_file_stat(&m_impl->m_archive, p_id, &stat)) {
    throw Exceptions::ZipFileStatError(p_id);
  }

  return Stat(stat);
}

Utils::File ZipFile::extractFileById(const U32 p_id) {
  auto stat = this->getFileStat(p_id);
  return this->extractFileByName(stat.getFilename());
}

Utils::File ZipFile::extractFileByName(const std::string& p_name) {
  size_t uncompressedSize = 0;
  auto content = mz_zip_reader_extract_file_to_heap(&m_impl->m_archive, p_name.c_str(), &uncompressedSize, 0);
  if (!content) {
    throw Exceptions::ZipFileExtractError(p_name);
  }

  Utils::File file;
  file.setRawValues(static_cast<char*>(content), uncompressedSize, Utils::File::kBinary);
  return file;
}

//////////////////
//////////////////

ZipFile::Stat::Stat() {
  m_stat = {0};
}

ZipFile::Stat::Stat(const mz_zip_archive_file_stat& p_stat):
  m_stat(p_stat)
{}

void ZipFile::Stat::loadStat(const mz_zip_archive_file_stat& p_stat) {
  m_stat = p_stat;
}

const char* ZipFile::Stat::getFilename() const {
  return m_stat.m_filename;
}

const char* ZipFile::Stat::getComment() const {
  return m_stat.m_comment;
}

U64 ZipFile::Stat::getUncompressedSize() const {
  return m_stat.m_uncomp_size;
}

U64 ZipFile::Stat::getCompressedSize() const {
  return m_stat.m_comp_size;
}

}
}
}

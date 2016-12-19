#include <Engine/Utils/Parsers/INIParser.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

#include <sstream>
#include <iostream>

#include <cctype>
#include <algorithm>

#include <map>
#include <vector>

namespace hx3d {
namespace Utils {

struct INIParser::Impl {
  std::string m_currentSection;
  std::map<std::string, std::map<std::string, std::string>> m_definitions;

  void handleLine(const std::string& p_line);
  std::string trim(const std::string& p_line);
	std::vector<std::string> split(const std::string& p_line, const char p_delim);
  const std::string& extract_value(const std::string& p_section, const std::string& p_key);
};

INIParser::INIParser(const std::string& p_content):
	m_impl(Utils::MakeUniquePtr<Impl>())
{
	if (p_content.size() > 0) {
		parse(p_content);
	}
}

INIParser::~INIParser() = default;

void INIParser::parse(const std::string& p_content) {
	std::istringstream iss(p_content);
	std::string current_line;

	while (std::getline(iss, current_line)) {
		m_impl->handleLine(current_line);
	}
}

std::vector<std::string> INIParser::Impl::split(const std::string& p_line, const char p_delim) {
	std::vector<std::string> result;

	size_t i = 0;
	size_t line_max = p_line.size();

	std::string curr_str;

	while (i < line_max) {
		char curr = p_line[i];

		if (curr == p_delim) {
			result.push_back(trim(curr_str));
			curr_str = "";
		}
		else {
			curr_str += curr;
		}

		i++;
	}

	result.push_back(trim(curr_str));
	return result;
}

std::string INIParser::Impl::trim(const std::string& p_line)
{
	auto wsfront = std::find_if_not(p_line.begin(), p_line.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(p_line.rbegin(), p_line.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

void INIParser::Impl::handleLine(const std::string& p_line) {
	const auto& logger = HX3D_LOGGER(kUtils);
	size_t line_size = p_line.size();
	size_t i = 0;

	if (line_size == 0)
		return;

	// Section
	else if (p_line[0] == '[' && p_line[line_size - 1] == ']') {
		std::string section_name;
		i++;

		while (i < line_size - 1) {
			section_name += p_line[i];
			i++;
		}

		m_currentSection = section_name;
		m_definitions[section_name] = {};
	}

	// Assign
	else {
		std::string key_name;

		auto kv = split(p_line, '=');
		if (kv.size() != 2) {
			logger.critical("Syntax error in INI file");
		}

		if (m_currentSection == "") {
			logger.critical("Assignations out of section in INI file");
		}

		const auto& k = kv[0];
		const auto& v = kv[1];

		m_definitions[m_currentSection][k] = v;
	}
}

const std::string& INIParser::extract_value(const std::string& p_section, const std::string& p_key) const {
	const auto& section = m_impl->m_definitions.find(p_section);
	if (section == m_impl->m_definitions.cend())
		throw Exceptions::KeyNotFound<INIParser, const std::string&>(p_section, "Section lookup");

	const auto& key = section->second.find(p_key);
	if (key == section->second.cend())
		throw Exceptions::KeyNotFound<INIParser, const std::string&>(p_key, "Key lookup");

	return key->second;
}

}
}

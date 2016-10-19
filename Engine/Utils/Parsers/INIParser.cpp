#include <Engine/Utils/Parsers/INIParser.hpp>

#include <Engine/Debug/Logging.hpp>

#include <sstream>
#include <iostream>

#include <cctype>
#include <algorithm>

namespace hx3d {
namespace Utils {

INIParser::INIParser(const std::string& p_content)
{
	if (p_content.size() > 0) {
		parse(p_content);
	}
}

void INIParser::parse(const std::string& p_content) {
	const auto& logger = HX3D_LOGGER(kUtils);

	std::istringstream iss(p_content);
	std::string current_line;

	while (std::getline(iss, current_line)) {
		handleLine(current_line);
	}
}

std::vector<std::string> INIParser::split(const std::string& p_line, const char p_delim) {
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

std::string INIParser::trim(const std::string& p_line)
{
	auto wsfront = std::find_if_not(p_line.begin(), p_line.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(p_line.rbegin(), p_line.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

void INIParser::handleLine(const std::string& p_line) {
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

}
}

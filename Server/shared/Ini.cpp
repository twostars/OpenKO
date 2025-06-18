#include "stdafx.h"
#include "Ini.h"
#include <iostream>
#include <fstream>
#include "string_utilities.h"

#define	INI_SECTION_START	'['
#define	INI_SECTION_END		']'
#define	INI_KEY_SEPARATOR	'='
#define	INI_NEWLINE			"\n"

constexpr int INI_BUFFER = 512;

CIni::CIni(
	std::string_view szPath)
{
	m_szPath = szPath;

	Load(szPath);
}

bool CIni::Load()
{
	return Load(
		m_szPath);
}

bool CIni::Load(
	std::string_view szPath)
{
	m_szPath = szPath;

	std::ifstream file(szPath.data());
	if (!file)
	{
		TRACE("Warning: %s does not exist, will use configured defaults.\n", szPath.data());
		return false;
	}

	std::string currentSection;

	// If an invalid section is hit
	// Ensure that we don't place key/value pairs
	// from the invalid section into the previously loaded section.
	bool bSkipNextSection = false;
	while (!file.eof())
	{
		std::string line;
		getline(file, line);

		rtrim(line);
		if (line.empty())
			continue;

		// Check for value strings first
		// It's faster than checking for a section
		// at the expense of of not being able to use '=' in section names.
		// As this is uncommon behaviour, this is a suitable trade-off.
		size_t keySeparatorPos = line.find(INI_KEY_SEPARATOR);
		if (keySeparatorPos != std::string::npos)
		{
			if (bSkipNextSection)
				continue;

			std::string key = line.substr(0, keySeparatorPos);
			std::string value = line.substr(keySeparatorPos + 1);

			// Clean up key/value to allow for 'key = value'
			rtrim(key);   /* remove trailing whitespace from keys */
			ltrim(value); /* remove preleading whitespace from values */

			auto itr = m_configMap.find(currentSection);
			if (itr == m_configMap.end())
			{
				m_configMap.insert(
					std::make_pair(currentSection, std::move(ConfigEntryMap())));
				itr = m_configMap.find(currentSection);
			}

			itr->second[key] = value;
			continue;
		}

		// Not a value, so assume it's a section
		size_t sectionStart = line.find_first_of(INI_SECTION_START),
			sectionEnd = line.find_last_of(INI_SECTION_END);

		if (sectionStart == std::string::npos
			|| sectionEnd == std::string::npos
			|| sectionStart > sectionEnd)
		{
			/* invalid section */
			bSkipNextSection = true;
			continue;
		}

		currentSection = line.substr(sectionStart + 1, sectionEnd - 1);
		bSkipNextSection = false;
	}

	file.close();
	return true;
}

void CIni::Save()
{
	Save(m_szPath);
}

void CIni::Save(
	std::string_view szPath)
{
	FILE* fp = fopen(szPath.data(), "w");
	if (fp == nullptr)
		return;

	for (const auto& [sectionName, keyValuePairs] : m_configMap)
	{
		// Start the section
		fprintf(fp, "[%s]" INI_NEWLINE, sectionName.c_str());

		// Now list out all the key/value pairs
		for (const auto& [key, value] : keyValuePairs)
			fprintf(fp, "%s=%s" INI_NEWLINE, key.c_str(), value.c_str());

		// Use a trailing newline to finish the section, to make it easier to read
		fprintf(fp, INI_NEWLINE);
	}

	fclose(fp);
}

int CIni::GetInt(
	std::string_view szAppName,
	std::string_view szKeyName,
	const int nDefault)
{
	auto sectionItr = m_configMap.find(szAppName.data());
	if (sectionItr != m_configMap.end())
	{
		auto keyItr = sectionItr->second.find(szKeyName.data());
		if (keyItr != sectionItr->second.end())
			return atoi(keyItr->second.c_str());
	}

	SetInt(szAppName, szKeyName, nDefault);
	return nDefault;
}

bool CIni::GetBool(
	std::string_view szAppName,
	std::string_view szKeyName,
	const bool bDefault)
{
	return GetInt(szAppName, szKeyName, bDefault) == 1;
}

std::string CIni::GetString(
	std::string_view szAppName,
	std::string_view szKeyName,
	std::string_view szDefault,
	bool bAllowEmptyStrings /*= true*/)
{
	auto sectionItr = m_configMap.find(szAppName.data());
	if (sectionItr != m_configMap.end())
	{
		auto keyItr = sectionItr->second.find(szKeyName.data());
		if (keyItr != sectionItr->second.end())
			return keyItr->second;
	}

	SetString(szAppName, szKeyName, szDefault);
	return szDefault.data();
}

int CIni::SetInt(
	std::string_view szAppName,
	std::string_view szKeyName,
	const int nDefault)
{
	char tmpDefault[INI_BUFFER + 1] = {};
	snprintf(tmpDefault, sizeof(tmpDefault), "%d", nDefault);
	return SetString(szAppName, szKeyName, tmpDefault);
}

int CIni::SetString(
	std::string_view szAppName,
	std::string_view szKeyName,
	std::string_view szDefault)
{
	auto itr = m_configMap.find(szAppName.data());
	if (itr == m_configMap.end())
	{
		auto ret = m_configMap.insert(
			std::make_pair(szAppName.data(), std::move(ConfigEntryMap())));
		if (!ret.second)
			return 0;

		itr = ret.first;
	}

	itr->second[szKeyName.data()] = szDefault.data();
	return 1;
}

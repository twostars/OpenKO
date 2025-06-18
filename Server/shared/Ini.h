#pragma once

#include <map>
#include <string_view>
#include <string>

class CIni
{
protected:
	std::string m_szPath;

	// Defines key/value pairs within sections
	using ConfigEntryMap = std::map<std::string, std::string>;

	// Defines the sections containing the key/value pairs
	using ConfigMap = std::map<std::string, ConfigEntryMap>;

	ConfigMap m_configMap;

public:
	CIni() = default;
	CIni(std::string_view szPath);

	bool Load();
	bool Load(std::string_view szPath);

	void Save();
	void Save(std::string_view szPath);

	int GetInt(std::string_view szAppName, std::string_view szKeyName, const int nDefault);
	bool GetBool(std::string_view szAppName, std::string_view szKeyName, const bool bDefault);
	std::string GetString(std::string_view szAppName, std::string_view szKeyName, std::string_view szDefault, bool bAllowEmptyStrings = true);
	int SetInt(std::string_view szAppName, std::string_view szKeyName, const int nDefault);
	int SetString(std::string_view szAppName, std::string_view szKeyName, std::string_view szDefault);
};

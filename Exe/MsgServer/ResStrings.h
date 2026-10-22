// CResStrings - ORIGINAL string-resource loader.
//
// The ORIGINAL server loads the client string table at startup through the
// string manager (see Tools/ServerLoader/ConfigManager.cpp: [Language]
// StringFile = ini\En_Res.ini). Modules resolve keys like
// "STR_TASK_DETAIL_NUM_MAX" (TaskDetail.dll) through that manager before
// sending them as system messages. This port loads the same ORIGINAL
// En_Res.ini (shipped at data/En_Res.ini) key=value pairs.
#pragma once
#include <map>
#include <string>

class CResStrings {
public:
    static CResStrings& Instance();

    // Loads key=value lines from the ORIGINAL En_Res.ini ("key" -> text).
    // ';'-prefixed lines and comments are skipped. Missing file = empty map.
    void LoadFromFile(const std::string& strPath);

    // ORIGINAL theInstance()->GetString(key): returns the text for the key,
    // or an empty string when the key is absent (the ORIGINAL send then
    // fires with an empty message).
    std::string Get(const std::string& strKey) const;

private:
    CResStrings() = default;
    std::map<std::string, std::string> m_strings;
};

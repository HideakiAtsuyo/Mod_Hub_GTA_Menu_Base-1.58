#include "stdafx.h"
#include "YTDLoader.h"
#include "SignatureScanner.h"
namespace Mod_Hub_Base
{
	YTDLoader::YTDLoader() : m_RegFile(nullptr), m_RetInt(-1)
	{
	}


	YTDLoader::~YTDLoader()
		= default;

	void YTDLoader::init()
	{
		m_RegFile = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9"_Scan.as<decltype(m_RegFile)>();
	}

	std::uint32_t YTDLoader::loadYtd(const std::string& path, const std::string& file)
	{
		if (std::ifstream(path))
		{
			m_RegFile(&m_RetInt, path.c_str(), true, file.c_str(), false);
			Log::Msg("file registered %s; ID: %i", path.c_str(), m_RetInt);
			Log::Msg("Loaded <!> Textures");
			return 0;
		}
	}
}

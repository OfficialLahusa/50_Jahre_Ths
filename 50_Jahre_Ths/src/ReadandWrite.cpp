#include "ReadandWrite.hpp"

namespace sse
{
	void ReadandWrite::Write(std::string toWrite, std::string Filepath, bool override)
	{
		std::string ContentBefore = Read(Filepath);
		std::ofstream File;
		File.open(Filepath);
		if (override)
		{
			File << toWrite;
		}
		else
		{			
			File <<  ContentBefore + toWrite;
		}
		File.close();
	}

	std::string ReadandWrite::Read(std::string Filepath)
	{
		std::string m_Output;
		std::ifstream File;
		File.open(Filepath);
		std::getline(File, m_Output);
		File.close();

		return std::string(m_Output);
	}
}
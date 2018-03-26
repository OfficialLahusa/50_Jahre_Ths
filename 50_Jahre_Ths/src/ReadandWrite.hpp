#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

namespace sse
{
	class ReadandWrite
	{
	public:

		void Write(std::string toWrite, std::string Filepath, bool override);
		std::string Read(std::string Filepath);

	private:

	};
}



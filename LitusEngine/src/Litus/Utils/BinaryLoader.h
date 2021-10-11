#pragma once
#include <string>
#include <fstream>

namespace LT {
	class BinaryLoader
	{
	public:
		template<typename T>
		static void WriteBinary(std::string path, T data[], size_t lenght)
		{
			size_t size = lenght;
			std::cout << size;
			std::ofstream binaryIo;
			binaryIo.open(path, std::ios::binary);
			if (binaryIo.is_open())
			{
				binaryIo.write((char*)&size, sizeof(size_t));
				binaryIo.write((char*)data, size * sizeof(*data));
				binaryIo.close();
			}
			else
				std::cout << "Error writing bin file..." << std::endl;

		}
		template<typename T>
		static void ReadBinary(std::string path, std::vector<T>& writeTo)
		{
			size_t size = 0;
			std::ifstream binaryIo;
			binaryIo.open(path, std::ios::binary);
			if (binaryIo.is_open())
			{
				binaryIo.read((char*)&size, sizeof(size_t));
				writeTo.resize(size);
				binaryIo.read((char*)writeTo.data(), size * sizeof(T));
				binaryIo.close();

			}
			else
				std::cout << "Error writing bin file..." << std::endl;
		}

	};
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "BinaryLoader.h"


void getBufferPaths(int argc, char* argv[], std::string& vertexPath, std::string& indexPath)
{
	std::string plyPath(argv[1]);

	auto lastSlash = plyPath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = plyPath.find('.');
	auto count = lastDot == std::string::npos ? plyPath.size() - lastSlash : lastDot - lastSlash;
	std::string name = plyPath.substr(lastSlash, count);
	 
	if (argc == 2)
	{
		std::string folderPath = plyPath.substr(0, lastSlash);
		vertexPath = folderPath + name + "Vertex.bin";
		indexPath = folderPath + name + "Index.bin";
	}
}

void getBuffers(const std::string& path, std::vector<float>& VertexBuffer, std::vector<int>& IndexBuffer)
{
	std::ifstream plyFile;
	plyFile.open(path);
	size_t propCount = 0;
	size_t vertexCount = 0;
	size_t faceCount = 0;
	if (!plyFile.is_open())
	{
		std::cerr << "Could not read file!" << std::endl;
		return;
	}
	bool header = true;
	std::string line;
	while (std::getline(plyFile, line))
	{
		std::stringstream keystream(line);
		std::string flag;
		keystream >> flag;

		if (line == "end_header")
			break;
		else if (flag == "element")
		{
			std::string type;
			keystream >> type;
			if (type == "vertex")
				keystream >> vertexCount;
			else if (type == "face")
				keystream >> faceCount;
		}
		else if (flag == "property")
		{
			std::string type;
			keystream >> type;
			if (type == "float")
				propCount++;
		}
	}


	VertexBuffer.resize(propCount * vertexCount);
	IndexBuffer.resize(3 * faceCount);

	for (size_t i = 0; i < VertexBuffer.size(); i += propCount)
	{
		std::getline(plyFile, line);
		std::stringstream keystream(line);
		for (size_t vi = 0; vi < propCount; vi++)
			keystream >> VertexBuffer[i + vi];
	}
	for (size_t i = 0; i < IndexBuffer.size(); i += 3)
	{
		std::getline(plyFile, line);
		std::stringstream keystream(line);
		int preData;
		keystream >> preData >> IndexBuffer[i] >> IndexBuffer[i + 1] >> IndexBuffer[i + 2];
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "To few arguments passed";
		return 1;
	}
	else if (argc > 3)
	{
		std::cerr << "To many arguments passed";
		return 2;
	}
	for (size_t i = 0; i < argc; i++)
	{
		std::cout << *(argv + i) << std::endl;
	}
	std::string vertexPath;
	std::string indexPath;
	std::string plyPath(argv[1]);
	std::vector<float> vertexB;
	std::vector<int> indexB;
	getBufferPaths(argc, argv, vertexPath, indexPath);
	getBuffers(plyPath, vertexB, indexB);

	LT::BinaryLoader::WriteBinary(vertexPath, vertexB.data(), vertexB.size());
	LT::BinaryLoader::WriteBinary(indexPath, indexB.data(), indexB.size());
	std::cin.get();
}
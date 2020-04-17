#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <map>
#include <vector>
namespace Fried
{
	class BinaryReaderWriter
	{
	public:
		BinaryReaderWriter() = default;
		// reading 
		template <typename T>
		void Read(T& variable, std::ifstream& input);
		template <typename T>
		void Read(std::vector<T>& vector, std::ifstream& input);
		template <typename T, typename V>
		void Read(std::map<T, V>& map, std::ifstream& input);
		void Read(std::string& variable, std::ifstream& input);
		// writing 
		template <typename T>
		void Write(const T& variable, std::ofstream& ofstream);
		template <typename T>
		void Write(const std::vector<T>& vector, std::ofstream& ofstream);
		template <typename T, typename V>
		void Write(const std::map<T, V>& map, std::ofstream& ofstream);
		void Write(const std::string& variable, std::ofstream& ofstream);
	};
}
using namespace Fried;
template <typename T>
inline void BinaryReaderWriter::Read(T& variable, std::ifstream& input)
{
	if (input.is_open())
	{
		input.read((char*)&variable, sizeof(T));
	}
}

template<typename T>
inline void BinaryReaderWriter::Read(std::vector<T>& vector, std::ifstream& input)
{
	if (input.is_open())
	{
		size_t vectorSize{};
		Read(vectorSize, input);
		vector.reserve(vectorSize);
		for (size_t i = 0; i < vectorSize; i++)
		{
			T var;
			Read(var, input);
			vector.push_back(var);
		}
	}
}

template <typename T, typename V>
inline void BinaryReaderWriter::Read(std::map<T, V>& map, std::ifstream& input)
{
	if (input.is_open())
	{
		size_t mapSize{};
		Read(mapSize, input);
		size_t counter{};
		while (counter != mapSize)
		{
			++counter;
			T fist;
			Read(fist, input);
			V second;
			Read(second, input);
			map.emplace(fist, second);
		}
	}
}

inline void BinaryReaderWriter::Read(std::string& variable, std::ifstream& input)
{
	if (input.is_open())
	{
		size_t stringBuffer{};
		char* cString{ nullptr };
		input.read((char*)&stringBuffer, sizeof(size_t));
		cString = new char[stringBuffer] {};
		input.read(cString, stringBuffer);
		for (size_t i = 0; i < stringBuffer; i++)
		{
			/*if (cString[i] == '\0')
			{
				break;
			}*/
			variable += cString[i];
		}
		delete[] cString;
	}
}

template <typename T>
inline void BinaryReaderWriter::Write(const T& variable, std::ofstream& ofstream)
{
	
	if (ofstream.is_open())
	{
		ofstream.write((char*)&variable, sizeof(T));
	}
}

template<typename T>
inline void BinaryReaderWriter::Write(const std::vector<T>& vector, std::ofstream& ofstream)
{
	if (ofstream.is_open())
	{
		size_t vectorSize{ vector.size() };
		Write(vectorSize, ofstream);
		for (size_t i = 0; i < vectorSize; i++)
		{
			Write(vector[i], ofstream);
		}
	}
}

template <typename T, typename V>
inline void BinaryReaderWriter::Write(const std::map<T, V>& map, std::ofstream& ofstream)
{
	if (ofstream.is_open())
	{
		size_t mapSize{ map.size() };
		Write(mapSize, ofstream);
		for (const std::pair<T, V>& pair : map)
		{
			Write(pair.first, ofstream);
			Write(pair.second, ofstream);
		}
	}
}

inline void BinaryReaderWriter::Write(const std::string& variable, std::ofstream& ofstream)
{
	if (ofstream.is_open())
	{
		size_t stringBuffer{ variable.size() };
		ofstream.write((const char*)&stringBuffer, sizeof(size_t));
		ofstream.write( variable.c_str(), stringBuffer);
	}
}
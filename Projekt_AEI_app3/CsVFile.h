#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "File_Error.h"
#include "Point.h"

template <typename T>
static uint64_t get_serialised_size(const T src, std::vector<std::string>(*serialiser)(T))
{
	return get_serialised_size(src, serialiser, ',', '\n');
}

template <typename T>
static uint64_t get_serialised_size(const T src, std::vector<std::string>(*serialiser)(T), const char separator, const char newline_char)
{
	std::vector<std::string> source_properties = serialiser(src);
	std::string serialised_source;

	for (const std::string& property : source_properties)
	{
		serialised_source.append(property);
		serialised_source.push_back(separator);
	}
	serialised_source.push_back(newline_char);

	return serialised_source.size();
}

static std::vector<std::string> point_serialiser(Point p)
{
	std::vector<std::string> properties;
	properties.resize(3);

	properties[0] = std::to_string(p.x);
	properties[1] = std::to_string(p.y);
	properties[2] = std::to_string(p.z);

	return properties;
};

static Point point_deserialiser(std::vector<std::string>& properties)
{
	Point p;

	p.x = std::stod(properties[0]);
	p.y = std::stod(properties[1]);
	p.z = std::stod(properties[2]);

	return p;
};

static uint64_t serialised_point_size = get_serialised_size<Point>(Point(0, 0, 0), point_serialiser);

class CsVFile
{
private:
	std::fstream file_stream_;
	const char* file_name_;
	std::fstream::openmode file_open_mode_;
	uint64_t file_size_;

	template <typename T>
	FileError read_offset(T* dest, const uint64_t count, const uint64_t offset, const uint64_t serialised_size, T(*deserialiser)(std::vector<std::string>&))
	{
		FileError error = ACCESS_DENIED;
		if ((file_open_mode_ & std::ios::in) != std::ios::in) return error;

		const uint64_t start_offset = offset * (serialised_size + 1);
		if (file_size_ < start_offset)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		const uint64_t data_size = count * serialised_size;
		if (file_size_ - start_offset < data_size)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		file_stream_.seekg(start_offset, std::fstream::beg);

		std::vector<char> serialised_data_buffer;
		serialised_data_buffer.resize(serialised_size + 1);
		for (uint64_t i = 0; i < count; ++i)
		{
			char* serialised_data = serialised_data_buffer.data();
			file_stream_.read(serialised_data, serialised_size);

			serialised_data_buffer[serialised_size] = '\0'; // sanitise input

			std::string data = std::string(serialised_data);
			
			std::vector<std::string> serialised_properties = Split(data, ',');
			T instance = deserialiser(serialised_properties);
			dest[i] = instance;
		}
		error = SUCCESS;

		return error;
	}
	
	template <typename T>
	FileError write_offset(const T* src, const uint64_t count, const uint64_t offset, const uint64_t serialised_size, std::vector<std::string>(*serialiser)(T), const char separator, const char newline)
	{
		FileError error = ACCESS_DENIED;
		if ((file_open_mode_ & std::ios::out) != std::ios::out) return error;

		const uint64_t start_offset = offset * serialised_size;
		if (file_size_ < start_offset)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		file_stream_.seekg(start_offset, std::fstream::beg);
		
		for (uint64_t i = 0; i < count; ++i)
		{
			std::vector<std::string> source_properties = serialiser(src[i]);
			std::string serialised_source;

			for (const std::string& property : source_properties)
			{
				serialised_source.append(property);
				serialised_source.push_back(separator);
			}
			serialised_source.push_back(newline);

			const uint64_t data_size = serialised_source.length();
			const char* serialised_data = serialised_source.c_str();

			file_stream_.write(serialised_data, data_size);
			file_size_ += data_size;
		}
		error = SUCCESS;

		return error;
	}
	
	static std::vector<std::string> Split(const std::string& src, const char separator)
	{
		std::vector<std::string> results;
		std::string current_split;

		for (char c : src)
		{
			if (c != separator)
			{
				current_split.push_back(c);
			}
			else
			{
				results.push_back(current_split);
				current_split.clear();
			}
		}

		return results;
	}

	FileError WritePoint(const Point src)
	{
		file_stream_.seekg(0, std::fstream::beg);
		file_stream_.seekg(0, std::fstream::end);
		const uint64_t offset = file_stream_.tellg();
		file_stream_.seekg(0, std::fstream::beg);
		
		return write_offset<Point>(&src, 1, offset, serialised_point_size, point_serialiser, ',', '\n');
	}

public:
	CsVFile(const char* file_name, const std::string& file_mode)
	{
		file_name_ = file_name;
		file_open_mode_ = std::ios::in;

		if (file_mode.find("r") != std::string::npos) file_open_mode_ |= std::ios::in;
		if (file_mode.find("w") != std::string::npos) file_open_mode_ |= std::ios::out;
		if (file_mode.find("a") != std::string::npos) file_open_mode_ |= std::ios::app;
		if (file_mode.find("t") != std::string::npos) file_open_mode_ |= std::ios::trunc;
		if (file_mode.find("e") != std::string::npos) file_open_mode_ |= std::ios::ate;

		file_stream_ = std::fstream(file_name_, file_open_mode_);
		file_stream_.seekg(0, std::fstream::end);
		file_size_ = file_stream_.tellg();
		file_stream_.seekg(0, std::fstream::beg);
	}

	~CsVFile()
	{
		file_stream_.close();
	}

	FileError Read(Point* dest, const uint64_t idx)
	{
		return read_offset<Point>(dest, 1, idx, serialised_point_size, point_deserialiser);
	}

	FileError Read(std::vector<Point>& dest)
	{
		const uint64_t total_points = file_size_ / serialised_point_size;

		dest.resize(total_points);
		return read_offset<Point>(dest.data(), total_points, 0, serialised_point_size, point_deserialiser);
	}

	FileError Write(const std::vector<Point>& points)
	{
		return write_offset<Point>(points.data(), points.size(), 0, serialised_point_size, point_serialiser, ',', '\n');
	}
};

/*Stworzyć klasę CsvFile, która zawiera następujące pola i metody: 
Strumień pliku 
● Nazwa pliku 
● Rozmiar pliku 
● Tryb otwarcia
● Konstruktor przyjmujący ścieżkę pliku jako std::string i tryb otwarcia pliku jako std::string. 
Na podstawie argumentów konstruktora, zostaje otwarty plik o podanej nazwie, w podanym trybie. Konstruktor oblicza rozmiar pliku. 
● Destruktor, który zamyka plik. 
● Metoda Write(const std::vector<Point>&) - zapisuje wektor punktów do pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(std::vector<Point>&) - wczytuje do wektora punkty z pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(Point&, int) - wczytuje do struktury Point punkt z pliku o podanym indeksie. Zwraca odpowiedni kod błędu FileError.  
● Prywatne metody pomocnicze:  
	○ WriteLine(Point) - zapisuje jeden punkt do pliku 
	○ Split(std::string, char) - rozdziela łańcuchy znaków zadanym separatorem (typu char).
*/
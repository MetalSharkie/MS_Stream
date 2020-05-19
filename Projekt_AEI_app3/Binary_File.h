#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "File_Error.h"


class BinaryFile
{
private:
	std::fstream file_stream_;
	const char* file_name_;
	std::fstream::openmode file_open_mode_;
	uint64_t file_size_;

	template <typename T>
	FileError read_offset(T* dest, const uint64_t count, const uint64_t offset)
	{
		FileError error = ACCESS_DENIED;
		if ((file_open_mode_ & std::ios::in) != std::ios::in) return error;

		const uint64_t binary_offset = offset * sizeof(T);

		if (file_size_ < binary_offset)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		const uint64_t data_size = count * sizeof(T);
		if (file_size_ - binary_offset < data_size)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		file_stream_.seekg(binary_offset, std::fstream::beg);

		char* binary_data_buffer = static_cast<char*>(malloc(sizeof(T)));
		for (uint64_t i = 0; i < count; i++)
		{
			file_stream_.read(binary_data_buffer, sizeof(T));

			dest[i] = *reinterpret_cast<T*>(binary_data_buffer);
		}
		free(binary_data_buffer);
		
		error = SUCCESS;

		return error;
	}
	
	template <typename T>
	FileError write_offset(T* src, const uint64_t count, const uint64_t offset)
	{
		FileError error = ACCESS_DENIED;
		if ((file_open_mode_ & std::ios::out) != std::ios::out) return error;

		const uint64_t binary_offset = offset * sizeof(T);

		if (file_size_ < binary_offset)
		{
			error = OUT_OF_BOUNDS;
			return error;
		}

		const uint64_t data_size = count * sizeof(T);

		file_stream_.seekg(binary_offset, std::fstream::beg);

		if ((file_open_mode_ & std::ios::app) != std::ios::app)
		{
			if (file_size_ - binary_offset < data_size)
			{
				error = OUT_OF_BOUNDS;
				return error;
			}

			for (uint64_t i = 0; i < count; i++)
			{
				const char* binary_data_buffer = reinterpret_cast<const char*>(&src[i]);
				file_stream_.write(binary_data_buffer, sizeof(T));
				file_size_ += sizeof(T);
			}

			error = SUCCESS;
		}
		else
		{
			for (uint64_t i = 0; i < count; i++)
			{
				const char* binary_data_buffer = reinterpret_cast<const char*>(&src[i]);
				file_stream_.write(binary_data_buffer, sizeof(T));
				file_size_ += sizeof(T);
			}
			
			error = SUCCESS;
		}

		return error;
	}

public:
	BinaryFile(const char* file_name, const std::string& file_mode)
	{
		file_name_ = file_name;
		file_open_mode_ = std::ios::in | std::ios::binary;

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

	~BinaryFile()
	{
		file_stream_.close();
	}

	template <typename T>
	uint64_t get_size() const
	{
		return file_size_ / sizeof(T);
	}

	FileError Read(Point* dest, const uint64_t idx)
	{
		return read_offset(dest, 1, idx);
	}

	FileError Read(std::vector<Point>& dest)
	{
		const uint64_t total_points = file_size_ / sizeof(Point);

		dest.resize(total_points);
		return read_offset(dest.data(), total_points, 0);
	}

	FileError Write(const std::vector<Point>& src)
	{
		return write_offset(src.data(), src.size(), 0);
	}
};

/*
Stworzyć klasę BinaryFile, która zawiera następujące pola i metody: 
● Strumień pliku
● Nazwa pliku 
● Rozmiar pliku 
● Tryb otwarcia 
● Konstruktor przyjmujący ścieżkę pliku jako std::string i tryb otwarcia pliku jako std::string. 
Na podstawie argumentów konstruktora, zostaje otwarty plik o podanej nazwie, w podanym trybie. 
Konstruktor oblicza rozmiar pliku. ● Destruktor, który zamyka plik. 
● Metoda Write(const std::vector<Point>&) - zapisuje wektor punktów do pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(std::vector<Point>&) - wczytuje do wektora punkty z pliku. Zwraca odpowiedni kod błędu FileError. 
● Metoda Read(Point&, int) - wczytuje do struktury Point punkt z pliku o podanym indeksie. Zwraca odpowiedni kod błędu FileError. 
Metoda musi pozwalać na odczyt tylko jednego punktu, nie może odczytywać całego pliku celem znalezienia wybranego punktu. 
Należy unikać wykorzystania pętli for do wczytywania i zapisywania punktów.
*/
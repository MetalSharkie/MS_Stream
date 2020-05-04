
#include <iostream>
#include <vector>

#include "Binary_File.h"
#include "CsVFile.h"

const char* point_file_path = R"(binary_test.txt)";
const char* csv_file_path = R"(csv_test.csv)";

int main()
{
	std::cout << "\n\nHi Babe!\n";

	// binary_test.txt manipulation
	BinaryFile binary(point_file_path, "rwa");

	const uint32_t point_count = 10;
	
	std::vector<Point> binary_points;
	binary_points.resize(point_count);
	
	for (uint32_t i = 0; i < point_count; i++)
	{
		binary_points[i] = Point(i, i, i);
	}

	const FileError binary_point_write_error = binary.Write(binary_points);
	if (binary_point_write_error == SUCCESS)
	{
		std::cout << "Wrote " << point_count << " points to " << point_file_path << std::endl;

		std::vector<Point> new_binary_points;
		new_binary_points.resize(point_count);
		
		const FileError binary_point_read_error = binary.Read(new_binary_points);

		if (binary_point_read_error == SUCCESS)
		{
			for (const Point p : new_binary_points)
			{
				char point_str_buff[SERIALISED_POINT_BUFF_SIZE];

				p.serialise(point_str_buff);

				std::cout << "Read point: " << point_str_buff << std::endl;
			}
		}
		else
		{
			std::cout << "Read Error: " << static_cast<uint32_t>(binary_point_read_error) << std::endl;
		}
	}
	else
	{
		std::cout << "Write Error: " << static_cast<uint32_t>(binary_point_write_error) << std::endl;
	}

	Point individual_binary_point;
	const FileError individual_binary_point_read_error = binary.Read(&individual_binary_point, 3);
	if (individual_binary_point_read_error == SUCCESS)
	{
		char point_str_buff[SERIALISED_POINT_BUFF_SIZE];

		individual_binary_point.serialise(point_str_buff);

		std::cout << "Read indexed point: " << point_str_buff << std::endl;
	}
	else
	{
		std::cout << "Write Error: " << static_cast<uint32_t>(individual_binary_point_read_error) << std::endl;
	}
	
	// csv_test.csv manipulation
	CsVFile csv(csv_file_path, "rwa");

	std::vector<Point> csv_points;
	csv_points.resize(point_count);

	for (uint32_t i = 0; i < point_count; i++)
	{
		csv_points[i] = Point(i, i, i);
	}
	
	const FileError point_csv_write_error = csv.Write(csv_points);
	if (point_csv_write_error == SUCCESS)
	{
		std::cout << "Wrote " << point_count << " points to " << csv_file_path << std::endl;

		std::vector<Point> new_csv_points;
		new_csv_points.resize(point_count);

		const FileError point_csv_read_error = csv.Read(new_csv_points);

		if (point_csv_read_error == SUCCESS)
		{
			for (const Point p : new_csv_points)
			{
				char point_str_buff[SERIALISED_POINT_BUFF_SIZE];

				p.serialise(point_str_buff);

				std::cout << "Read point: " << point_str_buff << std::endl;
			}
		}
		else
		{
			std::cout << "Read Error: " << static_cast<uint32_t>(point_csv_read_error) << std::endl;
		}
	}
	else
	{
		std::cout << "Write Error: " << static_cast<uint32_t>(point_csv_write_error) << std::endl;
	}

	Point individual_csv_point;
	const FileError individual_csv_point_read_error = csv.Read(&individual_csv_point, 3);
	if (individual_binary_point_read_error == SUCCESS)
	{
		char point_str_buff[SERIALISED_POINT_BUFF_SIZE];

		individual_csv_point.serialise(point_str_buff);

		std::cout << "Read indexed point: " << point_str_buff << std::endl;
	}
	else
	{
		std::cout << "Write Error: " << static_cast<uint32_t>(individual_csv_point_read_error) << std::endl;
	}
}

/*
Dwie klasy BinaryFile i CsvFile, których deklaracje znajduj¹ siê w plikach nag³ówkowych, a implementacja w plikach Ÿród³owych. 
Obie klasy musz¹ pozwalaæ na zapis wektorów punktów do pliku i odczyt wektorów punktów z pliku. 
Pozwalaj¹ tak¿e na wczytanie jednego punktu z pliku o podanym indeksie. Obs³uguj¹ sytuacje wyj¹tkowe zwracaj¹c odpowiednie kody b³êdów.
*/
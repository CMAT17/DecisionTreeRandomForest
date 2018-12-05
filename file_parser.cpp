#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <istream>
#include <utility>

#include "datasetitem.h"
#include "file_parser.h"

/**
 * Function parsing LibSVM-style textfiles
 */
std::vector<DataSetItem> file_parser(std::string filename)
{
	std::ifstream data_file;
	data_file.open(filename);
 	std::vector<DataSetItem> dataset_record;

	if(data_file.is_open())
	{
		string line;

		while(std::getline(data_file, line))
		{
			std::istringstream iss(line);
			std::vector<std::string> line_record = ( (std::istream_iterator(iss)) ,
													  std::istream_iterator());
			int label=(std::stoi(line_record[0]));
			std::vector<std::map<int, int> > dim_maps;
			for(auto it = std::next(line_record.begin()), it != line_record.end(), ++it)
			{
				std::string key, val;
				std::map<int, int> temp;
				std::istringstream iss2(it);
				while(std::getline(std::getline(iss2,key,":") >> std::ws, val)){
					temp[std::stoi(key)] = std::stoi(val);
				}
				dim_maps.push_back(temp);
			}
			DataSetItem new_datasetitem(label, dim_maps);
			dataset_record.push_back(DataSetItem);
		}
	}
	return dataset_record;
}
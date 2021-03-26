#include "Exercise.h"

void ShareManager::AddItem(const InputInfo& input)
{
	if (result_map_.count(input.symbol_))
	{
		auto item = result_map_.find(input.symbol_);
		MiddleInfo* info = item->second;
		info->max_time_gap_ = max(info->max_time_gap_, input.time_ - info->last_time_);
		info->last_time_ = input.time_;
		info->total_qty_ += input.qty_;
		info->total_amt_ += input.qty_ * input.price_;
		info->max_price_ = max(info->max_price_, input.price_);
	}
	else
	{
		MiddleInfo* info = new MiddleInfo();
		info->last_time_ = input.time_;
		info->max_time_gap_ = 0;
		info->total_qty_ = input.qty_;
		info->total_amt_ = input.qty_ * input.price_;
		info->max_price_ = input.price_;
		result_map_[input.symbol_] = info;
	}
}

int main(int argc, char* argv[]) 
{
	if (argc != 3)
	{
		cerr << "入参个数有误" << endl;
	}
	string inputfilename(argv[1]);
	string outputfilename(argv[2]);

	ifstream inputfile(inputfilename, ios::in); //inputfilename
	ofstream outputfile(outputfilename, ios::out | ios::trunc); //outputfilename
	while (!inputfile.eof())
	{
		InputInfo share_info;
		string line;
		inputfile >> line;
		istringstream sin(line);

		string field;
		getline(sin, field, ',');
		share_info.time_ = atoi(field.c_str());

		getline(sin, field, ',');
		share_info.symbol_ = field;

		getline(sin, field, ',');
		share_info.qty_ = atoi(field.c_str());

		getline(sin, field, ',');
		share_info.price_ = atoi(field.c_str());

		ShareManager::Instance()->AddItem(share_info);
	}

	auto result_map = ShareManager::Instance()->GetResultMap();

	for (auto& item : result_map)
	{
		outputfile << item.first << ","
			<< item.second->max_time_gap_ << ","
			<< item.second->total_qty_ << ","
			<< item.second->total_amt_ / item.second->total_qty_ << ","
			<< item.second->max_price_ << endl;
	}
	inputfile.close();
	outputfile.close();
}
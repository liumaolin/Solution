#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <array>
using namespace std;

typedef uint32_t TimeStamp_def;
typedef std::string Symbol_def;
typedef uint32_t Quantity_def;
typedef uint32_t Price_def;
typedef uint64_t Amount_def;

struct InputInfo
{
	TimeStamp_def time_;
	Symbol_def symbol_;
	Quantity_def qty_;
	Price_def price_;
};

struct MiddleInfo
{
	TimeStamp_def last_time_;
	TimeStamp_def max_time_gap_;
	Quantity_def total_qty_;
	Amount_def total_amt_;
	Price_def max_price_;
};

class ShareManager
{
public:
	void AddItem(const InputInfo& input);
	std::map<Symbol_def, MiddleInfo*> GetResultMap()
	{
		return result_map_;
	}
	static ShareManager* Instance()
	{
		static ShareManager manager;
		return &manager;
	}
private:
	ShareManager() {}
	std::map<Symbol_def, MiddleInfo*> result_map_;
};
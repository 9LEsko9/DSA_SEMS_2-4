#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

bool natural_less(const std::string& a, const std::string& b);

void natural_merge_sort(std::vector<std::string>& arr);
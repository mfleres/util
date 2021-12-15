//
// Created by mfleres on 11/17/21.
//

#include "CsvData.h"

namespace util {
    std::string getNextCsvColumn(const std::string& row, size_t& start, char delimiter = '|') {
        std::string ret;
        size_t end = row.find(delimiter, start);
        if (start > row.length() || end < start)
            return ret;
        if (end == std::string::npos)
            end = row.length();
        ret = row.substr(start, end - start);
        start = end + 1;
        return ret;
    }//std::string getNextCsvColumn(const std::string& row, size_t& start, char delimiter = '|')

    CsvData::CsvData(const std::string& filepath, char delimiter) {
        std::ifstream file(filepath.c_str());
        std::string entry;
        size_t rowNum = 0;
        while ( std::getline(file, entry) ) {
            size_t columnCount = std::count(entry.begin(), entry.end(), delimiter) + 1;
            data_.emplace_back(std::vector<std::string>(columnCount));
            size_t start = 0;
            while ( start < entry.length() )
                data_[rowNum].push_back(getNextCsvColumn(entry, start));
            rowNum++;
        }
        file.close();
    }//CsvData::CsvData(const std::string& filepath, char delimiter)

    void CsvData::assignHeader(size_t rowNum) {
        if (rowNum >= data_.size())
            return;
        if (!header_.empty())
            data_.emplace_back(std::move(header_));
        header_ = std::move(data_[rowNum]);
        data_.erase(data_.begin() + static_cast<long long>(rowNum));
    }

    void CsvData::assignColumnInfo(size_t rowNum) {
        if (rowNum >= data_.size())
            return;
        if (!columnInfo_.empty())
            data_.emplace_back(std::move(columnInfo_));
        columnInfo_ = std::move(data_[rowNum]);
        data_.erase(data_.begin() + static_cast<long long>(rowNum));
    }

    std::string CsvData::get(size_t row, size_t column) const {
        if (row >= data_.size() || column >= data_[row].size())
            return "";
        return data_[row][column];
    } //T get(size_t row, size_t column, CsvType type = CsvType::String)

    const std::vector<std::string>& CsvData::operator[](size_t row) const {
        if (row >= data_.size()) {
            std::stringstream ss;
            ss << "CsvData::operator[](" << row << ") const";
            std::string error = "ERROR::" + ss.str() + ": Input out of range.";
#ifdef UTIL_CSVDATA_ALWAYSTHROW
            throw std::out_of_range(error);
#else
            if (data_.empty())
                    throw std::out_of_range(error);
                else {
                    std::cout << error << std::endl;
                    std::cout << "WARNING::" << ss.str() << ": Returning first row." << std::endl;
                    return data_[0];
                }
#endif
        } //if (row >= data_.size()) {
        else
            return data_[row];
    } //const std::vector<std::string>& operator[](size_t row) const
}
//
// Created by mfleres on 11/16/21.
//

#ifndef GRIDWORLD3D_CSVDATA_H
#define GRIDWORLD3D_CSVDATA_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define UTIL_CSVDATA_ALWAYSTHROW

namespace util {
    enum class CsvType {
        Int,
        Long,
        ULong,
        Float,
        Double,
        String
    };

    class CsvData {
    private:
        std::vector<std::string> header_;
        std::vector<std::string> columnInfo_;
        std::vector<std::vector<std::string>> data_;
    public:
        CsvData() = default;
        explicit CsvData(std::vector<std::vector<std::string>> data = std::vector<std::vector<std::string>>(),
                         std::vector<std::string> header = std::vector<std::string>(),
                         std::vector<std::string> columnInfo = std::vector<std::string>())
            : data_(std::move(data)), header_(std::move(header)), columnInfo_(std::move(columnInfo)) {
        }
        explicit CsvData(const std::string& file, char delimiter = '|');

        void assignHeader(size_t rowNum);
        void assignHeader(std::vector<std::string> header) { header_ = std::move(header); }
        void assignColumnInfo(size_t rowNum);
        void assignColumnInfo(std::vector<std::string> columnInfo) { columnInfo_ = std::move(columnInfo); }


        const std::vector<std::string>& header() const { return header_; }
        const std::vector<std::string>& columnInfo() const { return columnInfo_; }
        size_t count() { return data_.size(); }

//        template <class T>
//        T get(size_t row, size_t column, CsvType type = CsvType::String) const;
        std::string get(size_t row, size_t column) const; // { return get<std::string>(row,column,CsvType::String); }
        const std::vector<std::string>& operator[](size_t row) const;

        bool operator!() { return data_.empty(); }
    }; //class CsvData
} //namespace util

#endif //GRIDWORLD3D_CSVDATA_H

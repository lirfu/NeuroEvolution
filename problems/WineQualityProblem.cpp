//
// Created by lirfu on 13.05.18..
//

#include <fstream>
#include <data/DataUtils.h>
#include "WineQualityProblem.h"


WineQualityProblem::WineQualityProblem(std::string &filepath) {
    ifstream file;
    file.open(filepath);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            double *rowIn = new double[11];

            string buffer;
            uint index = 0;
            for (char c : line) {
                if (c == ';') {
                    rowIn[index++] = stod(buffer);
                    buffer = "";
                } else {
                    buffer += c;
                }
            }
            inputs_.push_back(new Matrix(1, 11, rowIn));
            outputs_.push_back(new Matrix(1, 1, {stod(buffer)}));
        }
        // Store data divided into train/validation sets
        dataset_.push_back(DataUtils::shuffleData(DataUtils::separateData<Matrix>(&inputs_, &outputs_, 0.7)));
    } else {
        throw runtime_error("Cannot open file!");
    }
}

WineQualityProblem::~WineQualityProblem() {
    for (Data *d : dataset_)
        delete (d);
}

uint WineQualityProblem::inputSize() {
    return 11;
}

uint WineQualityProblem::outputSize() {
    return 1;
}

string WineQualityProblem::toLabel(Matrix &matrix) {
    return std::to_string((uint) round(matrix.get(0, 0)));
}

#include <iostream>
#include <cmath>
#include <vector>
#include "headers/quantumComputer.h"

/// Function used to set values of QuantumComputer structure
quantum::QuantumComputer::QuantumComputer(int regSize, double probability[], int arrSize) {
    this->registerSize = regSize;
    this->baseVectorsCount = 0;
    this->isNormalize = false;
    this->isMeasured = false;

    validateArraySize(arrSize, regSize);

    for (int i = 0; i < arrSize; i++) {
        baseVector.push_back(probability[i]);
    }

    validateProbability();
    countNonZeroBaseVector();
}

/// Function used to count base vector elements,
/// where single element != 0
void quantum::QuantumComputer::countNonZeroBaseVector() {
    for (auto x: this->baseVector) {
        if ((double) x != 0.0) {
            this->baseVectorsCount++;
        }
    }
}

/// Function used to reset state of base vector.
/// First element of vector is set to 1, other elements are set to 0.
void quantum::QuantumComputer::resetState() {
    std::vector<double>::iterator it;
    for (it = this->baseVector.begin(); it < this->baseVector.end(); it++) {
        *it = 0.0;
    }
    this->baseVector.at(0) = 1;
}

/// Function used to show defined base vector
void quantum::QuantumComputer::viewProbability() {
    std::cout << "Vector with probabilities {";
    for (auto x: this->baseVector) {
        printf("[%.4f]", x);
    }
    std::cout << "}";
}

/// Helper function used to convert integer to binary
int integerToBinary(int num) {
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    return (num % 2) + 10 * integerToBinary(num / 2);
}

/// Function used to show qubit as math expression
/// eg. for qubit 0 - |0>
void quantum::QuantumComputer::viewQubitsInMathExpression() {
    if (!this->isNormalize) {
        std::cout << "Base Vector is not in normalize state. To view qubit you should normalize it before.  Use .normalize() function for that" << std::endl;
    }
    else {
        printf("\nQubit in expression: \n");
        int i = 0;
        for (auto x: this->baseVector) {
            if (x != 0) {
                int binary = integerToBinary(i);
//                    std::string binaryStringValue = std::to_string(binary);  TODO: Refactor printing of qubit in expression  for register(2) -> |00> not |0>
                if (x == 1.00) {
                    if (binary == 0) {
                        std::string tmp = "";
                        for (int j = 0; j < this->registerSize; j++) {
                            tmp += "0";
                        }
                        std::cout << "|" << tmp << ">";
                    }
                    else {
                        printf("|%d> ", binary);
                    }
                }
                else {
                    if (binary == 0) {
                        std::string tmp = "";
                        for (int j = 0; j < this->registerSize; j++) {
                            tmp += "0";
                        }
                        std::cout << "|" << tmp << ">";
                    }
                    else {
                        printf("%.4f |%d> ", x, binary);
                    }
                }
            }

            i++;
        }
        std::cout << std::endl;
    }
}

/// Function used to check register size and array size from input
void quantum::QuantumComputer::validateArraySize(int arrSize, int regSize) {
    if (regSize < 1) {
        printf("\n[ERROR] Register size cannot be less than 1");
        exit(1);
    }

    if (arrSize != pow(2, regSize)) {
        printf("\n[ERROR] Invalid Register arr with []Probability");
        exit(1);
    }
}

/// Function used to check probabilities of base vector
/// If sum of square probabilities is not equal 1 - error, vector should be normalized
void quantum::QuantumComputer::validateProbability() {
    double result = 0.0;
    for (auto x: this->baseVector) {
        result += pow(sqrt(fabs(x)), 2);
    }

    if (result != 1.0) {
        printf("\n[ERROR] Probability should be equal 1, normalize register function is executed...\n");
        viewProbability();
        normalizeRegister();
        resetState();
    }
    else {
        this->isNormalize = true;
    }
}

/// Function used to normalize probabilities of base vector(register)
void quantum::QuantumComputer::normalizeRegister() {
    double vectorLength = 0.0;

    for (auto x: this->baseVector) {
        vectorLength += pow(x, 2);
    }

    vectorLength = sqrt(vectorLength);
    std::vector<double>::iterator it;

    for (it = this->baseVector.begin(); it < this->baseVector.end(); it++) {
        *it = *it / vectorLength;
    }

    this->isNormalize = true;
    printf("\nRegister (vector) is normalized\n");
}

/// Function used to measure of base vector
// TODO:  DO IT
void quantum::QuantumComputer::QuantumComputer::measure() {
    if (this->isMeasured) {
        std::cout << "U cannot measure collapsed qubit" << std::endl;
        return;
    }
    std::cout << "[Here will be function to measure register!]" << std::endl;

    this->isMeasured = true;
}

/// Function used to get created base vector
std::vector<double> quantum::QuantumComputer::QuantumComputer::getBaseVector() {
    return baseVector;
}
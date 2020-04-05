#include <iostream>
#include <complex>
#include <ctime>
#include "lib/headers/numericMatrix.h"
#include "lib/headers/complexMatrix.h"
#include "lib/headers/quantumComputer.h"
#include "lib/headers/qubitOperation.h"
#include "lib/headers/quantumGate.h"

using namespace std;
using namespace quantum;

void runMatrixOperations() {
    //TODO: another implementation for generate random values
    srand(static_cast<unsigned int>(time(nullptr)));

    int dimension = rand() % 4 + 2;
    setNumericMatrixDimension(dimension);
    setComplexMatrixDimension(dimension);
    cout << "Rows: " << dimension << " " << "Columns: " << dimension << endl;

    int **original01Matrix = allocateNumericMatrix(dimension);
    generateRandomNumericMatrix(original01Matrix);
    cout << "Original 01 matrix: " << endl;
    printNumericMatrix(original01Matrix, dimension);

    int **transposed01Matrix = transposeNumericMatrix(original01Matrix);
    cout << "Transposed 01 matrix: " << endl;
    /*
     * Transposed matrix, that we revert columns and rows parameters in function call.
     * In this case it doesn't matter - columns and rows have the same value
     * It's important when matrix have different dimensions.
     */
    printNumericMatrix(transposed01Matrix, dimension);

    delete (original01Matrix);
    delete (transposed01Matrix);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    complex<double> **originalComplexMatrix = allocateComplexMatrix(dimension);
    generateRandomComplexMatrix(originalComplexMatrix);
    cout << "Original complex matrix: " << endl;
    printHermitianComplexMatrix(originalComplexMatrix, dimension);

    complex<double> **transposedComplexMatrix = transposeComplexMatrix(originalComplexMatrix);
    cout << "Transposed complex matrix: " << endl;
    printHermitianComplexMatrix(transposedComplexMatrix, dimension);

    complex<double> **conjugatedComplexMatrix = conjugateComplexMatrix(transposedComplexMatrix);
    cout << "Conjugated complex matrix: " << endl;
    printHermitianComplexMatrix(conjugatedComplexMatrix, dimension);

    delete (originalComplexMatrix);
    delete (conjugatedComplexMatrix);
}

double *generateAndNormalizeQubit(int numberOfQubits, double probabilities[]) {
    int arrSize = pow(2, numberOfQubits);
    struct QuantumComputer qc = QuantumComputer(numberOfQubits, probabilities, arrSize);

    qc.viewProbability();
    qc.normalizeRegister();
    qc.viewProbability();
    qc.viewQubitsInMathExpression();

    return getBaseVectorAsArray(qc.getBaseVector());
}

double *generateQubit(int numberOfQubits, double probabilities[]) {
    int arrSize = pow(2, numberOfQubits);
    struct QuantumComputer qc = QuantumComputer(numberOfQubits, probabilities, arrSize);

    qc.viewProbability();
    qc.viewQubitsInMathExpression();

    return getBaseVectorAsArray(qc.getBaseVector());
}

void testNotQuantumGate() {
    double probabilitiesOfQubit0[] = {1, 0};
    double probabilitiesOfQubit1[] = {0, 1};

    double *qubit0 = generateQubit(1, probabilitiesOfQubit0);
    cout << "Qubit 0 (1 0) before negation:" << endl;
    printQubit(qubit0, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit 0 (1 0) after negation:" << endl;
    printQubit(makeNotOnQubit(qubit0), ROWS_NUMBER_IN_SINGLE_QUBIT);

    double *qubit1 = generateQubit(1, probabilitiesOfQubit1);
    cout << "Qubit 1 (0 1) before negation:" << endl;
    printQubit(qubit1, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit 1 (0 1) after negation:" << endl;
    printQubit(makeNotOnQubit(qubit1), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testSqrtNotQuantumGate() {
    double probabilitiesOfQubit0[] = {1.0, 0.0};
    double *singleQubit = generateQubit(1, probabilitiesOfQubit0);

    cout << "Qubit before SQRT(NOT):" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit after SQRT(NOT):" << endl;
    printComplexQubit(makeSqrtNotOnQubit(singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testCnotQuantumGate() {
    double probabilitiesOfTwoQubits[] = {0.0, 0.0, 0.0, 1.0};
    double *twoQubits = generateQubit(2, probabilitiesOfTwoQubits);

    cout << "Qubit before CNOT:" << endl;
    printQubit(twoQubits, ROWS_NUMBER_IN_TWO_QUBITS);
    cout << "Qubit after CNOT:" << endl;
    printQubit(makeCnotOnQubit(twoQubits), ROWS_NUMBER_IN_TWO_QUBITS);
}

void testSwapQuantumGate() {
    double probabilitiesOfTwoQubits[] = {0.0, 1.0, 0.0, 0.0};
    double *twoQubits = generateQubit(2, probabilitiesOfTwoQubits);

    cout << "Qubit before SWAP:" << endl;
    printQubit(twoQubits, ROWS_NUMBER_IN_TWO_QUBITS);
    cout << "Qubit after SWAP:" << endl;
    printQubit(makeSwapOnQubit(twoQubits), ROWS_NUMBER_IN_TWO_QUBITS);
}

void testFredkinQuantumGate() {
    double probabilitiesOfThreeQubits[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
    double *threeQubits = generateQubit(3, probabilitiesOfThreeQubits);

    cout << "Qubit before FREDKIN:" << endl;
    printQubit(threeQubits, ROWS_NUMBER_IN_THREE_QUBITS);
    cout << "Qubit after FREDKIN:" << endl;
    printQubit(makeFredkinOnQubit(threeQubits), ROWS_NUMBER_IN_THREE_QUBITS);
}

void testToffoliQuantumGate() {
    double probabilitiesOfThreeQubits[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
    double *threeQubits = generateQubit(3, probabilitiesOfThreeQubits);

    cout << "Qubit before TOFFOLI:" << endl;
    printQubit(threeQubits, ROWS_NUMBER_IN_THREE_QUBITS);
    cout << "Qubit after TOFFOLI:" << endl;
    printQubit(makeToffoliOnQubit(threeQubits), ROWS_NUMBER_IN_THREE_QUBITS);
}

void testHadamardQuantumGate() {
    double probabilitiesOfTwoQubits[] = {1.0, 0.0};
    double *singleQubit = generateQubit(1, probabilitiesOfTwoQubits);

    cout << "Qubit before HADAMARD:" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit after HADAMARD:" << endl;
    printQubit(makeHadamardOnQubit(singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testPhaseShiftQuantumGate() {
    double probabilitiesOfTwoQubits[] = {0.0, 1.0};
    double *singleQubit = generateQubit(1, probabilitiesOfTwoQubits);
    double angle = M_PI;

    cout << "Qubit before PHASE SHIFT:" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit after PHASE SHIFT:" << endl;
    printQubit(makePhaseShiftOnQubit(angle, singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testPauliXQuantumGate() {
    double probabilitiesOfQubit0[] = {1, 0};
    double *singleQubit = generateQubit(1, probabilitiesOfQubit0);

    cout << "Qubit 0 (1 0) before PAULI X:" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit 0 (1 0) after PAULI X:" << endl;
    printQubit(makePauliXOnQubit(singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testPauliYQuantumGate() {
    double probabilitiesOfQubit0[] = {1, 0};
    double *singleQubit = generateQubit(1, probabilitiesOfQubit0);

    cout << "Qubit 0 (1 0) before PAULI Y:" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit 0 (1 0) after PAULI Y:" << endl;
    printComplexQubit(makePauliYOnQubit(singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testPauliZQuantumGate() {
    double probabilitiesOfQubit0[] = {1, 0};
    double *singleQubit = generateQubit(1, probabilitiesOfQubit0);

    cout << "Qubit 0 (1 0) before PAULI Z:" << endl;
    printQubit(singleQubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit 0 (1 0) after PAULI Z:" << endl;
    printQubit(makePauliZOnQubit(singleQubit), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void testQubitWithNonCorrectProbabilities() {
    double probabilitiesOfThreeQubits[] = {4.0, 0.0, 3.0, 0.0, 4.0, 0.0, 3.0, 0.0};
    double *threeQubits = generateAndNormalizeQubit(3, probabilitiesOfThreeQubits);
}

void testGetMultidimensionalHadamardGate(int indexNumber) {
    double **hadamardGate = getMultidimensionalHadamardGate(indexNumber);
    cout << "Generated Hadamard gate for n = " << indexNumber << " (H" << indexNumber << ")" << endl;
    printMultidimensionalHadamardGate(hadamardGate, indexNumber);
}

void testMultidimensionalHadamardGate(int indexNumber, int qubitNumber, double *probabilitiesOfQubits) {
    double **hadamardGate = getMultidimensionalHadamardGate(indexNumber);
    double *qubit = generateQubit(qubitNumber, probabilitiesOfQubits);

    cout << "Qubit before multidimensional Hadamard:" << endl;
    printQubit(qubit, ROWS_NUMBER_IN_SINGLE_QUBIT);
    cout << "Qubit after multidimensional Hadamard:" << endl;
    printQubit(makeMultidimensionalHadamardOnQubit(hadamardGate, indexNumber, qubit, qubitNumber), ROWS_NUMBER_IN_SINGLE_QUBIT);
}

void defineDataForTestMultidimensionalHadamardGate() {
    //Test single qubit (0) * H0
    double probabilitiesOfSingleQubit[] = {1.0, 0.0};
    testMultidimensionalHadamardGate(0, 1, probabilitiesOfSingleQubit);

    //Test single qubit (0) * H1
    testMultidimensionalHadamardGate(1, 1, probabilitiesOfSingleQubit);

    //Test two qubits (00) * H2
    double probabilitiesOfTwoQubits[] = {1.0, 0.0, 0.0, 0.0};
    testMultidimensionalHadamardGate(2, 2, probabilitiesOfTwoQubits);

    //Test three qubits (000) * H3
    double probabilitiesOfThreeQubits[] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    testMultidimensionalHadamardGate(3, 3, probabilitiesOfThreeQubits);
}

int main() {
    testNotQuantumGate();
    testSqrtNotQuantumGate();
    testCnotQuantumGate();
    testSwapQuantumGate();
    testFredkinQuantumGate();
    testToffoliQuantumGate();
    testHadamardQuantumGate();
    testPhaseShiftQuantumGate();
    testPauliXQuantumGate();
    testPauliYQuantumGate();
    testPauliZQuantumGate();
    defineDataForTestMultidimensionalHadamardGate();

    //runMatrixOperations();
    return 0;
}
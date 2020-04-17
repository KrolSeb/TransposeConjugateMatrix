#include <complex>
#include "headers/quantumGate.h"

using namespace std;

/// Function used to compose two quantum gates.
/// Compose - multiplication of values from two matrices, at the same indexes
complex<double> **composeQuantumGates(complex<double> **firstGate, complex<double> **secondGate, int gateSize) {
    complex<double> **outputGate = getAllocatedQuantumGate(gateSize);

    for (int i = 0; i < gateSize; i++) {
        for (int j = 0; j < gateSize; j++) {
            for (int k = 0; k < gateSize; k++) {
                outputGate[i][j] += firstGate[i][k] * secondGate[k][j];
            }
        }
    }

    return outputGate;
}

/// Function used to get identity matrix for defined size.
/// Identity matrix - https://en.wikipedia.org/wiki/Identity_matrix
complex<double> **getIdentityMatrix(int gateSize) {
    complex<double> **identityMatrix = getAllocatedQuantumGate(gateSize);

    for (int i = 0; i < gateSize; i++) {
        for (int j = 0; j < gateSize; j++) {
            if (i == j) {
                identityMatrix[i][j] = 1;
            }
            else {
                identityMatrix[i][j] = 0;
            }
        }
    }

    return identityMatrix;
}

/// Helper function with logic to check if identity matrix are the same as composed gates.
bool isIdentityMatrixAndComposedGatesAreEqual(complex<double> **identityMatrix, complex<double> **composedGates, int gateSize) {
    double epsilon = 0.0000001;
    for (int i = 0; i < gateSize; i++) {
        for (int j = 0; j < gateSize; j++) {
            if(fabs(identityMatrix[i][j] - composedGates[i][j]) >= epsilon) {
                return false;
            }
        }
    }

    return true;
}

/// Function used to check if composed gates given identity matrix.
bool isComposeOfGatesGivesIdentityMatrix(complex<double> **firstGate, complex<double> **secondGate, int gateSize) {
    complex<double> **identityMatrix = getIdentityMatrix(gateSize);
    complex<double> **outputGate = composeQuantumGates(firstGate, secondGate, gateSize);

    return isIdentityMatrixAndComposedGatesAreEqual(identityMatrix, outputGate, gateSize);
}

/// Function used to check if matrix is unitary
/// Unitary matrix - https://en.wikipedia.org/wiki/Unitary_matrix
bool isMatrixUnitary(complex<double> **quantumGate, complex<double> **conjugateTransposedQuantumGate, int gateSize) {
    complex<double> **identityMatrix = getIdentityMatrix(gateSize);
    complex<double> **firstConditionMatrix = composeQuantumGates(quantumGate, conjugateTransposedQuantumGate, gateSize);
    complex<double> **secondConditionMatrix = composeQuantumGates(conjugateTransposedQuantumGate, quantumGate, gateSize);

    bool isFirstConditionDone = isIdentityMatrixAndComposedGatesAreEqual(identityMatrix, firstConditionMatrix, gateSize);
    bool isSecondConditionDone = isIdentityMatrixAndComposedGatesAreEqual(identityMatrix, secondConditionMatrix, gateSize);
    return isFirstConditionDone && isSecondConditionDone;
}

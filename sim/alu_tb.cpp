#include "Valu.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#define ALU_ADD  0
#define ALU_SUB  1
#define ALU_AND  2
#define ALU_OR   3
#define ALU_XOR  4
#define ALU_SLL  5
#define ALU_SRA  6
#define ALU_SRL  7
#define ALU_EQ   8
#define ALU_NEQ  9
#define ALU_SLT  10
#define ALU_SLTU 11

const char* opName(int op) {
    switch(op) {
        case ALU_ADD:  return "Add";
        case ALU_SUB:  return "Sub";
        case ALU_AND:  return "And";
        case ALU_OR:   return "Or";
        case ALU_XOR:  return "Xor";
        case ALU_SLL:  return "Sll";
        case ALU_SRA:  return "Sra";
        case ALU_SRL:  return "Srl";
        case ALU_EQ:   return "Eq";
        case ALU_NEQ:  return "Neq";
        case ALU_SLT:  return "Slt";
        case ALU_SLTU: return "Sltu";
        default:       return "Invalid";
    }
}

uint32_t simulateExpected(uint32_t a, uint32_t b, int op) {
    switch(op) {
        case ALU_ADD:  return a + b;
        case ALU_SUB:  return a - b;
        case ALU_AND:  return a & b;
        case ALU_OR:   return a | b;
        case ALU_XOR:  return a ^ b;
        case ALU_SLL:  return a << (b & 0x1F);
        case ALU_SRA:  return ((int32_t)a) >> (b & 0x1F);
        case ALU_SRL:  return a >> (b & 0x1F);
        case ALU_EQ:   return (a == b) ? 1 : 0;
        case ALU_NEQ:  return (a != b) ? 1 : 0;
        case ALU_SLT:  return ((int32_t)a < (int32_t)b) ? 1 : 0;
        case ALU_SLTU: return (a < b) ? 1 : 0;
        default:       return 0xDEADBEEF;
    }
}

int main() {
    Verilated::mkdir("logs");
    Verilated::randReset(2);
    Valu* alu = new Valu;

    const int numberSimulations = 1000;
    int failures = 0;

    srand(time(NULL));

    for (int i = 0; i < numberSimulations; i++) {
        uint32_t a = rand();
        uint32_t b = rand();
        int op = rand() % 12;  // now 12 ops

        alu->a = a;
        alu->b = b;
        alu->op = op;
        alu->eval();

        uint32_t expected = simulateExpected(a, b, op);
        uint32_t received = alu->out;

        bool pass = (expected == received);

        std::cout << "Test " << i << ": "
                  << "a = " << a << ", b = " << b
                  << ", op = " << opName(op)
                  << ", expected = " << expected
                  << ", received = " << received
                  << (pass ? " ✅" : " ❌")
                  << std::endl;

        if (!pass) failures++;
    }

    std::cout << "\nTotal failures: " << failures
              << " out of " << numberSimulations << std::endl;

    delete alu;
    return 0;
}

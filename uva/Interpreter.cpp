#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

class Machine {
public:
    Machine() {
        memset(mem, 0, sizeof(mem));
        memset(reg, 0, sizeof(reg));
    }

    void setMem(int addr, int value) {
        mem[addr] = value % 1000;
    }

    int getMem(int addr) {
        return mem[addr];
    }

    int getReg(int r) {
        return reg[r];
    }

    void setReg(int r, int value) {
        reg[r] = value % 1000;
    }

private:
    int mem[1000];
    int reg[10];
};

int main() {
    freopen("Interpreter.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    char* line = NULL;
    size_t line_size = 0;
    for (int i = 0; i < cases; ++i) {
        Machine machine;
        int addr = 0;
        do {
            getline(&line, &line_size, stdin);
        } while (!isdigit(line[0]));
        while (true) {
            int value = (line[0] - '0') * 100 + (line[1] - '0') * 10 + line[2] - '0';
            //printf("setMem(%d, %03d)\n", addr, value);
            machine.setMem(addr++, value);
            if (getline(&line, &line_size, stdin) <= 0) {
                break;
            }
            if (!isdigit(line[0])) {
                break;
            }
        }
        addr = 0;
        int count = 0;
        while (true) {
            int inst = machine.getMem(addr);
            count++;
            int op = inst / 100;
            int a = inst / 10 % 10;
            int b = inst % 10;
            if (op == 1) {
                break;
            }
            bool branch = false;
            switch (op) {
                case 2: {
                    machine.setReg(a, b);
                    break;
                }
                case 3: {
                    machine.setReg(a, machine.getReg(a) + b);
                    break;
                }
                case 4: {
                    machine.setReg(a, machine.getReg(a) * b);
                    break;
                }
                case 5: {
                    machine.setReg(a, machine.getReg(b));
                    break;
                }
                case 6: {
                    machine.setReg(a, machine.getReg(a) + machine.getReg(b));
                    break;
                }
                case 7: {
                    machine.setReg(a, machine.getReg(a) * machine.getReg(b));
                    break;
                }
                case 8: {
                    machine.setReg(a, machine.getMem(machine.getReg(b)));
                    break;
                }
                case 9: {
                    machine.setMem(machine.getReg(b), machine.getReg(a));
                    break;
                }
                case 0: {
                    if (machine.getReg(b) != 0) {
                        addr = machine.getReg(a);
                        branch = true;
                    }
                    break;
                }
            }
            if (!branch) {
                addr++;               
            }
        }
        if (i > 0) {
            printf("\n");
        }
        printf("%d\n", count);
    }
}
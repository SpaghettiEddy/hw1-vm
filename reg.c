#include "reg.h"

void add(int s, int t, int d)
{
    regi.GPR[d] = regi.GPR[s] + regi.GPR[t];
    return;
}

void sub(int s, int t, int d)
{
    regi.GPR[d] = regi.GPR[s] - regi.GPR[t];
    return;
}

void mult(int s, int t)
{
    long int res = regi.GPR[s] * regi.GPR[t];
    long int temphi = (res >> 32);
    long int templo = (res << 32) >> 32;
    regi.hi = temphi;
    regi.lo = templo;
    return;
}

void divi(int s, int t)
{
    regi.hi = regi.GPR[s] % regi.GPR[t];
    regi.lo = regi.GPR[s] / regi.GPR[t];
    return;
}

void mfhi(int d)
{
    regi.GPR[d] = regi.hi;
    return;
}

void mflo(int d)
{
    regi.GPR[d] = regi.lo;
    return;
}

void and (int s, int t, int d)
{
    regi.GPR[d] = regi.GPR[s] & regi.GPR[t];
    return;
}

void bor(int s, int t, int d)
{
    regi.GPR[d] = regi.GPR[s] | regi.GPR[t];
    return;
}

void nor(int s, int t, int d)
{
    regi.GPR[d] = ~(regi.GPR[s] | regi.GPR[t]);
    return;
}

void xor (int s, int t, int d) {
    regi.GPR[d] = regi.GPR[s] ^ regi.GPR[t];
    return;
}

void sll(int t, int d, int h)
{
    regi.GPR[d] = regi.GPR[t] << h;
    return;
}

void srl(int t, int d, int h)
{
    regi.GPR[d] = regi.GPR[t] >> h;
    return;
}

void jr(int s)
{
    regi.pc = regi.GPR[s];
    return;
}

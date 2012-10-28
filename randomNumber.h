#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

class RandomNumber
{
    public:
    static int generateNumber(int a) { return rand()% a;}
};

#endif // RANDOMNUMBER_H

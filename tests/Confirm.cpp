//
// Created by razor on 25.10.2023.
//
#include "../Test.h"

bool isPassingGrade(int value) {
    if (value < 60) {
        return false;
    }
    return true;
}

bool isNegative(int value) {
    return value < 0;
}

int multiplyBy2(int value)
{
    return value * 2;
}

//bool isPassingGrade(int value) {
//    return true;

TEST("Test can be created") {
}

TEST("Test will pass without any confirms") {}

TEST("Test int confirms")
{
    int result = multiplyBy2(0);
    CONFIRM(0,result);
    result = multiplyBy2(1);
    CONFIRM(2,result);
    result = multiplyBy2(-1);
    CONFIRM(-2,result);

}
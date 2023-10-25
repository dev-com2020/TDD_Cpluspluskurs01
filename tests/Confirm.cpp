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

//bool isPassingGrade(int value) {
//    return true;

TEST("Test can be created") {
}

TEST("Test will pass without any confirms") {}

TEST("Test passing grades") {
    bool result = isPassingGrade(0);
    CONFIRM_FALSE(result);
    result = isPassingGrade(100);
    CONFIRM_TRUE(result);
}

TEST("Test passing confirms")

{
    bool result = isNegative(0);
    CONFIRM_FALSE(result);
    result = isNegative(-1);
    CONFIRM_TRUE(result);
}
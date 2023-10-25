//
// Created by razor on 25.10.2023.
//
#ifndef INC_01_TEST_H
#define INC_01_TEST_H
#include <string_view>
#include <vector>
namespace TDD
{
    class TestInterface
    {
    public:
        virtual ~TestInterface() = default;
        virtual void run () = 0;
    };
    std::vector<TestInterface *> & getTest (){
        static std::vector<TestInterface *> tests;
        return tests;
    }
} // namespace TDD

#define TEST \
class Test \
{ \
public: \
    Test (std::string_view name) \
            : nName(name), mResult(true) \
    {} \
    void operator () (); \
private: \
    std::string nName; \
    bool mResult; \
}; \
Test test("testCanBeCreated"); \
void Test::operator()()
#endif //INC_01_TEST_H
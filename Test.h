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
    inline std::vector<TestInterface *> & getTests (){
        static std::vector<TestInterface *> tests;
        return tests;
    }
    inline void runTests ()
    {
        for (auto * test: getTests())
        {
            test->run();
        }
    }
} // namespace TDD

#define TEST \
class Test : public TDD::TestInterface \
{ \
public: \
    Test (std::string_view name) \
            : nName(name), mResult(true) \
    { TDD::getTests().push_back(this);} \
    void run () override; \
private: \
    std::string nName; \
    bool mResult; \
}; \
Test test("testCanBeCreated"); \
void Test::run ()
#endif //INC_01_TEST_H
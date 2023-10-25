//
// Created by razor on 25.10.2023.
//
#ifndef INC_01_TEST_H
#define INC_01_TEST_H
#include <string_view>
#include <vector>
#include <iostream>
namespace TDD
{
    class TestBase
    {
    public:
        TestBase (std::string_view name)
        : nName(name), mPassed(true)
        {}

        virtual ~TestBase() = default;
        virtual void run () = 0;

        std::string_view name () const
        {
            return nName;
        }
        bool passed () const
        {
            return mPassed;
        }

        std::string_view reason () const
        {
            return mReason;
        }
        void setFailed (std::string_view reason)
        {
            mPassed = false;
            mReason = reason;
        }
    private:
        std::string nName;
        bool mPassed;
        std::string mReason;
    };
    inline std::vector<TestBase *> & getTests (){
        static std::vector<TestBase *> tests;
        return tests;
    }
    inline int runTests ()
    {
        std::cout << "Running "
        << getTests().size()
        << " test\n";
        int numPassed = 0;
        int numFailed = 0;
        for (auto * test: getTests())
        {
            std::cout << "-------------------\n"
            << test->name()
            << std::endl;
            try {
                test->run();
            }
            catch (...)
            {
                test->setFailed("Unexpected exception thrown.");
            }
            if (test->passed())
            {
                ++numPassed;
                std::cout << "Passed"
                << std::endl;
            }
            else
            {
                ++numFailed;
                std::cout << "Failed\n"
                          << test->reason()
                          << std::endl;
            }
        }
        std::cout << "-------------------\n";
        if (numFailed == 0)
        {
            std::cout << "All tests passed."
            << std::endl;
        }
        else
        {
            std::cout << "Test passed: " << numPassed
            << "\nTest failed: " << numFailed
            << std::endl;
        }
        return numFailed;
    }
} // namespace TDD
#define TDD_CLASS_FINAL( line ) Test ## line
#define TDD_CLASS_RELAY( line ) TDD_CLASS_FINAL( line )
#define TDD_CLASS TDD_CLASS_RELAY(__LINE__)
#define TDD_INSTANCE_FINAL( line ) test ## line
#define TDD_INSTANCE_RELAY( line ) TDD_INSTANCE_FINAL( line )
#define TDD_INSTANCE TDD_INSTANCE_RELAY(__LINE__)


#define TEST( testName ) \
class TDD_CLASS : public TDD::TestBase \
{ \
public: \
    TDD_CLASS (std::string_view name) \
            : TestBase(name) \
    { TDD::getTests().push_back(this);} \
    void run () override; \
};                       \
TDD_CLASS TDD_INSTANCE(testName);\
void TDD_CLASS::run ()
#endif //INC_01_TEST_H
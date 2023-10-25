//
// Created by razor on 25.10.2023.
//
#ifndef INC_01_TEST_H
#define INC_01_TEST_H
#include <string_view>
#include <vector>
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
    inline void runTests ()
    {
        for (auto * test: getTests())
        {
            try {
                test->run();
            }
            catch (...)
            {
                test->setFailed("Unexpected exception thrown.");
            }
        }
    }
} // namespace TDD

#define TEST( testName ) \
class Test : public TDD::TestBase \
{ \
public: \
    Test (std::string_view name) \
            : testBase(name) \
    { TDD::getTests().push_back(this);} \
    void run () override; \
}; \
void Test::run ()
#endif //INC_01_TEST_H
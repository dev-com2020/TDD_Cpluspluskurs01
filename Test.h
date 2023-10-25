//
// Created by razor on 25.10.2023.
//
#ifndef INC_01_TEST_H
#define INC_01_TEST_H

#include <string_view>
#include <vector>
#include <iostream>
#include <ostream>

namespace TDD {

    class MissingException {
    public:
        MissingException(std::string_view exType)
                : mExType(exType) {}

        std::string_view exType() const {
            return mExType;
        }
    private:
        std::string mExType;
    };

    class TestBase {
    public:
        TestBase(std::string_view name)
                : nName(name), mPassed(true) {}

        virtual ~TestBase() = default;

        virtual void runEx() {
            run();
        }

        virtual void run() = 0;

        std::string_view name() const {
            return nName;
        }

        bool passed() const {
            return mPassed;
        }

        std::string_view reason() const {
            return mReason;
        }

        void setFailed(std::string_view reason) {
            mPassed = false;
            mReason = reason;
        }
        void setExpectedFailureReason (std::string_view reason) {
            mExpectedReason = reason;
        }

    private:
        std::string nName;
        bool mPassed;
        std::string mReason;
        std::string mExpectedReason;
    };

    inline std::vector<TestBase *> &getTests() {
        static std::vector<TestBase *> tests;
        return tests;
    }

    inline int runTests(std::ostream &output) {
        output << "Running "
               << getTests().size()
               << " test\n";
        int numPassed = 0;
        int numFailed = 0;
        for (auto *test: getTests()) {
            output << "-------------------\n"
                   << test->name()
                   << std::endl;
            try {
                test->runEx();
            }
            catch (MissingException const & ex) {
                std::string message = "Expected exception type ";
                message += ex.exType();
                message += " was no thrown.";
                test->setFailed(message);
            }
            catch (...) {
                test->setFailed("Unexpected exception thrown.");
            }
            if (test->passed()) {
                ++numPassed;
                output << "Passed"
                       << std::endl;
            } else {
                ++numFailed;
                output << "Failed\n"
                       << test->reason()
                       << std::endl;
            }
        }
        output << "-------------------\n";
        if (numFailed == 0) {
            output << "All tests passed."
                   << std::endl;
        } else {
            output << "Test passed: " << numPassed
                   << "\nTest failed: " << numFailed
                   << std::endl;
        }
        return numFailed;
    }
} // namespace TDD
#define TDD_CLASS_FINAL(line) Test ## line
#define TDD_CLASS_RELAY(line) TDD_CLASS_FINAL( line )
#define TDD_CLASS TDD_CLASS_RELAY(__LINE__)
#define TDD_INSTANCE_FINAL(line) test ## line
#define TDD_INSTANCE_RELAY(line) TDD_INSTANCE_FINAL( line )
#define TDD_INSTANCE TDD_INSTANCE_RELAY(__LINE__)


#define TEST(testName) \
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

#define TEST_EX(testName, exceptionType) \
class TDD_CLASS : public TDD::TestBase \
{ \
public: \
    TDD_CLASS (std::string_view name) \
            : TestBase(name) \
    { TDD::getTests().push_back(this);} \
    void runEx () override                 \
    {                                      \
    try                                    \
    {                                      \
        run();\
    }                                      \
    catch (exceptionType const &)          \
    {                                      \
        return;\
    }                                      \
    throw TDD::MissingException(#exceptionType); \
}                                         \
void run () override;                     \
};                                         \
TDD_CLASS TDD_INSTANCE(testName);\
void TDD_CLASS::run ()
#endif //INC_01_TEST_H
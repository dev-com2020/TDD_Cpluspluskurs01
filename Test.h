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

    class ConfirmException {
    public:
        ConfirmException() = default;

        virtual ~ConfirmException() = default;

        std::string_view reason() const {
            return mReason;
        }

    protected:
        std::string mReason;
    };

    class BoolConfirmException : public ConfirmException {
    public:
        BoolConfirmException(bool expected, int line) {
            mReason = "Confirm fialed on line ";
            mReason += std::to_string(line) + "\n";
            mReason += "  Expected: ";
            mReason += expected ? "true" : "false";
        }
    };

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

        std::string_view expectedReason() const {
            return mExpectedReason;
        }

        void setFailed(std::string_view reason) {
            mPassed = false;
            mReason = reason;
        }

        void setExpectedFailureReason(std::string_view reason) {
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
        int numMissedFailed = 0;
        for (auto *test: getTests()) {
            output << "-------------------\n"
                   << test->name()
                   << std::endl;
            try {
                test->runEx();
            }
            catch (ConfirmException const &ex) {
                test->setFailed(ex.reason());
            }

            catch (MissingException const &ex) {
                std::string message = "Expected exception type ";
                message += ex.exType();
                message += " was no thrown.";
                test->setFailed(message);
            }
            catch (...) {
                test->setFailed("Unexpected exception thrown.");
            }
            if (test->passed()) {
                if (not test->expectedReason().empty()) {
                    ++numMissedFailed;
                    output << "Missed expected failure\n"
                           << "Test passed but was expected to fail"
                           << std::endl;
                } else {
                    ++numPassed;
                    output << "Passed"
                           << std::endl;
                }
            } else if (not test->expectedReason().empty() &&
                       test->expectedReason() == test->reason()) {
                ++numPassed;
                output << "Expected failure\n"
                       << test->reason()
                       << std::endl;

            } else {
                ++numFailed;
                output << "Failed\n"
                       << test->reason()
                       << std::endl;
            }
        }
        output << "-------------------\n";
        output << "Test passed: " << numPassed
               << "\nTest failed: " << numFailed;
        if (numMissedFailed != 0) {
            output << "\nTests failures missed: " << numMissedFailed;

            output << std::endl;
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
namespace {            \
class TDD_CLASS : public TDD::TestBase \
{ \
public: \
    TDD_CLASS (std::string_view name) \
            : TestBase(name) \
    { TDD::getTests().push_back(this);} \
    void run () override; \
};                     \
}/* end of unnamed namespace */\
TDD_CLASS TDD_INSTANCE(testName);\
void TDD_CLASS::run ()

#define TEST_EX(testName, exceptionType) \
namespace {                                        \
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
} /* end of unnamed namespace */         \
TDD_CLASS TDD_INSTANCE(testName);\
void TDD_CLASS::run ()

#define CONFIRM_FALSE(actual)\
if (actual)\
{\
throw TDD::BoolConfirmException(false, __LINE__);\
}                                    \

#define CONFIRM_TRUE(actual)\
if (not actual)\
{\
throw TDD::BoolConfirmException(true, __LINE__);\
}\

#endif //INC_01_TEST_H
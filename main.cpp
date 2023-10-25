#include <iostream>
#include <string_view>

class Test
        {
public:
            Test (std::string_view name)
            : nName(name), mResult(true)
            {}
            void operator () (){
                std::cout << nName << std::endl;
            }
private:
            std::string nName;
            bool mResult;
        };
Test test("testCanBeCreated");

int main() {
    test();
    return 0;
}

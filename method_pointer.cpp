#include <cstddef>
#include <iostream>
#include <vector>
#include <thread>

template<typename T>
struct DynamicInitCommand {
    void            (T::*init)();   // Pointer to (delayed) initialization method
    unsigned int    ticks;          // Number of ticks after init() is called
};

class Frontend
{
public:
    Frontend(){

        DynamicInitCommand<Frontend> init1, init2, init3;

        init1 = { &Frontend::dynamicInit1, 5};
        init2 = { &Frontend::dynamicInit2, 10};
        init3 = { &Frontend::dynamicInit3, 15};
        
        m_dynamicInit.push_back(init1);
        m_dynamicInit.push_back(init2);
        m_dynamicInit.push_back(init3);
    }

    unsigned int m_ticks{0};

    void tick(){

        std::cout << "tick: " << ++m_ticks << std::endl;

        /* Check for delayed initializations */

        std::vector<DynamicInitCommand<Frontend>>::iterator it = m_dynamicInit.begin();

        while (it != m_dynamicInit.end()){

            if (it->ticks < m_ticks){

                if(it->init)
                    ((*this).*(it->init))();

                it = m_dynamicInit.erase(it);

            } else {
                it++;
            }
        }
    }

private:

    void dynamicInit1(){
        std::cout << "dynamicInit1 called" << std::endl;
    }
    
    void dynamicInit2(){
        std::cout << "dynamicInit2 called" << std::endl;
    }

    void dynamicInit3(){
        std::cout << "dynamicInit3 called" << std::endl;
    }

    unsigned int m_initCnt{0};
    
    std::vector<DynamicInitCommand<Frontend> > m_dynamicInit;
};





class MyClass 
{
public:

    int sum(int a, int b){
        return a+b;
    }

    int *next(int *arrayOfInt){
        return ++arrayOfInt;
    }
};





int main(int argc, char* argv[]){

    std::cout << "Application started..." << std::endl;


    /*************************
     *       PART ONE        *
     *************************/
    

    /* Create an instance of MyClass */

    /* Step one: Define a pointer to the sum(...) method of MyClass */
    int (MyClass::*methodPtrOne)(int, int);

    /* Step two: assign thh member function sum(..) */
    methodPtrOne = &MyClass::sum;

    
    /* Step three: call the method by accessing the instance */
    
    MyClass clsInstance;
    int resultOne = (clsInstance.*methodPtrOne)(2, 3);

    std::cout << "resultOne: " << resultOne << std::endl;

    /*************************
     *       PART TWO        *
     *************************/

    Frontend frontendInstance;

    while(frontendInstance.m_ticks < 20){
        frontendInstance.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    while(true){
        
    }

}

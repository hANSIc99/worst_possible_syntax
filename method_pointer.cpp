#include <cstddef>
#include <iostream>
#include <vector>
#include <thread>

template<typename T>
struct DelayedInitCommand {
    void            (T::*init)();   // Pointer to (delayed) initialization method
    unsigned int    ticks;          // Number of ticks after init() is called
};

class Frontend
{
public:
    Frontend(){

        DelayedInitCommand<Frontend> init1, init2, init3;

        init1 = { &Frontend::delayedInit1, 5};
        init2 = { &Frontend::delayedInit2, 10};
        init3 = { &Frontend::delayedInit3, 15};
        
        m_delayedInit.push_back(init1);
        m_delayedInit.push_back(init2);
        m_delayedInit.push_back(init3);
    }

    unsigned int m_ticks{0};

    void tick(){

        std::cout << "tick: " << ++m_ticks << std::endl;

        /* Check for delayed initializations */

        std::vector<DelayedInitCommand<Frontend>>::iterator it = m_delayedInit.begin();

        while (it != m_delayedInit.end()){

            if (it->ticks < m_ticks){

                if(it->init)
                    ((*this).*(it->init))();

                it = m_delayedInit.erase(it);

            } else {
                it++;
            }
        }
    }

private:

    void delayedInit1(){
        std::cout << "delayedInit1 called" << std::endl;
    }
    
    void delayedInit2(){
        std::cout << "delayedInit2 called" << std::endl;
    }

    void delayedInit3(){
        std::cout << "delayedInit3 called" << std::endl;
    }

    unsigned int m_initCnt{0};
    
    std::vector<DelayedInitCommand<Frontend> > m_delayedInit;
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

}

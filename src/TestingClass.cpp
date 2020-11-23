#include "TestingClass.h"  

TestingClass::TestingClass(int input){
    m_stored_value = input;
}

TestingClass::~TestingClass(){

}

int TestingClass::get_value(){
    return m_stored_value;
}
#include <iostream>
#include "treat_directory.h"

int main(void){
    std::cout<<"Hello, world!"<<std::endl;    
    treat_directory* td = new treat_directory(); 
    std::cout<<td->get_message()<<std::endl;    
    delete td;
    return 0;
}
#include <iostream>
#include <thread>

/*Purpose: This program demonstrates how to start a thread for a function that is a member of a class 
            and pass an argument to the function by reference.*/
class A {
  public:
    int change_status(bool& z) {
      //std::cout << a << " + " << b << " + " << z << " is " << a + b + z << std::endl;
      while (true) {
        std::cout << "thread status: " << z << std::endl;
        
        /*Changes to the status are performed in the thread*/
        if (z == true) { z = false; }
        else if (z == false) { z = true; }
 
        std::this_thread::sleep_for(std::chrono::seconds(6));
      }
    }
  };

int main() {
  A alpha;
  bool status = true;

  /*std::thread takes at least 1 argument. 
  
  The first argument is always a pointer to
  the function. In this case, the function belongs to class A so we reference the class
  directly and not the instance of the class.
  
  If the function pointed to belongs to a class, the second argument will be a reference or
  pointer to the object instance (&alpha as shown below). This is specified in the API.

  Additional arguments can then be passed after. Note that std::thread passes by
  value by default. It will also take a constant reference (std::cref(var)). This
  is done to prevent race conditions.

  To work around this, we can force it to pass by reference by using std::ref(var). However,
  the developer will now need to handle race conditions on his/her own.

  Additional note: std::thread() will ALWAYS return void.
  */
  std::thread (&A::change_status, &alpha, std::ref(status)).detach();
  
  while (true) {

    /*Constantly prints the status to see if thread manipulates the "status"
    variable in main*/
    std::cout << "main status: " << status << std::endl;
   
    std::this_thread::sleep_for(std::chrono::seconds(6));
  }
}
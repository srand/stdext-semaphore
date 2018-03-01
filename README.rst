================
stdext-semaphore
================
Semaphore written in C++11

Usage
-----

Example:
::
   stdext::semaphore sem;
   
   std::cout << sem.value() << std::endl;
   sem.post();
   std::cout << sem.value() << std::endl;
   sem.wait();
   std::cout << sem.value() << std::endl;
   
   sem.reset(3);
   std::cout << sem.value() << std::endl;
   
   sem.wait_for(500ms); // C++14
   sem.wait_until(std::chrono::system_clock::now() + 5s); // C++14

   
Build
-----

Use Pam, http://github.com/srand/pam
::
   stdext_semaphore = cxx_project(
      name = "stdext-semaphore",
      incpaths = [("include", {"publish": True})]
   )
   
   cxx_executable(
      name = "hello",
      sources = ["hello.cpp"],
      dependencies = [stdext_semaphore]
   )

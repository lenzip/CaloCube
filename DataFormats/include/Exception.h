#ifndef CaloCubeException_h
#define CaloCubeException_h

#include <exception>
#include <string>
#include <sstream>

namespace CaloCube{
  class Exception : public std::exception {

    public:
    Exception(std::string cathegory):_cathegory(cathegory){};

    virtual const char* what() const throw(){
      std::stringstream fullmessage;
      fullmessage << "\n**************BEGIN EXCEPTION*******************\n";
      fullmessage << "Exception of cathegory: " << _cathegory << "\n";
      fullmessage << message << "\n";
      fullmessage << "***************END EXCEPTION********************\n";
      return fullmessage.str().c_str();
    }

    ~Exception() throw(){};

    template<class T> Exception operator<<(const T& stuff){
      std::stringstream content;
      content << stuff;
      message += content.str();
      return *this;
    }

    
    private:
    // the exception cathegory
    std::string _cathegory;

    // the exception message
    std::string message;

  };


}
#endif

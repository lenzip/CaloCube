#ifndef CaloCubeRef_h
#define CaloCubeRef_h

#include <string>
#include "Exception.h"
#include "GlobalEvent.h"
#include "TROOT.h"
#include "TTree.h"

namespace CaloCube {
  
  template<class T>
  class Ref {

    public:
    //constructor
    Ref() {}	
    Ref(std::string treeName, std::string branchName, unsigned int index);

    const T& get() const;

    private:
    //the name of the tree this references to
    std::string _treeName;
    //the name of the branch this references to
    std::string _branchName;
    //the event number
    static int _lastevent;
    //the index in std::vector<T> contaned in the referenced branch
    unsigned int _index;
    // the container of the branch when reading the tree
    static std::vector<T>* _container;

  
  };

  template<class T>
  Ref<T>::Ref(std::string treeName, std::string branchName, unsigned int index):
   _treeName(treeName),
   _branchName(branchName),
   _index(index)
   {
    _lastevent = -1;
   }

  template<class T>
  const T& Ref<T>::get() const{
    if ( _lastevent != GlobalEvent::getEventNumber() || _container==0 ){
      if (_container != 0)
        delete _container;
      TTree* tree = (TTree*) gROOT->Get(_treeName.c_str());
      if (!tree){
        throw Exception("CaloCube::Ref") << "Tree " << _treeName << " not found.";  
      }
      _container =  new std::vector<T>();
      int iret = tree->SetBranchAddress(_branchName.c_str(), &_container);
      if (iret != 0){
        throw Exception("CaloCube::Ref") << " Cannot set " << _branchName;
      }
      _lastevent = GlobalEvent::getEventNumber();
    }  

    return (*_container)[_index];
    
  }

  template<class T> int Ref<T>::_lastevent;
  template<class T> std::vector<T>* Ref<T>::_container;
}

#endif

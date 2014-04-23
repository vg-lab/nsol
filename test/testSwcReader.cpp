#include <nsdl.h>

#include <assert.h>

#include <iostream>


using namespace nol;
using namespace std;

int main (int argc, char *argv[]) {

  SwcReader r;

  cout << "Reading file" << argv[1] << endl;

  NeuronPtr n = r.readFile(argv[1]);



}

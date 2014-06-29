#include <iostream>
using namespace std;

#include "image_output.h"
#include "main.h"

int main(int argc, char const *argv[])
{
  cout << "Hello, foo!" << endl;

  writeSampleImage("./bin/random.jpg");

  return 0;
}

#include "Span.hpp"

int main() {
  Span sp = Span(5);
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  std::cout << sp.shortestSpan() << std::endl;
  std::cout << sp.longestSpan() << std::endl;

  Span span1(5);

  span1.addNumber(4);
  try
  {
    std::cout << span1 << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

    Span span2(5000000);

  span2.addNumber(3);
  span2.randomFill();
  std::cout << span2 << std::endl;

  Span              span3(5);
  std::vector<int>      vect;

  vect.push_back(25);
  vect.push_back(5);
  vect.push_back(12);
  vect.push_back(90);
  vect.push_back(-2);
  span3.addByIteratorRange(vect.begin(), vect.end());
  std::cout << span3 << std::endl;

  
return 0; }
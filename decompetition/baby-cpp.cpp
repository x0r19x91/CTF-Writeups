#include <cstring>
#include <iostream>
#include <string>
#include <vector>

bool check(const std::string& hand, const std::string& word) {
  // Here be dragons.
  std::vector<int> arr(26, 0);
  for (char ch : hand)
  {
    if (!isalpha(ch)) return 0;
    // {
    arr[toupper(ch)-0x41]++;
    // }
    // else
    // {
    //   return 0;
    // }
  }
  for (char ch : word)
  {
    if (!isalpha(ch)) return 0;
    // {
      if (--arr[toupper(ch)-0x41] < 0) return false;
    // }
    // else
    // {
    //   return 0;
    // }
  }
  return true;
}

int score(const std::string& word) {
  // Here be more dragons.
  int sum = 0;
  std::vector<int> arr {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 0xa, 1, 1, 1, 1, 5, 4, 8, 3, 0xa};
  // while (pb != pe)
  // {
  //   sum += arr[toupper(*pb)-0x41];
  //   ++pb;
  // }
  for (char ch : word)
  {
    sum += arr[toupper(ch)-0x41];
  }
  return sum;
}

int main(int argc, char** argv) {
  // Here be porcupines.
  if (argc != 3) {
    std::cerr << "USAGE: ./clabbers [hand] [word]" <<std::endl;
    return 1;
  } else {
    std::string fuck(argv[1]), fuck2(argv[2]);
    if (check(fuck, fuck2))
    {
      int xp = score(fuck2) ;
      auto s = (xp == 1 ? "" : "s");
      std::cout << xp << " point" << s << "." << std::endl;
      return 0;
    }
    else
    {
      std::cout << "Invalid." << std::endl;
      return 2;
    }
  }
}

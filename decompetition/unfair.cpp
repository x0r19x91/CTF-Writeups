#include <string>
#include <iostream>
#include <utility>
#include <tuple>
#include <functional>

typedef unsigned long ulong;

const std::string UNFAIR[] = {"LREOT", "HQGNU", "YIVXC", "DBKFM", "PZWAS"};

std::string clean(const std::string& s)
{
  std::string ans;
  for (size_t i = 0; i < s.size(); i++)
  {
    if (s[i] == 'j' || s[i] == 'J')
    {
      ans += 'I';
    }
    else
    {
      if (isalpha(s[i]))
        ans += toupper(s[i]);
    }
  }
  if (ans.size() %2 == 1)
    ans += 'X';
  return ans;
}

std::tuple<ulong, ulong> find(char ch)
{
  ulong i = 0, pos;
  while (1)
  {
    if (i <= 4ul)
    {
      pos = UNFAIR[i].find(ch);
      if (pos != -1)
      {
        return std::make_tuple(i, pos);
      }
      ++i;
    }
    else
    {
      std::cerr << "Chaos and corruption!" << std::endl;
      exit(1);
    }
  }
}

// TODO: find clean crypt
std::string crypt(const std::string& s)
{
  auto p = clean(s);
  std::string ans {};
  for (int i = 0; i < p.size(); i += 2)
  {
    // std::tuple<ulong&, ulong&> tp, tq;
    // auto tp = find(p[i]);
    // auto &pa = std::get<0>(tp);
    // auto &pb = std::get<1>(tp);
    auto [pa, pb] = find(p[i]); // uses std::get and returns rvalue ref
    auto [qa, qb] = find(p[i+1]);
    // auto &qa = std::get<0>(tq);
    // auto &qb = std::get<1>(tq);
    if (pa == qa)
    {
      pb = (pb+1)%5;
      qb = (qb+1)%5;
    }
    else if (pb == qb)
    {
      pa = (pa + 1) % 5;
      qa = (qa + 1) % 5;
    }
    else
    {
      std::swap(pb, qb);
    }
    ans += UNFAIR[pa][pb];
    ans += UNFAIR[qa][qb];
  }
  return ans;
}

int main(int argc, char** argv) {
  // Because vampires have standards.
  if (argc != 2)
  {
    std::cerr << "USAGE: ./unfair [text]\n";
    exit(1);
  }

  std::cout << crypt(argv[1]) << std::endl;
}

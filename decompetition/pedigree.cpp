#include <iostream>
#include <map>
#include <set>
#include <string>

class Person {
public:
  std::string name;
private:
  Person* m_fuckMN;
  Person* m_fuckFN;
  std::set<Person*, std::less<Person*>> m_fuckSet;
public:
  static Person* find(const std::string& m);
  static std::map<std::string, Person*> ALL;
  Person(const std::string& pn, const std::string& mn, const std::string& fn) ;
  std::set<Person*> ancestors() const;
  std::set<Person*> descendants() const;
};

std::map<std::string, Person*> Person::ALL = {{"???", nullptr}};

Person::Person(const std::string& pn, const std::string& mn, const std::string& fn)
{
  name = pn;
  m_fuckMN = find(mn);
  m_fuckFN = find(fn);
  if (m_fuckMN)
  {
    m_fuckMN->m_fuckSet.insert(this);
  }
  if (m_fuckFN)
  {
    m_fuckFN->m_fuckSet.insert(this);
  }
  ALL[pn] = this;
}

Person* Person::find(const std::string& m)
{
  auto xp = ALL.find(m);
  if (xp == ALL.end())
  {
    std::cerr << "Unknown person: " << m << '\n';
    exit(2);
  }
  return xp->second;
}

std::set<Person*> Person::ancestors() const
{
  std::set<Person*> ps;
  if (m_fuckMN)
  {
    ps.merge(m_fuckMN->ancestors());
    ps.insert(m_fuckMN);
  }
  if (m_fuckFN)
  {
    ps.merge(m_fuckFN->ancestors());
    ps.insert(m_fuckFN);
  }
  return ps;
}

std::set<Person*> Person::descendants() const
{
  std::set ans(m_fuckSet);
  for (Person* p : m_fuckSet)
  {
    ans.merge(p->descendants());
  }
  return ans;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "USAGE: ./pedigree [name]\n";
    std::exit(1);
  }

  std::string pname, mname, fname;
  while(std::cin >> pname >> mname >> fname) {
    new Person(pname, mname, fname);
  }

  // std::string s = argv[1];
  Person* mc = Person::find(argv[1]);
  std::cout << argv[1] << "'s Ancestors:\n";
  for(auto person: mc->ancestors()) {
    std::cout << " - " << person->name << '\n';
  }

  std::cout << argv[1] << "'s Descendants:\n";
  for(auto person: mc->descendants()) {
    std::cout << " - " << person->name << '\n';
  }
}

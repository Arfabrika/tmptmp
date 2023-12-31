#define PAGE_COUNT 8

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "lab4.h"

using namespace std;

class page
{
public:
  int number;
  bool r;
  bool m;
  int type;

  page(int number, bool r, bool m)
  {
    this->number = number;
    this->r = r;
    this->m = m;
    this->set_type();
  };

  void set_type()
  {
    if (r)
    {
      if (m)
	type = 3;
      else
	type = 2;
    }
    else
    {
      if (m)
	type = 1;
      else
	type = 0;
    }
  };
};

void print_pages_NRU(vector<pair<int, page*>> pages)
{
  for (int i = 0; i<pages.size(); i++)
  {
    if (i < PAGE_COUNT - 1)
    cout << pages[i].second->number << " ";
      //cout  <<  pages[i].second->number << "(" << pages[i].second->get_r() << ", " << pages[i].second->get_m() << ")t:" << pages[i].first << "," << pages[i].second->type << " ";
    else
      //cout  << pages[i].second->number << "(" << pages[i].second->get_r() << ", " << pages[i].second->get_m() << ")t:" << pages[i].first<< "," << pages[i].second->type;
      cout << pages[i].second->number;
  }
  for (int i = pages.size(); i < PAGE_COUNT; i++)
  {
    if (i < PAGE_COUNT - 1)
      cout << "# ";
    else
      cout << "#";
  }
  cout << endl;
}

void print_pages_clock(vector<page*> pages)
{
  for (int i = 0; i<pages.size(); i++)
  {
    if (i < PAGE_COUNT - 1)
      cout << pages[i]->number << " ";
    else
      cout << pages[i]->number;
  }
  for (int i = pages.size(); i < PAGE_COUNT; i++)
  {
    if (i < PAGE_COUNT - 1)
      cout << "# ";
    else
      cout << "#";
  }
  cout << endl;
}

vector<pair<int, page*>> set_r_null(vector<pair<int, page*>> pages)
{
  for (int i = 0; i < pages.size(); i++)
  {
    pages[i].second->r = 0;
    pages[i].second->set_type();
    pages[i].first = pages[i].second->type;
  }
  return pages;
}

void set_r_null(vector<page*> pages)
{
  for (int i = 0; i < pages.size(); i++)
  {
    pages[i]->r = 0;
    pages[i]->set_type();
  }
}

void clock_alg()
{
  vector<page*> pages;
  string str;
  int cnt = 0, last_r_ind = 0, replace_cnt = 0;  

  while (true)
  {
    getline(cin, str);
    if (str.empty())
      break;

    if (cnt % 5 == 0)
      set_r_null(pages);
    cnt++;
    
    bool mode = str[0] -'0';
    int num = stoi(str.substr(2));
    bool is_found = 0;

    for (int i = 0; i < pages.size(); i++)
    {
      if (pages[i]->number == num)
      {
	is_found = 1;
	pages[i]->r = 1;
	if (mode)
          pages[i]->m = 1;
        break;
      }
    }

    if (is_found == false)
    {
      page* pr = new page(num, 1, mode);
      if (pages.size() < PAGE_COUNT)
        pages.push_back(pr);
      else
      {
        int ind = last_r_ind % PAGE_COUNT;
        while (pages[ind]->r != 0)
        {
	  last_r_ind++;
	  ind = last_r_ind % PAGE_COUNT;
	}
        pages[ind] = pr;
	last_r_ind++;
	replace_cnt++;
      }
    }
    print_pages_clock(pages);
  }
  //cout << "Count of replaces: " << replace_cnt << endl;
}

int getNumberPageFromIndexArray(vector<int> inds)
{
  int index = uniform_rnd(0, inds.size() - 1);
  return inds[index];
}
    
void NRU_alg()
{
  vector<pair<int, page*>> pages;
  string str;
  int cnt = 0, replace_cnt = 0;  

  while (true)
  {
    getline(cin, str);
    if (str.empty())
      break;

    if (cnt % 5 == 0)
      pages = set_r_null(pages);
    cnt++;
    
    bool mode = str[0] -'0', is_found = false;
    int num = stoi(str.substr(2));
    for (auto it = pages.begin(); it != pages.end(); it++)
    {
      if (it->second->number == num)
      {        
        it->second->r = 1;
        if (mode)
          it->second->m = 1;
        it->second->set_type();
        it->first = it->second->type;
        is_found = true;
        break;
      }
    }
    
    if (is_found == false)
    {
      page* pg = new page(num, 1, mode);
      if (pages.size() < PAGE_COUNT)
      	pages.push_back(pair<int, page*>(pg->type, pg));
      else
      {
        for (int type = 0; type < 4; type++)
        {
          vector<int> curpages;          
          for (int i = 0; i < pages.size(); i++)
          {
            if (pages[i].first == type)
              curpages.push_back(i);
          }
          if (curpages.size() == 0)
            continue;

          int ind = getNumberPageFromIndexArray(curpages);
          pages[ind] = pair<int, page*>(pg->type, pg);
          replace_cnt++;
          break;
        }
      }     
    }
    print_pages_NRU(pages);
  }
  //cout << "Count of replaces: " << replace_cnt << endl;
}

int main(int argc, char *argv[])
{
  if (*argv[1] =='1')
    clock_alg();
  else
    NRU_alg();
  return 0;
}

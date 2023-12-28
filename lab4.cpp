#define PAGE_COUNT 8

#include <iostream>
#include <vector>
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

  int get_number() { return number; };
  bool get_r() { return r; };
  bool get_m() { return m; };
  int get_type() {return type; };

  void set_r(bool r) { this->r = r; };
  void set_m(bool m) { this->m = m; };
};

void print_pages(vector<page*> pages)
{  
  for (int i = 0; i < pages.size(); i++)
  {
    if (i < PAGE_COUNT - 1)
      cout << pages[i]->get_number() << " ";
      //cout  <<  pages[i]->get_number() << "(" << pages[i]->get_r() << ", " << pages[i]->get_m() << ")t:" << pages[i]->type << " ";
    else
      //cout <<  pages[i]->get_number() << "(" << pages[i]->get_r() << ", " << pages[i]->get_m() << ")t:" << pages[i]->type << " ";
      cout << pages[i]->get_number();
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

void drop_r(vector<page*> pages)
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
  int cnt = 0, cur_ind = 0;
  string str;
  vector<string> strs;

  while (true)
  {
    getline(cin, str);
    if (str.empty())
      break;
   // strs.push_back(str);
  //}
  //for (int i = 0; i < strs.size(); i++)
  //{
    /* Drop R */
    if (cnt % 5 == 0)
      drop_r(pages);
    cnt++;
    
    bool mode = str[0] -'0';
    int num = stoi(str.substr(2));
    bool find_flag = 0;

    /* Find page in pagesay */
    for (auto p : pages)
    {
      if (p->get_number() == num)
      {
        /*Set R */
	find_flag = 1;
        mode == 0 ? p->set_r(1) : p->set_m(1);
        break;
      }
    }

    if (!find_flag)
    {

      /* If page doesn't exist, add it */
      /* If vector has free cells, add it */
      /* Else check pointer element, move if needs, rewrite */
      page* pr = new page(num, (mode == 0 ? 1 : 0), (mode == 1 ? 1 : 0));
      if (pages.size() < PAGE_COUNT)
      {
        pages.push_back(pr);
      }
      else
      {

        while (pages[(cur_ind) % PAGE_COUNT]->get_r() != 0)
        {
	  cur_ind++;
        }
        pages[(cur_ind) % PAGE_COUNT] = pr;
	cur_ind++;;
      }
    }

    print_pages(pages);
  }
}

void NRU_alg()
{
  vector<page*> pages;
  int cnt = 0;
  string str;
  vector<string> strs;

  while (cin)//while (getline(cin, str))
  {
    getline(cin, str);
    if (str.empty()) {
      break;
    }
    strs.push_back(str);
  }
  for (auto data : strs)
  {
    if (cnt % 5 == 0)
      drop_r(pages);

    cnt++;
    /* Find page in pagesay */
    bool mode = data[0] -'0';
    int num = stoi(data.substr(2));
    bool find_flag = 0;

    for (auto p : pages)
    {
      if (p->get_number() == num)
      {
        /*Set R */
	find_flag = 1; 
        mode == 0 ? p->set_r(1) : p->set_m(1);
	p->set_type();
        break;
      }
      //p->set_type();
    }

    if (!find_flag)
    {
      page* pr = new page(num, (mode == 0 ? 1 : 0), (mode == 1 ? 1 : 0));
      //pr->set_type();
      if (pages.size() < PAGE_COUNT)
      {
        pages.push_back(pr);
      }
      else
      {
      	int ind = -1;
      	vector<page*> del_pages;
      	for (int i = 0; i < pages.size(); i++)
      	{
      	  if (pages[i]->type == 0)
      	    del_pages.push_back(pages[i]);
      	}
      	if (del_pages.size() != 0)
      	{
      	  ind = uniform_rnd(0, del_pages.size() - 1);
      	  for (int i = 0; i < pages.size(); i++)
      	  {
      	    if (pages[i] == del_pages[ind])
      	      pages[i] = pr;
      	  }
      	}
      	else
      	{
      	  for (int i = 0; i < pages.size(); i++)
      	  {
      	    if (pages[i]->type == 1)
      	      del_pages.push_back(pages[i]);
      	  }
      	  if (del_pages.size() != 0)
      	  {
      	    ind = uniform_rnd(0, del_pages.size() - 1);
      	    for (int i = 0; i < pages.size(); i++)
      	    {
      	      if (pages[i] == del_pages[ind])
      	        pages[i] = pr;
      	    }
      	  }
      	  else
      	  {
      	    for (int i = 0; i < pages.size(); i++)
      	    {
      	      if (pages[i]->type == 2)
      	        del_pages.push_back(pages[i]);
      	    }
      	    if (del_pages.size() != 0)
      	    {
      	      ind = uniform_rnd(0, del_pages.size() - 1);
      	      for (int i = 0; i < pages.size(); i++)
      	      {
      	        if (pages[i] == del_pages[ind])
      	          pages[i] = pr;
      	      }
      	    }
      	  }
      	}
     
	/*vector<int> fst, scd, thd, fth;
	for (int i = 0; i < pages.size(); i++)
	{
	  switch (pages[i]->get_type())
	  {
	  case 0:
	    fst.push_back(i);
	    break;
	  case 1:
	    scd.push_back(i);
	    break;
	  case 2:
	    thd.push_back(i);
	    break;
	  case 3:
	    fth.push_back(i);
	    break;
	  }
	}
	vector<page*>::iterator it = pages.begin();
	if (fst.size() != 0)
	{
	  int ind = uniform_rnd(0, fst.size() - 1);
	  it += fst[ind];
	  
	  pages.erase(it);
	}
	else if (scd.size() != 0)
	{
	  int ind = uniform_rnd(0, scd.size() - 1);
	  it += scd[ind];
	  /*cout << "Scd: ";
	  for (auto el : scd)
	  	cout << el << " ";
	  cout << "\nScd[ind]: " << scd[ind] << ", pages[scd[ind]]->number:" << pages[scd[ind]]->number << endl;
	  pages.erase(it);
	}

	else if (thd.size() != 0)
	{
	  int ind = uniform_rnd(0, thd.size() - 1);
	  it += thd[ind];
	  pages.erase(it);
	}
	pages.insert(it, pr);
	it = pages.begin();
	print_pages(pages);
	continue;*/
      }
    }
   
    print_pages(pages);
  }

}

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    if (*argv[1] =='1')
      clock_alg();
    else
      NRU_alg();
  }
  return 0;
}

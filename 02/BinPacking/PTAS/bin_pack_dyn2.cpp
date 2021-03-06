#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
#include <functional>
#define DBG(X)
#include "bin_pack_dyn2.hpp"

using namespace std;

namespace dyn2
{

static int A[1200][1200];
static int B[1200][1200];
static X C[1200][1200];


dyn2::dyn2(vector<double> S, vector<int> x, double capacity)
{
  this->S = S;
  this->x = x;
  this->capacity = capacity;
}


void dyn2::calcPath(X cur, X pop)
{
  X sol = {cur.a - pop.a, cur.b - pop.b};

  if (cur.a + cur.b == 0) 
  {
    return;
  }

  calcPath(sol, C[sol.a][sol.b]);
  
  bins.push_back(1.0 - (S[0] * pop.a + S[1] * pop.b));

  DBG(cout << pop.a << " " << pop.b << " " << endl;)
}

void dyn2::prepare_conf()
{
  for (int i = 0; i <= x[0]; i++)
    for (int j = 0; j <= x[1]; j++)
        {
          if (i + j  == 0) continue;
          if (S[0] * i + S[1] * j <= capacity)
          {
            A[i][j] = 1;
            C[i][j] = {0,0};
            CONF.push_back(make_tuple(i,j));
          }
        }
}


vector<double> dyn2::dp()
{
  prepare_conf();
  A[0][0] = 0;
  for (int i = 0; i <= x[0]; i++)
    for (int j = 0; j <= x[1]; j++)
        {
          int cur = 1 << 30;
          for (auto& c : CONF)
          {
            int x1 = get<0>(c), x2 = get<1>(c);
            if (i >= x1 && j >= x2)
            {
              if (cur > A[i - x1][j - x2] + 1)
              {
                C[i][j] = {x1, x2};
                cur = A[i - x1][j - x2] + 1;
              }
            }
          }
          if (cur < (1 << 30)) 
            A[i][j] = cur;
        }

          DBG(for (int c = 0; c < CONF.size(); c++)
          {
            int x1 = get<0>(CONF[c]);
            int x2 = get<1>(CONF[c]);
            
            cout << x1 << " " << x2 << " " << endl;
          })

  DBG(for (int i = 0; i <= x[0]; i++)
    for (int j = 0; j <= x[1]; j++)
  
          cout << i << " " << j << " " << A[i][j] << endl;
          
  cout << A[x[0]][x[1]] << endl;)

  X pop = C[x[0]][x[1]];
  X cur = {x[0], x[1]};

  DBG(cout << "path" << endl;)
  calcPath(cur, {0,0});
  DBG(cout << "path end" << endl;)

  DBG(cout << cur.a << " " << cur.b << " " << endl;
  cout << pop.a << " " << pop.b << " " << endl;)

  while (1)
  { 
    X sol = {cur.a - pop.a, cur.b - pop.b};
    DBG(cout << sol.a << " " << sol.b << " " << endl;)
    if (sol.a + sol.b == 0) break;
    
    pop = C[sol.a][sol.b];
    cur = sol;
  }
  
  bins.pop_back();

  for (int i = 0; i < bins.size(); i++)
  {
    cout << "bin " << i << " " << bins[i] << " ";
  }
  return bins;
}
}


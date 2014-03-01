
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  using namespace std;
  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int MAX_N = 150 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int L[MAX_N];
    Int D[MAX_N][MAX_N];
  };
  
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( ! ( s >> in.N ) ) return false;
      for ( auto i = 0; i < in.N; ++ i ) {
        s >> in.L[i];
        for ( auto j = 0; j < in.L[i]; ++ j ) {
          s >> in.D[i][j];
        }
      }
      return s;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.result << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}

    bool visited[MAX_N][2];
    bool used[MAX_N];
    
    bool solve() {
      out.result = count();
      return true;
    }

    Int count() {
      Int res = 0;
      for ( auto i = 0; i < in.N; ++ i ) {
        init_visited();
        fill(used, used + MAX_N, false);
        rec(i, 0);
        res = max(res, (Int)std::count(used, used + MAX_N, true));
      }
      return res;
    }

    void rec( const Int& cur, const Int& t ) {
      if ( visited[cur][t] ) return;
      visited[cur][t] = true;
      used[cur] = true;
      cout << "@rec: cur = " << cur << endl;
      for ( auto i = 0; i < in.L[cur]; ++ i ) {
        Int to = in.D[cur][i];
        cout << cur << " -> " << to << endl;
        rec(to, 1);
      }
    }

    void init_visited() {
      for ( auto i = 0; i < MAX_N; ++ i ) {
        for ( auto j = 0; j < 3; ++ j ) {
          visited[i][j] = false;
        }
      }
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>


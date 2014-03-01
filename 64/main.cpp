
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
  const Int MAX_N = 10 + 1;
  const Int MAX_L = 50 + 1;
  const Int MAX_M = 10000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int L[MAX_N];
    Double X[MAX_N][MAX_L];
    Double Y[MAX_N][MAX_L];
    Double AX[MAX_M];
    Double AY[MAX_M];
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
      if ( ! ( s >> in.N >> in.M ) ) return false;
      for ( auto i = 0; i < in.N; ++ i ) {
        s >> in.L[i];
        for ( auto j = 0; j < in.L[i]; ++ j ) {
          s >> in.X[i][j] >> in.Y[i][j];
        }
      }
      for ( auto i = 0; i < in.M; ++ i )
        if ( ! ( s >> in.AX[i] >> in.AY[i] ) ) return false;
      return true;
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
    
    bool solve() {
      out.result = count();
      return true;
    }

    Int count() {
      Int res = 0;
      for ( auto i = 0; i < in.M; ++ i ) {
        if ( check(i) ) res ++;
      }
      return res;
    }

    bool check( const Int& a_id ) {
      for ( auto i = 0; i < in.N; ++ i ) {
        if ( check(a_id, i) ) return true;
      }
      return false;
    }

    bool check( const Int& a_id, const Int& l_id ) {
      const Double& ax = in.AX[a_id];
      const Double& ay = in.AY[a_id];
      const Int& l = in.L[l_id];
      for ( auto i = 0; i < l; ++ i ) {
        Double x[3];
        Double y[3];
        x[0] = in.X[l_id][0];
        y[0] = in.Y[l_id][0];
        for ( auto j = 1; j < 3; ++ j ) {
          x[j] = in.X[l_id][(i + j) % l];
          y[j] = in.Y[l_id][(i + j) % l];
        }
        Double c[3];
        for ( auto j = 0; j < 3; ++ j ) {
          Double vx01 = x[(j + 1) % 3] - x[j];
          Double vy01 = y[(j + 1) % 3] - y[j];
          Double vxp = ax - x[j];
          Double vyp = ay - y[j];
          c[j] = get_cross(vx01, vy01, vxp, vyp);
        }
        if ( check_less_than_equal(c[0], 0.0) && check_less_than_equal(c[1], 0.0) && check_less_than_equal(c[2], 0.0) ) return true;
        if ( check_less_than_equal(0.0, c[0]) && check_less_than_equal(0.0, c[1]) && check_less_than_equal(0.0, c[2]) ) return true;
      }
      return false;
    }

    bool check_less_than_equal( const Double& a, const Double& b ) {
      if ( a < b ) return true;
      return abs(a - b) < 1e-9;
    }

    Double get_cross( const Double& ax, const Double& ay, const Double& bx, const Double& by ) {
      return ax * by - ay * bx;
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


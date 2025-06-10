/*
  <timer>
    - 時間を測定する

    [実装/関数]
        - timer the_timer : インスタンスを作成
        - void start : 計測開始
        - void stop : 計測の一時中止
        - void restart : 今までの計測時間を0として計測開始
        - double time : 今まで計測していた時間の総和を[s]単位で返す

    [計算時間]
        - 
    
    [備考]
        - https://atcoder.jp/contests/ahc010/submissions/31233938
    
    [参照]
        - 

    [verified at]
        - 
        
*/

#include <mach/mach_time.h>  
#include <cstdint>     

struct timer {
    double t = 0.0;
    double lastStop = 0.0;
    bool stopped = false;
    timer() {
      restart();
    }
    inline void restart() {
      t = now();
      stopped = false;
    }
    inline void start() {
      if (stopped) {
        t += now() - lastStop;
        stopped = false;
      }
    }
    inline void stop() {
      if (!stopped) {
        lastStop = now();
        stopped = true;
      }
    }
    inline double time() {
      if (stopped) return lastStop - t;
      else return now() - t;
    }
    inline double now() {
        unsigned long long l, h;
        __asm__ ("rdtsc" : "=a"(l), "=d"(h));
        #ifdef LOCAL
        return (double)(l | h << 32) * 2.857142857142857e-10; // 1 / 3.5e9, for local (Ryzen 9 3950X)
        #else
        //return (double)(l | h << 32) * 3.5714285714285715e-10; // 1 / 2.8e9, for AWS EC2 C3 (Xeon E5-2680 v2)
        //return (double)(l | h << 32) * 3.4482758620689656e-10; // 1 / 2.9e9, for AWS EC2 C4 (Xeon E5-2666 v3)
        return (double)(l | h << 32) * 3.333333333333333e-10; // 1 / 3.0e9, for AWS EC2 C5 (Xeon Platinum 8124M / Xeon Platinum 8275CL)
        #endif
    }
};
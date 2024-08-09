//time//
 double time=0.0;
    clock_t start = clock();
    clock_t end = clock();
 time= static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
 cout<<(double)(end - start) / CLOCKS_PER_SEC << endl;

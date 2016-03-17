# Eigen 3
Eigen 3 is a lightweight C++ template library for vector and matrix math, a.k.a. linear algebra.

## Ubuntu
```
sudo apt-get install libeigen3-dev
```

## Mac OSX
```
brew install eigen
```

# GNUPLOT

## Ubuntu
```
sudo apt-get install gnuplot-qt
```

## Mac OSX
```
brew uninstall gnuplot
brew install gnuplot --with-qt
```

# GNUPLOT_I (c++)
http://code.google.com/p/gnuplot-cpp

# GNUPLOT_I (c origin but not maintain)
GNUPLOT_I is a C library which allows a C or C++ program to pass data to GNUPLOT for immediate plotting, by Nicholas Devillard.  
http://people.sc.fsu.edu/~jburkardt/c_src/gnuplot_i/gnuplot_i.html

# Reference
http://wildpie.hatenablog.com/entry/20120712  
一個資料集合, 共14個點如下  
x = {77.6, 114.9, 141.1, 190.8, 239.9, 289.0, 332.8, 378.4, 434.8, 477.3, 536.8, 593.1, 689.1, 760.0}  
y = {10.07, 14.73, 17.94, 23.93, 29.61, 35.18, 40.02, 44.82, 50.76, 55.05, 61.01, 66.40, 75.47, 81.78}  
繪製出來的曲線趨近於 y=beta1(1-exp(-beta2*x))  
設定beta1, beta2初始值為500, 0.0001  

欲求出最接近這些點的曲線  
可利用LM演算法求得beta1, beta2的係數  

F[i] = (beta1(1-exp(-beta2*x[i]))-y[i])  
盡可能的讓函數F差異接近0  

LM演算法需要填Jacobian matrix  
對F的beta1做偏微分  
= (1-exp(-beta2*x))  
對F的beta2做偏微分  
= beta1*x*exp(-beta2*x) (網站上的公式是錯的 但code是對的  


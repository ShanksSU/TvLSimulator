# TvLSimulator
[![C++](https://img.shields.io/badge/support-C%2B%2B11%20or%20later-blue?style=flat&logo=cplusplus)](https://github.com/topics/cpp) 
[![CMake](https://img.shields.io/badge/support-v2.8.12%20or%20later-blue?style=flat&logo=cmake)](https://cmake.org/) 
## 介紹

在2022年，Alessandro Pluchino、Alessio Emanuele Biondo和Andrea Rapisarda因其在經濟學領域的研究而獲得了Ig Nobel獎，這是一個幽默諾貝爾獎。

他們的論文在數學上解釋了為什麼成功通常更傾向於幸運而非最有天賦(個人能力)的個體而受到肯定(Improbable Research，2022)。

通過在“天賦 vs. 運氣”辯論的背景下進行模擬，該論文聲稱運氣比天賦更具重要性。這個輕鬆詼諧的肯定揭示了影響成功的非傳統因素，並引發了人們對運氣和個人能力相互作用的思考。

模擬的條件如下：
+ 構建agent-based model
+ 模擬一個世界，其中1000人遇到500個事件
+ 天賦為正態分佈，範圍在0和1之間
+ 資產起始值均為10
+ 進行80次迭代，年齡範圍在20到60之間
+ 代理人遇到的事件有50%的機率是幸運或是不幸
+ + 幸運事件根據天賦決定是否使資產翻倍
+ + 不幸事件無視天賦資產减半

## 項目結構
```
.
├── CMakeLists.txt
├── lib
│   ├── constants.h
│   ├── simulation.cpp
│   └── simulation.h
└── main.cpp
```

## 目標

構建agent-based model使用C++實現模型R語言做視覺化呈現與分析。

## 參考資料

<b>執行環境：</b><br>
gcc version 11.3.0<br>
g++ version 11.3.0<br>
R version 4.2.3<br>
<br>
<b>參考：</b><br>
Pluchino, A., Biondo, A. E., & Rapisarda, A.(2018). Talent vs. Luck: The Role of Randomness in Success and Failure. <i>Advances in Complex Systems</i>. 
https://arxiv.org/abs/1802.07068

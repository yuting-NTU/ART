### 目的
為了檢察PCB瑕疵，我們需要用X-ray重建三維的錫球以檢察內部構造  

### ART技術
ART(Algebraic Reconstruction Technique)   
此例子是模擬重建過程  
將1D重建為2D  

### 問題
* 重建後如何決定原本的heigh?  
* 展示圖的時候要  
```cpp
cv::normalize(results, results, 0, 255, NORM_MINMAX, CV_8UC1);
```
* 計算圖的時候要
```cpp
cv::normalize(newArray, newArray, 0, 1, NORM_MINMAX, CV_32FC1);
```

### 程式環境
* 使用C++
* 使用vs2022與vcpkg

### 原理
<img src="https://user-images.githubusercontent.com/66452317/153203523-7612f902-4ffa-425c-bf6f-de702aa79237.png" width=600/>

![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/rotate.gif)
![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/addCol.gif)  
![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/result.png)

在旋轉時，超出的範圍會被切掉  
![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/oriImg2.png)
![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/rotate2.gif)  
復原也只能復原沒被切掉的部分    
![image](https://github.com/YuTing-Fang1999/ART/blob/main/resource/result2.png)

### 加法與乘法的比較
![image](https://user-images.githubusercontent.com/66452317/154830277-aaf11818-4a72-4573-80af-e65caab7c050.png)

### 我的改良(non-negative additive)
![image](https://user-images.githubusercontent.com/66452317/154830261-20bbceff-9718-44a3-9891-7db8418a89b1.png)
non-negative additive結合了加法與乘法的優點  
詳細內容請看ppt  


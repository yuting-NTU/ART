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

![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/rotate.gif)
![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/addCol.gif)  
![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/result.png)

在旋轉時，超出的範圍會被切掉  
![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/oriImg2.png)
![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/rotate2.gif)  
復原也只能復原沒被切掉的部分    
![image](https://github.com/YuTing-Fang1999/NTU-Lab/blob/main/HomeWork/ART/resource/result2.png)

### 公式
#### addtive
![image](https://user-images.githubusercontent.com/66452317/153180249-1c422d2a-2f52-443b-a226-9ff1c2e620c6.png)
#### Multiplicative  
see the ppt  

clc;
data1 = textread('1_linear.txt')/255;
data2 = textread('Newton_linear.txt')/255;
data3 = textread('Newton_cubic.txt')/255;
figure('NumberTitle', 'off', 'Name', '原图');
imshow(data1);
figure('NumberTitle', 'off', 'Name', '线性插值');
imshow(data2);
 figure('NumberTitle', 'off', 'Name', '三次插值');
imshow(data3);
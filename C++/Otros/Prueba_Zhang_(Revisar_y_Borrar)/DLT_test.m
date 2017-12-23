% Direct Linear Transformation
cam = imread('D:\Facultad\Proyecto\SL_Tests\Calibration\Test_Zhang\Capturas\cap0.png');
pc = readPoints(cam);

save('cam0.mat', 'pc');
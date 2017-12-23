%Manual Loader

%%

% cam = imread('Cajas\c4_0.jpeg');
% c4_0 = readPoints(cam);
% 
% save('c4_0.mat', 'c4_0');
% clf;
% 
% cam = imread('Cajas\c4_1.jpeg');
% c4_1 = readPoints(cam);
% 
% save('c4_1.mat', 'c4_1');
% clf;
% 
% cam = imread('Cajas\c4_2.jpeg');
% c4_2 = readPoints(cam);
% 
% save('c4_2.mat', 'c4_2');
% clf;
% 
% cam = imread('Cajas\c4_3.jpeg');
% c4_3 = readPoints(cam);
% 
% save('c4_3.mat', 'c4_3');
% clf;

%%

c1 = imread('Cajas\c1_4.jpeg');
c2 = imread('Cajas\c2_4.jpeg');
c3 = imread('Cajas\c3_4.jpeg');
c4 = imread('Cajas\c4_4.jpeg');

% figure(1)
% image(c1)
% 
figure(2)
image(c2)

figure(3)
image(c3)
% 
% figure(4)
% image(c4)

figure(5)
c2_3_obj = readPoints(c2);
c3_2_obj = readPoints(c3);

% c3_1_obj = readPoints(c3);
% c1_3_obj = readPoints(c1);
% 
% c1_4_obj = readPoints(c1);
% c4_1_obj = readPoints(c4);

save('c2_3_obj_2.mat', 'c2_3_obj');
save('c3_2_obj_2.mat', 'c3_2_obj');

% save('c3_1_obj.mat', 'c3_1_obj');
% save('c1_3_obj.mat', 'c1_3_obj');
% 
% save('c1_4_obj.mat', 'c1_4_obj');
% save('c4_1_obj.mat', 'c4_1_obj');

clf;

cam = imread('D:\Facultad\Proyecto\SL_Tests\Calibration\Test_Zhang\Capturas\cap0_v2.jpeg');
cam = rgb2gray(cam);
% Compute edge image
BW = edge(cam,'canny');

% Compute Hough transform
[H theta rho] = hough(BW);

% Find local maxima of Hough transform
numpeaks = 19;
thresh = ceil(0.1 * max(H(:)));
P = houghpeaks(H,numpeaks,'threshold',thresh);

% Extract image lines
lines = houghlines(BW,theta,rho,P,'FillGap',50,'MinLength',60);

%--------------------------------------------------------------------------
% Display results
%--------------------------------------------------------------------------
% Original image
figure; imshow(cam);

% Edge image
figure; imshow(BW);

% Hough transform
figure; image(theta,rho,imadjust(mat2gray(H)),'CDataMapping','scaled');
hold on; colormap(gray(256));
plot(theta(P(:,2)),rho(P(:,1)),'o','color','r');

% Detected lines
figure; imshow(cam); hold on; n = size(cam,2);
for k = 1:length(lines)
    % Overlay kth line
    x = [lines(k).point1(1) lines(k).point2(1)];
    y = [lines(k).point1(2) lines(k).point2(2)];
    line = @(z) ((y(2) - y(1)) / (x(2) - x(1))) * (z - x(1)) + y(1);
    plot([1 n],line([1 n]),'Color','r');
end
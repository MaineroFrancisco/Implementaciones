% EIGHT POINT ALGORIMTH
clear;
res_x = 640;
res_y = 480;

% cam_1 = textread('D:\Facultad\Proyecto\SL_Tests\Calibration\Test_Zhang\cam_1.txt','%d',8);
% % cam_1(2:2:8) = -1*cam_1(2:2:8) + res_y; 
% cam_1 = [
%     cam_1(1), cam_1(2), 1;
%     cam_1(3), cam_1(4), 1;
%     cam_1(5), cam_1(6), 1;
%     cam_1(7), cam_1(8), 1;
%     ];

cam_2 = textread('D:\Facultad\Proyecto\SL_Tests\Calibration\Test_Zhang\cam_2.txt','%d',16);
% cam_2(2:2:8) = -1*cam_2(2:2:8) + res_y;
cam_2 = [
    cam_2(1), cam_2(2), 1;
    cam_2(3), cam_2(4), 1;
    cam_2(5), cam_2(6), 1;
    cam_2(7), cam_2(8), 1;
    cam_2(9), cam_2(10), 1;
    cam_2(11), cam_2(12), 1;
    cam_2(13), cam_2(14), 1;
    cam_2(15), cam_2(16), 1;
    ];

cam_3 = textread('D:\Facultad\Proyecto\SL_Tests\Calibration\Test_Zhang\cam_3.txt','%d',16);
% cam_3(2:2:8) = -1*cam_3(2:2:8) + res_y;
cam_3 = [
    cam_3(1), cam_3(2), 1;
    cam_3(3), cam_3(4), 1;
    cam_3(5), cam_3(6), 1;
    cam_3(7), cam_3(8), 1;
    cam_3(9), cam_3(10), 1;
    cam_3(11), cam_3(12), 1;
    cam_3(13), cam_3(14), 1;
    cam_3(15), cam_3(16), 1;
    ];


%%
A = zeros(8,9);
for k=1:8
   
    p1 = cam_2(k,:);
    p2 = cam_3(k,:);
    
    % (1 fila,9 columnas)
    A(k,:) = [ 
        %  px'*px  ,    px'*py  ,  px' ,   py'*px   ,    py'*py  ,  py' ,  px  ,  py  ,  1
        p2(1)*p1(1), p2(1)*p1(2), p2(1), p2(2)*p1(1), p2(2)*p1(2), p2(2), p1(1), p1(2),  1
    ];

end

[U,S,V] = svd(A);

v = V(:,9)';

Q = -1*[
    v(1:3);
    v(4:6);
    v(7:9)
];

% [U, S, V] = svd(Q);

QtQ = Q'*Q;
tq = sqrt((1/2)*trace(QtQ));

for k = 1:size(Q,1)
    Q(k,:) = Q(k,:)/tq;
end

%%
QtQ = Q'*Q;

% Traslacion
% Los signos deben elegirse arbitrariamente, con posterioridad
t = -1*[
  sqrt(abs(QtQ(1,1)-1));
  sqrt(abs(QtQ(2,2)-1));
  sqrt(abs(QtQ(3,3)-1))
];

% Rotacion

Wa = cross(Q(1,:),t);
Wb = cross(Q(2,:),t);
Wc = cross(Q(3,:),t);

R = [
    Wa + cross(Wb,Wc);
    Wb + cross(Wc,Wa);
    Wc + cross(Wa,Wb);
];

%% Computo X3

k=1;

% Esta es la matriiz que transforma los puntos (X,Y,Z,1) del sistema de
% coordenadas de la camara 1, en los (X, Y, Z, 1) del sistema de
% coordenadas de la camara 2.
%
%       P2 = [R | -R*t] P1
%                Mp
err = 0;
while k <=size(cam_2,1)
    %
    
    x3 = ((R(1,:) - cam_3(k,1)*R(3,:))*t) / ((R(1,:) - cam_3(k,1)*R(3,:))*cam_2(k,:)')
    
    P(k,:) = x3 * cam_2(k,:)';
    P_p = R*(P(k,:)' - t);
    
    %
    
    x3_p = R(3,:)*(P(k,:)' - t)
    
    Fp(k,:) = P_p';
    
    err = err + P_p'*Q*P(k,:)'.^2;

    %
    
    k= k+1;
end

%%
figure(1)
clf
hold on
grid on
axis equal on

Mp = [R t; 0 0 0 1];
Imp = inv(Mp);
%
% scatter3(p_reales(:,1) ,p_reales(:,2), p_reales(:,3), 'o', 'black')

%
o = [0 0 0 1]';
M_or = [
    1 0 0 0;
    0 1 0 0;
    0 0 1 0;
    0 0 0 1
    ];
draw_coordinate_system(o, M_or, 'o', 'blue' )

%
draw_coordinate_system(Imp*o, Imp*M_or, 'o', 'blue' )
% draw_coordinate_system(E2*o', E2*M_or, 'o', 'blue' )
% 
% Mf = E1*Mp;
% draw_coordinate_system(Mf*o', Mf*M_or, 'o', 'blue' )


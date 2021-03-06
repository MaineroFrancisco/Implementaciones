 % Zhang Complete Test
clear;
% 
% load('cam0.mat');
% p0 = [pc' ones(size(pc',1),1)];
% load('cam1.mat');
% p1 = [pc' ones(size(pc',1),1)];
% load('cam2.mat');
% p2 = [pc' ones(size(pc',1),1)];
% load('cam3.mat');
% p3 = [pc' ones(size(pc',1),1)];
% load('cam4.mat');
% p4 = [pc' ones(size(pc',1),1)];
% load('cam5.mat');
% p5 = [pc' ones(size(pc',1),1)];
% load('cam6.mat');
% p6 = [pc' ones(size(pc',1),1)];
% load('cam7.mat');
% p7 = [pc' ones(size(pc',1),1)];
% 
% % load('cam02.mat');
% % p0 = [pc0' ones(size(pc0',1),1)];
% % load('cam12.mat');
% % p4 = [pc1' ones(size(pc1',1),1)];   %% ESTABA MAL CARGADO CORREGIR
% % load('cam22.mat');
% % p2 = [pc2' ones(size(pc2',1),1)];
% % load('cam42.mat');
% % p1 = [pc4' ones(size(pc4',1),1)];


% % load('cam03.mat');
% % p0 = [pc0' ones(size(pc0',1),1)];
% % load('cam13.mat');
% % p1 = [pc1' ones(size(pc1',1),1)];
% % load('cam23.mat');
% % p2 = [pc2' ones(size(pc2',1),1)];
% % load('cam33.mat');
% % p3 = [pc3' ones(size(pc3',1),1)];
 
% % load('cam04.mat');
% % p0 = [pc0' ones(size(pc0',1),1)];
% % load('cam14.mat');
% % p1 = [pc1' ones(size(pc1',1),1)];
% % load('cam24.mat');
% % p2 = [pc2' ones(size(pc2',1),1)];
% % load('cam34.mat');
% % p3 = [pc3' ones(size(pc3',1),1)];

% load('cam_c11.mat');
% p0 = [c1' ones(size(c1',1),1)];
% load('cam_c12.mat');
% p1 = [c1' ones(size(c1',1),1)];   
% load('cam_c13.mat');
% p2 = [c1' ones(size(c1',1),1)];

% % load('cam_c21.mat');
% % p0 = [c2' ones(size(c2',1),1)];
% % load('cam_c22.mat');
% % p1 = [c2' ones(size(c2',1),1)]; 
% % load('cam_c23.mat');
% % p2 = [c2' ones(size(c2',1),1)];

load('c11_v2.mat');
p0 = [c1' ones(size(c1',1),1)];
load('c12_v2.mat');
p1 = [c1' ones(size(c1',1),1)];   
load('c13_v2.mat');
p2 = [c1' ones(size(c1',1),1)];

% load('c21_v2.mat');
% p0 = [c2' ones(size(c2',1),1)];
% load('c22_v2.mat');
% p1 = [c2' ones(size(c2',1),1)];
% load('c23_v2.mat');
% p2 = [c2' ones(size(c2',1),1)];

% DEBERIAN SER (X,Y,Z,W)... pero como Z=0... uso solo (X,Y,W)
p_reales = [
    0 0 1;
    0 1 1;
%     0 2 1;
%     0 3 1;
    1 0 1;
    1 1 1;
%     1 2 1;
%     1 3 1;
%     2 0 1;
%     2 1 1;
%     2 2 1
%     2 3 1;
%     3 0 1;
%     3 1 1;
%     3 2 1;
%     3 3 1
];

% p_reales = [
%     0 0 1;
%     0 10 1;
%     0 20 1;
%     0 30 1;
%     10 0 1;
%     10 10 1;
%     10 20 1;
%     10 30 1;
%     20 0 1;
%     20 10 1;
%     20 20 1;
%     20 30 1;
%     30 0 1;
%     30 10 1;
%     30 20 1;
%     30 30 1
% ];
%% Homography Computation
%Closed Form Solution
% z = 0

% Homography Camera 0
H1 = estimateHomography(p_reales,p0);

% Homography Camera 1
H2 = estimateHomography(p_reales,p1);

% Homography Camera 2
H3 = estimateHomography(p_reales,p2);

%%
V = zeros(6,6);

% Camara 1
v12_c1 = vij(H1,1,2);
v11_c1 = vij(H1,1,1);
v22_c1 = vij(H1,2,2);

V(1,:) = v12_c1;
V(2,:) = v11_c1 - v22_c1;

% Camara 2
v12_c2 = vij(H2,1,2);
v11_c2 = vij(H2,1,1);
v22_c2 = vij(H2,2,2);

V(3,:) = v12_c2;
V(4,:) = v11_c2 - v22_c2;

% Camara 3
v12_c3 = vij(H3,1,2);
v11_c3 = vij(H3,1,1);
v22_c3 = vij(H3,2,2);

V(5,:) = v12_c3;
% V(5,:) = [0 1 0 0 0 0];
V(6,:) = v11_c3 - v22_c3;

%%
[U,S,Vt] = svd(V);

b = Vt(:,size(Vt,2));

if b(1) < 0 || b(3) < 0 || b(6) < 0
    b = -b;
end

w = b(1)*b(3)*b(6) - b(2)*b(2)*b(6) - b(1)*b(5)*b(5) + 2*b(2)*b(4)*b(5) - b(3)*b(4)*b(4);
d = b(1)*b(3) - b(2)*b(2);

% alpha = sqrt(abs(1/b(1)));
% beta = sqrt(abs(1/b(3)));

alpha = sqrt(abs(w/(d*b(1))));
beta = sqrt(abs((w/(d*d))*b(1)));

gamma = sqrt(w/(d*d*b(1)))*b(2);
% gamma = 0;

u0 = (b(2)*b(5) - b(3)*b(4))/d;
v0 = (b(2)*b(4) - b(1)*b(5))/d;

% % u0 = 320;
% % v0 = 240;

% v0 = (B(1,2)*B(1,3) - B(1,1)*B(2,3))/(B(1,1)*B(2,2) - B(1,2)*B(1,2));
% v0 = -240;
% lambda = B(3,3) - (B(1,3)*B(1,3) + v0 * (B(1,2)*B(1,3) - B(1,1)*B(2,3)))/B(1,1);

% gamma = 0;   %% por definicion del problema (solo 2 fotos)
% gamma = -B(1,2)*alpha*alpha*beta/lambda;
% u0 = (gamma*v0/alpha) - B(1,2)*alpha*alpha/lambda;
% u0 = -320; 

% Intrinsic Matrix

Im = [
  alpha, gamma, u0;
      0,  beta, v0;
      0,     0,  1
];


%% Extrinsic

% Camara 1
[R1 t1] = getExtrinsic(H1,Im);
Em1 = [R1 t1];

% Camara 2
[R2 t2] = getExtrinsic(H2,Im);
Em2 = [R2 t2];

% Camara 3
[R3 t3] = getExtrinsic(H3,Im);
Em3 = [R3 t3];

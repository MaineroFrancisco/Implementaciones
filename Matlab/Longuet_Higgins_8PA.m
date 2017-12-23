clear;

loader;

%% Caja_Cubo
% load('c11_v2_obj.mat');
% load('Im_c1_v2.mat')
% Im1 = Im;
% 
% % Im1 = [1 0 0; 0 1 0; 0 0 1];
% % c1_1 = c1;
% 
% c1 = [c1' ones(size(c1',1),1)];
% 
% c1_1 = inv(Im1)*c1';
% c1_1 = c1_1';
% 
% load('c21_v2_obj.mat');
% 
% load('Im_c2_v2.mat')
% Im2 = Im;
% 
% % Im2 = [1 0 0; 0 1 0; 0 0 1];
% % c2_1 = c2;
% 
% c2 = [c2' ones(size(c2',1),1)];
% 
% c2_1 = inv(Im2)*c2';
% c2_1 = c2_1';

%% Cajas
Im1 = Im_1;

% Im1 = [1 0 0; 0 1 0; 0 0 1];
% c1_1 = c1;

c1 = [c1_3_obj' ones(size(c1_3_obj',1),1)];

c1_1 = inv(Im1)*c1';
c1_1 = c1_1';


Im2 = Im_3;

% Im2 = [1 0 0; 0 1 0; 0 0 1];
% c2_1 = c2;

c2 = [c3_1_obj' ones(size(c3_1_obj',1),1)];

c2_1 = inv(Im2)*c2';
c2_1 = c2_1';


%%

% Formo la matriz para resolver el Sistema de Ecuaciones Lineal Homogeneo

N = size(c1_1,1);
Na = getNormMatrix(c1_1);
Nb = getNormMatrix(c2_1);
% Na = [1 0 0; 0 1 0; 0 0 1];
% Nb = [1 0 0; 0 1 0; 0 0 1];

A = zeros(size(c1_1,1),9);
for j=1:N

    k = 2*j;

    %Normalizar
    p1 = Na * c1_1(j,:)';
%     p1 = c1_1(j,:);

    if p1(3)~=0
        p1 = p1/p1(3);
    end

    p2 = Nb * c2_1(j,:)';
%     p2 = c2_1(j,:);
    
    if p2(3)~=0
        p2 = p2/p2(3);
    end

    % (1 fila,9 columnas)
    A(k,:) = [ 
        %  px'*px  ,    px'*py  ,  px' ,   py'*px   ,    py'*py  ,  py' ,  px  ,  py  ,  1
        p2(1)*p1(1), p2(1)*p1(2), p2(1), p2(2)*p1(1), p2(2)*p1(2), p2(2), p1(1), p1(2),  1
    ];

end

%%
% Resuelvo el sistema:  A*e = 0 -> Uso SVD... REVISAR
[U,S,V] = svd(A, 0);
S = diag(S);
     
nullspace_dimension = sum(S < eps * S(1) * 1e3);
if nullspace_dimension > 1
  fprintf('Nullspace is a bit roomy...');
end

v = V(:,size(V,2));

Q = [
    v(1:3)';
    v(4:6)';
    v(7:9)'
];

% Q = inv(Nb)*Q*Na;
% Q = Q/Q(3,3);

% Q=-Q;

%% Resolviendo Rotacion y Traslacion
QtQ = Q'*Q;

norma = sqrt((1/2)*trace(QtQ));

Q = Q/(norma);

QtQ = Q'*Q;

% Traslacion
% Los signos deben elegirse arbitrariamente, con posterioridad
t = [
  sqrt(abs(QtQ(1,1)-1));
  sqrt(abs(QtQ(2,2)-1));
  sqrt(abs(QtQ(3,3)-1))
];

% t=-t;

% t2 = sqrt(abs(QtQ(1,2)*QtQ(2,3)/QtQ(1,3)));
% t3 = QtQ(2,3) / t2;
% t1 = QtQ(1,2)/t2;
% 
% t = [t1 t2 t3]';

% Rotacion

Wa = cross(Q(1,:),t);
Wb = cross(Q(2,:),t);
Wc = cross(Q(3,:),t);

R = [
    Wa + cross(Wb,Wc);
    Wb + cross(Wc,Wa);
    Wc + cross(Wa,Wb);
];

k=1;
err = 0;
while k <=size(c1_1,1)
    %
    
    x3 = ((R(1,:) - c2_1(k,1)*R(3,:))*t) / ((R(1,:) - c2_1(k,1)*R(3,:))*c1_1(k,:)');
    
    P(k,:) = x3 * c1_1(k,:);
    P_p = R*(P(k,:)' - t);
    
    %
    
    x3_p = R(3,:)*(P(k,3)' - t);
    
    Fp(k,:) = P_p';
    
    err = err + P_p'*Q*P(k,:)' * P_p'*Q*P(k,:)';

    %
    
    k = k+1;
end



%% Computo X3

k=1;
% Esta es la matriiz que transforma los puntos (X,Y,Z,1) del sistema de
% coordenadas de la camara 1, en los (X, Y, Z, 1) del sistema de
% coordenadas de la camara 2.
%
%       P2 = [R | -R*t] P1
%                Mp
Mp = [R -R*t;
    0 0 0 1];

% Invertrlo es solo para verlo desde el punto de vista de la Camara 1, 
%   Mp describe la transformacion para pasar de la camara 1 a la 2
%   Para verlo desde la perspectiva de la camara 1 (traer de la camara 2 a 
%   la 1) hace falta invertir
% Mp = inv(Mp);

%% Proyeccion a 1 Imagen:

M_or = [
    1, 0, 0, 0;
    0, 1, 0, 0;
    0, 0, 1, 0;
    0, 0, 0, 1
];

% Origen del SC del mundo
o = [0, 0, 0, 1];

%%
figure(1)
clf
hold on
grid on
axis equal on

% %
draw_coordinate_system(o, M_or, 'o', 'blue' )
% scatter3(c1_1(:,1),c1_1(:,2),c1_1(:,3),'x','black')
% % scatter3(P(:,1),P(:,2),P(:,3),'x','black')
% 
% %
draw_coordinate_system(inv(Mp)*o', inv(Mp)*M_or, 'o', 'blue' )
% c2_2 = inv(Mp)*[c2_1 ones(size(c2_1,1),1)]';
% c2_2 = c2_2';
% scatter3(c2_2(:,1),c2_2(:,2),c2_2(:,3),'+','magenta')
% % Fp2 = inv(Mp)*[Fp ones(size(Fp,1),1)]';
% % Fp2 = Fp2';
% % scatter3(Fp2(:,1),Fp2(:,2),Fp2(:,3),'o','red')
triangulation_2(Im1,Im2,M_or(1:3,:), Mp(1:3,:),c1,c2,'o','red',1)
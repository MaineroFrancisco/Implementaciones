%% Paper: "SceneReconstruction.pdf" Longuet-Higgins
clear;
%% Puntos en el espacio tridimensional Real

p_reales = [
    0, 0, 0;
    0, 1, 0;
    0, 2, 0;
    1, 0, 0.2;
    1, 1, 0.23;
    1, 2, 0.2;
    2, 0, 0.1;
    2, 1, 0.2;
    2, 2, 0.1
];

% Matrix de puntos 2D para la imagen de la camara 1
p = zeros(size(p_reales,1),2);

% Matrix de puntos 2D para la imagen de la camara 2
p_p = zeros(size(p_reales,1),2);

%% Proyeccion a 1 Imagen:

M_or = [
    1, 0, 0, 0;
    0, 1, 0, 0;
    0, 0, 1, 0;
    0, 0, 0, 1
];

% Origen del SC del mundo
o = [0, 0, 0, 1];
 
%% Camera 1 - Informacion:

    %% Rotation Matrix
    
    angle_x_1 = 130;
    angle_y_1 = 40;
    angle_z_1 = 0;
    
    %% Translation
    %     X  Y  Z
    t1 = [-1, 4, 2]';
    
%% Aplicar proyeccion con respecto a la camara 1
    % Distancia Focal Camara 1
    f1 = 1;
    
    % Matriz proyectiva
    [I1, W1, E1] = camera_matrix(angle_x_1, angle_y_1, angle_z_1, t1, f1);
    
    % Var. Aux. puntos proyectados
    p_proy_1 = zeros(size(p_reales,1),3);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE1 = inv(E1);
    for k=1:size(p_reales(:,1))
        p_proy_1(k,:) = (I1* W1 * inE1 * [p_reales(k,:) 1]')';
    end
    
    % nuevo origen cam_1
    c1_o = E1*o';
        
    % Sistema de coordenadas de la cam_1
    M_c1 = M_or * E1;
    
%% Camera 2 - Informacion:

    %% Rotation Matrix
    
    angle_x_2 = 130;
    angle_y_2 = 310;
    angle_z_2 = 0;
    
    %% Translation
    %     X  Y  Z
    t2 = [5, 3, 2]';
    
%% Aplicar proyeccion con respecto a la camara 2
    % Distancia Focal Camara 2
    f2 = 1;
    
    % Matriz proyectiva
    [I2, W2, E2] = camera_matrix(angle_x_2, angle_y_2, angle_z_2, t2, f2);
    
    % Var. Aux. puntos proyectados
    p_proy_2 = zeros(size(p_reales,1),3);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE2 = inv(E2);
    for k=1:size(p_reales(:,1))
        p_proy_2(k,:) = (I2 * W2 * inE2 * [p_reales(k,:) 1]')';
    end    
    
%%

    %Visualizar los puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            p(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,3))';
        end

    % Visualizar los puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            p_p(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,3))'; 
        end
%%  Dados los puntos de las imagenes, computo la matrix Q de 3x3 que
%   cumple:
%           Siendo que p' = R*(p - t)
%               transpose(p')*Q*p = 0  
%           Donde Q = R*Tx
%           Siendo Tx = [0 T3 -T2; -T3 0 T1; T2 -T1 0] (Forma matricial
%           del producto vectorial)

% Formo la matriz para resolver el Sistema de Ecuaciones Lineal Homogeneo
A = zeros(8,9);
for k=1:8
    p1 = [p(k,:) 1];
    p2 = [p_p(k,:) 1];
    
    % (1 fila,9 columnas)
    A(k,:) = [ 
        %  px'*px  ,    px'*py  ,  px' ,   py'*px   ,    py'*py  ,  py' ,  px  ,  py  ,  1
        p2(1)*p1(1), p2(1)*p1(2), p2(1), p2(2)*p1(1), p2(2)*p1(2), p2(2), p1(1), p1(2),  1
    ];

end

% Resuelvo el sistema:  A*e = 0 -> Uso SVD... REVISAR

[U,S,V] = svd(A);
v = V(:,9);

Q = [
    v(1:3)';
    v(4:6)';
    v(7:9)'
];

er =0;
for k=1:size(p,1)
    er = er + [p_p(k,:) 1]*Q*[p(k,:) 1]'.^2;
end

er = er / size(p,1);

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
Mp = inv(Mp);

% TODO queda dependiendo de un factor de escala "lambda" (6.0828 para este 
%   ejemplo).

P = zeros(size(p,1), 3);
Fp = zeros(size(p_p, 1), 3);

err = 0;
while k <=size(p,1)
    %
    
    x3 = ((R(1,:) - p_p(k,1)*R(3,:))*t) / ((R(1,:) - p_p(k,1)*R(3,:))*[p(k,:) 1]');
    
    P(k,:) = x3 * [p(k,:) 1];
    P_p = R*(P(k,:)' - t);
    
    %
    
    x3_p = R(3,:)*(P(3,:)' - t);
    
    Fp(k,:) = P_p';
    
    err = err + P_p'*Q*P(k,:)'.^2;

    %
    
    k= k+1;
end

err = err /size(P,1);

% %%
% figure(2)
% clf
% hold on 
% grid on
% axis equal on
% 
% draw_coordinate_system(o,M_or,'o','blue')
% 
% scatter3(p(:,1), p(:,2), ones(size(p,1),1), 'o', 'black')
% 

%%
% figure(3)
% hold on
% grid on
% axis equal on
% 
% draw_coordinate_system(o, M_or,'o','blue')
% 
% scatter3(p_p(:,1), p_p(:,2), ones(size(p_p,1),1), 'o', 'black')
% scatter3(p_proy_2(:,1), p_proy_2(:,2), p_proy_2(:,3), 'o', 'black')

%%
figure(1)
clf
hold on
grid on
axis equal on

%
scatter3(p_reales(:,1) ,p_reales(:,2), p_reales(:,3), 'o', 'black')

%
draw_coordinate_system(o, M_or, 'o', 'blue' )

%
draw_coordinate_system(E1*o', E1*M_or, 'o', 'blue' )
draw_coordinate_system(E2*o', E2*M_or, 'o', 'blue' )

Mf = E1*Mp;
draw_coordinate_system(Mf*o', Mf*M_or, 'o', 'blue' )

lambda = 6.0828;

for k=1:size(P,1)
    Ep(k,:) = E1 * [lambda 0 0 0;
        0 lambda 0 0;
        0 0 lambda 0;
        0 0 0 1]* [P(k,:) 1]';
end

scatter3(Ep(:,1) , Ep(:,2), Ep(:,3), 'x', 'blue')

for k=1:size(P,1)
    Epl(k,:) = E1 * [p(k,:) 1 1]';
end

scatter3(Epl(:,1) , Epl(:,2), Epl(:,3), 'o', 'black')


Eo = E1*o';
plot3( [o(1) Eo(1)],[o(2) Eo(2)], [o(3) Eo(3)], 'color', 'black')

Ep1 = [p_reales(3,:) 1]';
plot3( [Ep1(1) Eo(1)],[Ep1(2) Eo(2)], [Ep1(3) Eo(3)], 'color', 'black')

Ep2 = [p_reales(7,:) 1]';
plot3( [Ep2(1) Eo(1)],[Ep2(2) Eo(2)], [Ep2(3) Eo(3)], 'color', 'black')

Ep3 = [p_reales(9,:) 1]';
plot3( [Ep3(1) Eo(1)],[Ep3(2) Eo(2)], [Ep3(3) Eo(3)], 'color', 'black')

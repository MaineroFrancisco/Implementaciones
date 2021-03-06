%% Paper: Hartley Richard
clear;
%% Puntos en el espacio tridimensional Real

p_reales = [
    0, 0, 0;
    0, 1, 0;
    0, 2, 0;
    1, 0, 0.3;
    1, 1, 0.5;
    1, 2, 0.3;
    2, 0, 0.1;
    2, 1, 0.2;
    2, 2, 0.1;
    3, 0, 0;
    3, 1, 0;
    3, 2, 0

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

    % Puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            p(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,3))';
        end

    % Puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            p_p(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,3))'; 
        end
        
%%
%%  Dados los puntos de las imagenes, computo la matrix Q de 3x3 que
%   cumple:
%           Siendo que p' = R*(p - t)
%               transpose(p')*Q*p = 0  
%           Donde Q = R*Tx
%           Siendo Tx = [0 T3 -T2; -T3 0 T1; T2 -T1 0] (Forma matricial
%           del producto vectorial)

% Formo la matriz para resolver el Sistema de Ecuaciones Lineal Homogeneo
A = zeros(8,9);
for k=1:size(p_reales,1)
% for k=1:8
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
% Descomposicion de Q usando SVD

[U1,S1,V1] = svd(Q);

k = (S1(1,1) + S1(2,2))/2;
S1 = [
    k 0 0;
    0 k 0;
    0 0 0    
];

% 
Q = U1*S1*V1';

QtQ = Q'*Q;
norma = sqrt((1/2)*trace(QtQ));
Q = Q/(norma);

[U1,S1,V1] = svd(Q);

E = [
     0 -1 0;
     1 0 0;
     0 0 1 
];

Z = [
    0 -1 0;
    1  0 0;
    0  0 0
];

% Matrices de Transfromacion:
% 4 versiones

% Rotation
% R = U1*E*V1';
R = U1*E'*V1';

% Traslation
t_x = V1*Z*V1';

% t = V1*[0 0 1]';
t = -V1*[0 0 1]';

Mp = [
    R  -R*t;
    0 0 0 1
];

% Mp = inv(Mp);

%%

P = zeros(size(p,1), 3);
Fp = zeros(size(p_p, 1), 3);

err = 0;
k=1;
while k <=size(p,1)
    %
    
    x3 = ((R(1,:) - p_p(k,1)*R(3,:))*t) / ((R(1,:) - p_p(k,1)*R(3,:))*[p(k,:) 1]');
    
    P(k,:) = x3 * [p(k,:) 1];
    P_p = R*(P(k,:)' - t);
    
    %
    
    x3_p = R(3,:)*(P(k,3)' - t);
    
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

Ei = inv(E1);

%
pei = Ei * [p_reales ones(size(p_reales,1),1)]';
pei = pei';

% scatter3(p_reales(:,1) ,p_reales(:,2), p_reales(:,3), 'o', 'black')
scatter3(pei(:,1) ,pei(:,2), pei(:,3), 'o', 'black')

%
draw_coordinate_system(Ei*o', Ei*M_or, 'o', 'blue' )

%
draw_coordinate_system(Ei*E1*o', Ei*E1*M_or, 'o', 'magenta' )
draw_coordinate_system(Ei*E2*o', Ei*E2*M_or, 'o', 'blue' )

Mf = Ei*E1*inv(Mp);
draw_coordinate_system(Mf*o', Mf*M_or, 'o', 'blue' )

scatter3(p_proy_1(:,1),p_proy_1(:,2), p_proy_1(:,3), '*', 'blue')

pe2 = Ei * E2 * [p_proy_2 ones(size(p_reales,1),1)]';
pe2 = pe2';
scatter3(pe2(:,1), pe2(:,2), pe2(:,3), 'x', 'red')

% for k=1:size(P,1)
%     Ep(k,:) = Ei * E1 * [3.5 0 0 0;
%         0 3.5 0 0;
%         0 0 3.5 0;
%         0 0 0 1]* [P(k,:) 1]';
% end
% 
% scatter3(Ep(:,1) , Ep(:,2), Ep(:,3), 'x', 'blue')
% 
% for k=1:size(P,1)
%     Epl(k,:) = Ei * E1 * [p(k,:) 1 1]';
% end
% 
% scatter3(Epl(:,1) , Epl(:,2), Epl(:,3), 'o', 'black')
% 
% Eo = Ei * E1*o';
% plot3( [o(1) Eo(1)],[o(2) Eo(2)], [o(3) Eo(3)], 'color', 'black')
% 
% Ep1 = [p_reales(3,:) 1]';
% plot3( [Ep1(1) Eo(1)],[Ep1(2) Eo(2)], [Ep1(3) Eo(3)], 'color', 'black')
% 
% Ep2 = [p_reales(7,:) 1]';
% plot3( [Ep2(1) Eo(1)],[Ep2(2) Eo(2)], [Ep2(3) Eo(3)], 'color', 'black')
% 
% Ep3 = [p_reales(9,:) 1]';
% plot3( [Ep3(1) Eo(1)],[Ep3(2) Eo(2)], [Ep3(3) Eo(3)], 'color', 'black')

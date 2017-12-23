%% Paper: "Zhang.pdf" Zhengyou Zhang
clear;
%% Puntos en el espacio tridimensional Real

p_reales = [
    0, 0, 0;
    0, 1, 0;
    1, 1, 0;
    1, 0, 0;
    0, 2, 0;
    0, 3, 0;
    1, 2, 0;
    1, 3, 0;
    2, 0, 0;
    2, 1, 0;
    2, 2, 0;
    2, 3, 0;
    3, 0, 0;
    3, 1, 0;
    3, 2, 0;
    3, 3, 0
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
    f1 = 2;
    
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
    f2 = 1.5;
    
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

%% Homografia: 
%   Cambio importante:
%       Z = 0 para toda la imagen.
%       Se computa la homografia entre la imagen y el MODELO... osea las
%       coordenadas en el mundo real.
% 
%       Q = A*[r1 r2 t] -> r3 = 0
% 

% Reestriccion: Los puntos deben formar un cuadrilatero(buscar relacion, no explicado en paper, REVISAR)


%   Mas de 1 foto con la misma camara es para la deduccion de parametros
%       INTRINSECOS

%     z1 = 1;
%     z2 = 2;
    n = 4;
    A = zeros(2*n,9);
    for k=1:n
        
        x1 = p_reales(k,1);
        y1 = p_reales(k,2);
        
        x2 = p(k,1);
        y2 = p(k,2);
        
        
        A(2*k-1,:) = [
         -x1 -y1 -1 0 0 0 (x2*x1) (x2*y1) x2;
        ];
        A(2*k,:)=[
         0 0 0 -x1 -y1 -1 (y2*x1) (y2*y1) y2;
        ];
    end

[U,S,V] = svd(A);

v = V(:,9)';

Q = [
    v(1:3);
    v(4:6);
    v(7:9)
];

%% Error
er = 0;
% 
% I = [
%     1 0 0;
%     0 1 0;
%     0 0 1
% ];
% 
% Iin = inv(I);
Iin = inv(I1);

for k=1:size(p,1)

    er = er + ([p(k,:) 1]'-Q*p_reales(k,:)').^2;

end
er = er /size(p,1);

%%
% Idealmente
lambda = 1/norm(Iin*Q(:,1));

r1 = lambda * Iin * Q(:,1);
r2 = lambda * Iin * Q(:,2);
r3 = cross(r1,r2);

R = [r1 r2 r3];

t = lambda* Iin * Q(:,3);


% Mp transforma los (X, Y, Z) del mundo real en (x, y, 1) de la imagen, visto desde la perspectiva del SC de la camara 
Mp = [
        R, t;
        0, 0, 0, 1
];

%%
figure(2)
clf
hold on 
grid on
axis equal on

draw_coordinate_system(o,M_or,'o','blue')

scatter3(p(:,1), p(:,2), ones(size(p,1),1), 'o', 'black')


P = I1 * W1* Mp * [p_reales ones(size(p,1),1)]';
P = P';

scatter3(P(:,1), P(:,2), P(:,3), '*', 'green')
scatter3(p_proy_1(:,1), p_proy_1(:,2), p_proy_1(:,3), 'x', 'blue')

draw_coordinate_system(Mp*o', Mp*M_or,'o','blue')

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

%
Ep1 = E1*[p f1*ones(size(p,1),1) ones(size(p,1),1)]';
Ep1 = Ep1';

Ep2 = E2*[p_p f2*ones(size(p_p,1),1) ones(size(p_p,1),1)]';
Ep2 = Ep2';

scatter3(Ep1(:,1), Ep1(:,2), Ep1(:,3), '.', 'black')
scatter3(Ep2(:,1), Ep2(:,2), Ep2(:,3), '.', 'black')

%%
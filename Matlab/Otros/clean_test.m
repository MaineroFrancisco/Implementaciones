%% Presets

    figure(2)
    clf
    figure(1)
    clf

    clear;
    
%% Puntos en el espacio tridimensional Real
% p_reales = [
%     0, 0, 0;
%     0, 1, 0;
%     0, 2, 0;
%     0, 3, 0;
%     1, 0, 0;
%     1, 1, 0;
%     1, 2, 0;
%     1, 3, 0;
%     2, 0, 0;
%     2, 1, 0;
%     2, 2, 0;
%     2, 3, 0;
%     3, 0, 0;
%     3, 1, 0;
%     3, 2, 0;
%     3, 3, 0
% ];

p_reales = [
    0, 0, 0;
    0, 1, 0;
    0, 2, 0;
    0, 3, 0;
    1, 0, 0;
    1, 1, 0.25;
    1, 2, 0.25;
    1, 3, 0;
    2, 0, 0;
    2, 1, 0.30;
    2, 2, 0.30;
    2, 3, 0;
    3, 0, 0;
    4, 1, 0;
    4, 2, 0;
    3, 3, 0
];

% Matrix de puntos 2D para la imagen de la camara 1
img_cam_1 = zeros(size(p_reales,1),2);

% Matrix de puntos 2D para la imagen de la camara 2
img_cam_2 = zeros(size(p_reales,1),2);

%% Proyeccion a 1 Imagen:
%    El sistema de coordenadas inicial:
%    [1 0 0              [1 0 0 0
%     0 1 0      o        0 1 0 0    en coordenadas homogeneas
%     0 0 1]              0 0 1 0
%                         0 0 0 1]
%   Para el sistema coordenado de la camara, la fotografia se proyectara en
%   el plano XY para z = 1
%

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
    % respecto a lo ejes originales
    %     X  Y  Z
    t1 = [-1, 4, 2]';
    
%% Aplicar proyeccion con respecto a la camara 1
    % Distancia Focal Camara 1
    f1 = 1;
    
    % Matriz proyectiva
    % REVISAR PINHOLE_CAMERA_MODEL PARA ENTENDER PORQUE ASI ESTA MATRIZ
    [I1, W1, E1] = camera_matrix(angle_x_1, angle_y_1, angle_z_1, t1, f1);
    
    % Var. Aux. puntos proyectados
    p_proy_1 = zeros(size(p_reales,1),3);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE1 = inv(E1);
    for k=1:size(p_reales(:,1))
        p_proy_1(k,:) = (I1* W1 * inE1 * [p_reales(k,:) 1]')';
%         p_proy_1(k,:) = p_proy_1(k,:)/p_proy_1(k,4);
    end
    
    % nuevo origen cam_1
    c1_o = E1*o';
        
    % Sistema de coordenadas de la cam_1
    M_c1 = M_or * E1;
    
%% Camera 2 - Informacion:

    %% Rotation Matrix
    
    angle_x_2 = 130;
    angle_y_2 = -50;
    angle_z_2 = 0;
    
    %% Translation
    % respecto a lo ejes originales
    %     X  Y  Z
    t2 = [5, 3, 2]';
    
%% Aplicar proyeccion con respecto a la camara 2
    % Distancia Focal Camara 2
    f2 = 1;
    
    % Matriz proyectiva
    % REVISAR PINHOLE_CAMERA_MODEL PARA ENTENDER PORQUE ASI ESTA MATRIZ
    [I2, W2, E2] = camera_matrix(angle_x_2, angle_y_2, angle_z_2, t2, f2);
    
    % Var. Aux. puntos proyectados
    p_proy_2 = zeros(size(p_reales,1),3);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE2 = inv(E2);
    for k=1:size(p_reales(:,1))
        p_proy_2(k,:) = (I2 * W2 * inE2 * [p_reales(k,:) 1]')';
%         p_proy_1(k,:) = p_proy_1(k,:)/p_proy_1(k,4);
    end    

% 
%     % nuevo origen cam_1
%     c2_o = E2*o';
% 
%     % Sistema de coordenadas de la cam_1
%     M_c2 = M_or * E2;

%%  Epipoles

%     % Proyeccion epipole camara 1
%     p_proy_1 = [ 
%         p_proy_1;
%         (I1 * W1 * inE1 * c2_o)'
%     ];
% 
%     p_proy_2 = [ 
%         p_proy_2;
%         (I2 * W2 * inE2 * c1_o)'
%     ];
    
%% Resolver SE Lineal NO Homogeneo:

    %Visualizar los puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            img_cam_1(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,3))';
        end

    % Visualizar los puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            img_cam_2(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,3))'; 
        end
    
    x1 = img_cam_1(1,1);
    y1 = img_cam_1(1,2);
%     z1 = f1;
    z1 = 1;
    
    x2 = img_cam_2(1,1);
    y2 = img_cam_2(1,2);
%     z2 = f2;
    z2 = 1;
    
    % Para el primer punto
    A = [
        x2*x1, x2*y1, x2, y2*x1, y2*y1, y2, x1, y1, 1;
    ];
%     A = [
%         -x2, -y2, -z2, 0, 0, 0, (x1/z1)*x2, (x1/z1)*y2, (x1/z1)*z2;
%         0, 0, 0, -x2, -y2, -z2,(y1/z1)*x2, (y1/z1)*y2, (y1/z1)*z2;
%     ];

%     A = [
%         x2, y2, z2, 1, 0, 0, 0, 0, 0, 0, 0, 0;
%         0, 0, 0, 0, x2, y2, z2, 1, 0, 0, 0, 0;
%         0, 0, 0, 0, 0, 0, 0, 0, x2, y2, z2, 1;
%     ];
% 
%     b = [
%         x1, y1, z1
%     ]';
    
%     for k=2:size(p_proy_2(2:size(img_cam_2,1)-1,1),1)
    for k=2:size(p_proy_2(2:9,1),1)
%     for k=2:size(p_proy_2(2:8,1),1)
        
        x1 = img_cam_1(k,1);
        y1 = img_cam_1(k,2);

        x2 = img_cam_2(k,1);
        y2 = img_cam_2(k,2);

        % Por punto
        %% 8 - points Algorithm
        %   p2'*E*p1 = 0
        A_punto = [
            x2*x1, x2*y1, x2, y2*x1, y2*y1, y2, x1, y1, 1;
        ];

        %% Homografia General
%         A_punto = [
%             -x2, -y2, -z2, 0, 0, 0, (x1/z1)*x2, (x1/z1)*y2, (x1/z1)*z2;
%             0, 0, 0, -x2, -y2, -z2,(y1/z1)*x2, (y1/z1)*y2, (y1/z1)*z2;
%         ];

        %% Sistema de ecuaciones pelado
%         A_punto = [
%             x2, y2, z2, 1, 0, 0, 0, 0, 0, 0, 0, 0;
%             0, 0, 0, 0, x2, y2, z2, 1, 0, 0, 0, 0;
%             0, 0, 0, 0, 0, 0, 0, 0, x2, y2, z2, 1;
%         ];
% 
%         b_punto = [
%             x1, y1, z1
%         ]';
    
        % Final
        A = [ 
            A;
            A_punto
            ];
        
%         b = [
%           b;
%           b_punto
%         ];
    end
    
    % Solucion
%     v = linsolve(A,b)
    
    [U1,S1,V1] = svd(A);
    
    % Descomposicion

    v = V1(:,9);

    E = [
        v(1:3)';
        v(4:6)';
        v(7:9)'
    ];
    
    [U2,S2,V2] = svd(E);
    
    S2 = [
        ((S2(1,1) + S2(2,2))/2), 0, 0;
        0, ((S2(1,1) + S2(2,2))/2), 0;
        0, 0, 0
    ];

    E = U2 *S2 * V2';
    
    norma = sqrt((1/2)*trace(E'*E));
    E = E/norma;
    
%     E
    [U2,S2,V2] =svd(E);
    %% Chequeo Constrains
    det(E)
    2*E*E'*E - trace(E*E')*E

    v = [E(1,:), E(2,:), E(3,:)]';
%     A*v

    %% R y t_x
    W = [
        0 -1 0;
        1 0 0;
        0 0 1
    ];

    Z = [
        0 1 0;
        -1 0 0;
        0 0 0
    ];

    t_x = U2 * Z * U2';
    
    t = [
      -t_x(2,3);
      t_x(1,3);
      -t_x(1,2)
    ];
    
    R = U2 * W * V2';
    
    Mp = [
        R t;
        0 0 0 1
    ];

ad = 0;
for k=1:size(img_cam_1,1)
    
    ad = ad + [img_cam_1(1,:) 1]*E'*[img_cam_2(1,:) 1]'.^2;
    
end

ad/size(img_cam_1,1)
%%
figure(2)
hold on
grid on
axis equal on

%     for k=1:size(img_cam_2,1)
%         res =  E * [img_cam_2(k,:) 1]';
% %         res = res/res(3);
%         scatter3(res(1), res(2), res(3), '*', 'red')
%     end

draw_coordinate_system(o,M_or,'o','blue')
draw_coordinate_system(Mp*o',Mp*M_or,'o','blue')
% draw_coordinate_system([E [0 0 0]'; [0 0 0 1]]*o',[E [0 0 0]'; [0 0 0 1]]*M_or,'o','blue')

% scatter3(img_cam_1(:,1), img_cam_1(:,2), 1*ones(size(img_cam_1,1),1), 'o', 'black')
% scatter3(img_cam_2(:,1), img_cam_2(:,2), 1*ones(size(img_cam_2,1),1), 'o', 'magenta')

%%
% 
% figure(1)
% hold on
% grid on
% axis equal on
% axis equal on
% 
% scatter3(0,0,0,'*','black')
% scatter3(0,1,0,'o','blue')
% scatter3(0,0,1,'o','green')
% 
% plot3([0 1], [0 0],[0 0], 'Color', 'red')
% plot3([0 0], [0 1],[0 0], 'Color', 'blue')
% plot3([0 0], [0 0],[0 1], 'Color', 'green')
% 
% % plot3([0 op(1)], [0 op(2)],[0 op(3)], 'Color', 'black')
% % scatter3(op(1), op(2), op(3), 'x', 'black')
% 
% scatter3(Or(:,1), Or(:,2), Or(:,3), 'o', 'black')
% scatter3(Xr(:,1), Xr(:,2), Xr(:,3), 'o', 'black')

%% 
%% Figure 1: Ploteo General del Sistema.
%       -> Sistema de Coordenadas Original (del mundo)
%       -> Objeto en el espacio
%       -> Sistema de Coordenadas de la Camara
%       -> Imagen proyectada en el plano (segun el SC de la camara)
    
    % Visualizar Sistema de Coordenadas original

        figure(1)
        hold on
        grid on
        axis equal on
        
        draw_coordinate_system(o, M_or, 'o', 'blue')
        
    % Visualizar objeto a projectar
        scatter3(p_reales(:,1),p_reales(:,2),p_reales(:,3),'x','black');
    
    %% Visualizar Sistema de Coordenadas Cam_1
        % para computar rotation y translacion en una sola matriz 
        % es necesario trabajar en coordenadas homogenes,
        % lo cual ayuda a computar la traslacion como una operacion
        % lineal en un dominio projectado.

        % nuevo origen cam_1
        c1_o = E1*o';
        
        % Sistema de coordenadas de la cam_1
        M_c1 = E1 * M_or;
        
        draw_coordinate_system(c1_o,M_c1, 'o', 'blue')
        
    %Visualizar los puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            img_cam_1(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,3))';
            
%             p_fig = M_c1 * [(p_proy_1(k,:)/p_proy_1(k,3)) 1]';
            p_fig = M_c1 * [p_proy_1(k,:)/p_proy_1(k,3) 1]';
            p_fig = p_fig/p_fig(4);
            
            scatter3(p_fig(1), p_fig(2), p_fig(3), 'o', 'black');        
        end
    
    % Plotear plano proyectado en el SC de la camara 1

        [x y] = meshgrid(-1:0.1:1); % Generate x and y data

        z = f1*ones(size(x, 1)); % Generate z data

        C = zeros(size(z))*100;
        
        for k=1:size(x,1)
            for j=1:size(x,2)
                pos = M_c1 * [x(k, j); y(k, j); z(k, j); 1];

                x(k, j) = pos(1);
                y(k, j) = pos(2);
                z(k, j) = pos(3);
            end
        end
        
        surf(x, y, z, C) % Plot the surface
        
    % Potear linea, Punto Original - Origen SC Cam 1
     
        plot3([o(1), c1_o(1)], [o(2), c1_o(2)], [o(3), c1_o(3)], 'color', 'black');
        plot3([p_reales(4,1), c1_o(1)], [p_reales(4,2), c1_o(2)], [p_reales(4,3), c1_o(3)], 'color', 'black');
        plot3([p_reales(13,1), c1_o(1)], [p_reales(13,2), c1_o(2)], [p_reales(13,3), c1_o(3)], 'color', 'black');
        plot3([p_reales(16,1), c1_o(1)], [p_reales(16,2), c1_o(2)], [p_reales(16,3), c1_o(3)], 'color', 'black');

    %% Visualizar Sistema de Coordenadas Cam_2
        % para computar rotation y translacion en una sola matriz 
        % es necesario trabajar en coordenadas homogenes,
        % lo cual ayuda a computar la traslacion como una operacion
        % lineal en un dominio projectado.

        % nuevo origen cam_1
        c2_o = E2*o';

        % Sistema de coordenadas de la cam_1
        M_c2 = E2 * M_or;
        
        draw_coordinate_system(c2_o, M_c2, 'o', 'blue')
    % Visualizar los puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            img_cam_2(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,3))'; 
            
%             p_fig = M_c2 * [(p_proy_2(k,:)/p_proy_2(k,3)) 1]';            
            p_fig = M_c2 * [p_proy_2(k,:)/p_proy_2(k,3) 1]';            
            p_fig = p_fig/p_fig(4);
            
            scatter3(p_fig(1), p_fig(2), p_fig(3), 'o', 'black');        
        end
    
    % Plotear plano proyectado en el SC de la camara 1

        [x y] = meshgrid(-1:0.1:1); % Generate x and y data

        z = f2*ones(size(x, 1)); % Generate z data

        C = zeros(size(z))*100;
        for k=1:size(x,1)
            for j=1:size(x,2)
                pos = M_c2 * [x(k, j); y(k, j); z(k, j); 1];

                x(k, j) = pos(1);
                y(k, j) = pos(2);
                z(k, j) = pos(3);
            end
        end

        surf(x, y, z, C) % Plot the surface
        
    % Potear linea, Punto Original - Origen SC Cam 1
     
        plot3([o(1), c2_o(1)], [o(2), c2_o(2)], [o(3), c2_o(3)], 'color', 'black');
        plot3([p_reales(4,1), c2_o(1)], [p_reales(4,2), c2_o(2)], [p_reales(4,3), c2_o(3)], 'color', 'black');
        plot3([p_reales(13,1), c2_o(1)], [p_reales(13,2), c2_o(2)], [p_reales(13,3), c2_o(3)], 'color', 'black');
        plot3([p_reales(16,1), c2_o(1)], [p_reales(16,2), c2_o(2)], [p_reales(16,3), c2_o(3)], 'color', 'black');

    % Plotear Linea entre centros de camaras
    
    plot3([c1_o(1), c2_o(1)], [c1_o(2), c2_o(2)], [c1_o(3), c2_o(3)], 'color', 'm');
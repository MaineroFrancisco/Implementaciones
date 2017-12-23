%% Presets

    figure(2)
    clf
    figure(1)
    clf

%% Puntos en el espacio tridimensional Real
p_reales = [
    0, 0, 0;
    0, 1, 0;
    0, 2, 0;
    0, 3, 0;
    1, 0, 0;
    1, 1, 0;
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

img_cam_1 = zeros(size(p_reales,1),2);
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

M_sc = [
    1, 0, 0;
    0, 1, 0;
    0, 0, 1
];

M_sc_h = [
    1, 0, 0, 0;
    0, 1, 0, 0;
    0, 0, 1, 0;
    0, 0, 0, 1
];

% Origen del SC del mundo
o = [0, 0, 0];
 
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
    f1 = 0.5;
    
    % Matriz proyectiva
    % REVISAR PINHOLE_CAMERA_MODEL PARA ENTENDER PORQUE ASI ESTA MATRIZ
    [I1, E1] = camera_matrix(angle_x_1, angle_y_1, angle_z_1, t1, f1);
    
    % Var. Aux. puntos proyectados
    p_proy_1 = zeros(size(p_reales,1),4);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE1 = inv(E1);
    for k=1:size(p_reales(:,1))
        p_proy_1(k,:) = (I1 * inE1 * [p_reales(k,:) 1]')';
%         p_proy_1(k,:) = p_proy_1(k,:)/p_proy_1(k,4);
    end
    
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
    f2 = 0.75;
    
    % Matriz proyectiva
    % REVISAR PINHOLE_CAMERA_MODEL PARA ENTENDER PORQUE ASI ESTA MATRIZ
    [I2, E2] = camera_matrix(angle_x_2, angle_y_2, angle_z_2, t2, f2);
    
    % Var. Aux. puntos proyectados
    p_proy_2 = zeros(size(p_reales,1),4);
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
    inE2 = inv(E2);
    for k=1:size(p_reales(:,1))
        p_proy_2(k,:) = (I2 * inE2 * [p_reales(k,:) 1]')';
%         p_proy_1(k,:) = p_proy_1(k,:)/p_proy_1(k,4);
    end    
    
% %% Figure 2: Ploteo Sistema para la Camara 1.
% %       -> Sistema de Coordenadas de la Camara 1 (como SC Original, perspectiva del O)
% %       -> Puntos Originales, desde la perspectiva de la Camara 1, por eso
% %       es necearia la inversion de E.
% 
% %       -> E : Matriz de parametros Extrinsecos de la camara
% %       -> I : Matriz de parametros Intrinsecos de la camara
% 
%     figure(2)
%     hold on
%     grid on
%     axis equal on
%     
%     scatter3(p_proy_1(:,1), p_proy_1(:,2)', p_proy_1(:,3)', 'o', 'black');
%     
%     scatter3(o(1), o(2), o(3), '*', 'red');
% 
%     plot3([o(1), M_sc(1,1)], [o(2), M_sc(2,1)], [o(3), M_sc(3,1)], 'color', 'red');
%     plot3([o(1), M_sc(1,2)], [o(2), M_sc(2,2)], [o(3), M_sc(3,2)], 'color', 'blue');
%     plot3([o(1), M_sc(1,3)], [o(2), M_sc(2,3)], [o(3), M_sc(3,3)], 'color', 'green');
% 
%     scatter3(M_sc(:,1), M_sc(:,2), M_sc(:,3), 'o', 'red');
%         
% 
%     % Ploteo plano de proyeccion
%     [x y] = meshgrid(-1:0.1:1); % Generate x and y data
%     
%     z = f1*ones(size(x, 1)); % Generate z data
% 
%     surf(x, y, z) % Plot the surface
%     
%     % Ploteo lineas, Punto Original - Origen SC Camara 1
%     plot3([p_proy_1(1,1), o(1)], [p_proy_1(1,2), o(2)], [p_proy_1(1,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(4,1), o(1)], [p_proy_1(4,2), o(2)], [p_proy_1(4,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(13,1), o(1)], [p_proy_1(13,2), o(2)], [p_proy_1(13,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(16,1), o(1)], [p_proy_1(16,2), o(2)], [p_proy_1(16,3), o(3)], 'color', 'black');
%     
% %% Figure 3: Ploteo Sistema para la Camara 2.
% %       -> Sistema de Coordenadas de la Camara 1 (como SC Original, perspectiva del O)
% %       -> Puntos Originales, desde la perspectiva de la Camara 1, por eso
% %       es necearia la inversion de E.
% 
% %       -> E : Matriz de parametros Extrinsecos de la camara
% %       -> I : Matriz de parametros Intrinsecos de la camara
% 
%     figure(3)
%     hold on
%     grid on
%     axis equal on
%     
%     scatter3(p_proy_2(:,1), p_proy_2(:,2)', p_proy_2(:,3)', 'o', 'black');
%     
%     scatter3(o(1), o(2), o(3), '*', 'red');
% 
%     plot3([o(1), M_sc(1,1)], [o(2), M_sc(2,1)], [o(3), M_sc(3,1)], 'color', 'red');
%     plot3([o(1), M_sc(1,2)], [o(2), M_sc(2,2)], [o(3), M_sc(3,2)], 'color', 'blue');
%     plot3([o(1), M_sc(1,3)], [o(2), M_sc(2,3)], [o(3), M_sc(3,3)], 'color', 'green');
% 
%     scatter3(M_sc(:,1), M_sc(:,2), M_sc(:,3), 'o', 'red');
%         
% 
%     % Ploteo plano de proyeccion
%     [x y] = meshgrid(-1:0.1:1); % Generate x and y data
%     
%     z = f2*ones(size(x, 1)); % Generate z data
% 
%     surf(x, y, z) % Plot the surface
%     
%     % Ploteo lineas, Punto Original - Origen SC Camara 1
%     plot3([p_proy_2(1,1), o(1)], [p_proy_2(1,2), o(2)], [p_proy_2(1,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(4,1), o(1)], [p_proy_2(4,2), o(2)], [p_proy_2(4,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(13,1), o(1)], [p_proy_2(13,2), o(2)], [p_proy_2(13,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(16,1), o(1)], [p_proy_2(16,2), o(2)], [p_proy_2(16,3), o(3)], 'color', 'black');   
            
% Ploteos de las imagenes capturadas por las camaras
% 
%     % Camara 1
%     figure(4)
%     hold on 
%     grid on
%     axis equal on
%     scatter(img_cam_1(:,1),img_cam_1(:,2), 'o', 'black');
%     
%     % Camara 2
%     figure(5)
%     hold on 
%     grid on
%     axis equal on
%     scatter(img_cam_2(:,1),img_cam_2(:,2), 'o', 'black');
%     
%% Deduccion de Parametros Extrinsicos

% Conociendo las F (distancia focal) de cada camara, y tomando una de las
% mismas como el SC Original (0, 0, 0), requiero deducir una transformacion
% de la siguiente forma:

%       Para estos ejemplos: f1 = f2, es decir, que las fotografias fueron  
%           tomadas con el mismo tipo de camara.

%       Siendo X,Y y Z las coordenadas del SCO para la primer imagen,
%           y 'x','y' y 'z' los de la segunda imagen,
%           al corresponderse los puntos capturados en la segunda imagen
%           con los de la primera, se los puede interpretar como una
%           version, para una misma distancia focal, trasladada y rotada de
%           los mismo, es decir, su correspondencia se puede traducir en
%           una matriz que transforma los puntos de una imagen a los de
%           otra.
%           Se puede hacer provecho de esto para deducir las propiedades
%           extrinsicas (rotacion y traslacion) de una camara respecto a la otra,
%           y de este modo poder ubicar ambas, de forma relativa, en el
%           espacio 3D.
%           Posterior a esto se puede llevar a cabo una triangulacion entre
%           correspondencias para determinar la posicion 3D de cada punto.
%
%       X       r1x r2x r3x  ex     x 
%       Y   =   r1y r2y r3y  ey  *  y 
%       f1      r1z r2z r3z  ez     f2
%       1         0   0   0   1     1
% 

%       Se tiene un Sistema De Ecuaciones LINEAL NO HOMOGENEO, con 
%       3 ecuaciones y 12 incognitas, con lo cual se requieren 4 puntos 
%       que se correspondan como minimo para resolverlo. 

%       O se puede traducir en un Sistema De Ecuaciones LINEAL HOMOGENEO
%       de 2 ecuaciones y 12 incognitas, pero se requerira de 6 puntos para
%       resolverlo.
%       El SE Lineal Homogeneo es de la siguiente forma:

%
%
%
%       *VER APUNTE "homography_estimations.pdf"*

    %% Resolver SE Lineal NO Homogeneo:
    
%     syms r1x r1y r1z ex r2x r2y r2z ey r3x r3y r3z ez
    
%     incg = [ r1x, r1y, r1z, ex, r2x, r2y, r2z, ey, r3x, r3y, r3z, ez ]';
    

    % Visualizar los puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            img_cam_2(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,4))'; 
            
%             p_fig = M_c2 * (p_proy_2(k,:)/p_proy_2(k,4))';            
%             scatter3(p_fig(1), p_fig(2), p_fig(3), 'o', 'black');        
        end
    
    %Visualizar los puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            img_cam_1(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,4))';
            
%             p_fig = M_c1 * (p_proy_1(k,:)/p_proy_1(k,4))';
%             scatter3(p_fig(1), p_fig(2), p_fig(3), 'o', 'black');        
        end

    x1 = img_cam_1(1,1);
    y1 = img_cam_1(1,2);
    
    x2 = img_cam_2(1,1);
    y2 = img_cam_2(1,2);
    z2 = f2;
    
    % Por punto
    A_punto = [
        -x2, -y2, -z2, 0, 0, 0, (x1/f1)*x2, (x1/f1)*y2, (x1/f1)*z2;
        0, 0, 0, -x2, -y2, -z2,(y1/f1)*x2, (y1/f1)*y2, (y1/f1)*z2;
    ];

    b_punto = [
        x1, y1, f1
    ]';
    
    % Final
    A = [ 
        A_punto
        ];
    
    b = [
        b_punto
    ];
    
    for k=2:size(p_proy_2(:,1),1)
        
        x1 = img_cam_1(k,1);
        y1 = img_cam_1(k,2);

        x2 = img_cam_2(k,1);
        y2 = img_cam_2(k,2);

        % Por punto
        A_punto = [
            -x2, -y2, -z2, 0, 0, 0, (x1/f1)*x2, (x1/f1)*y2, (x1/f1)*z2;
            0, 0, 0, -x2, -y2, -z2,(y1/f1)*x2, (y1/f1)*y2, (y1/f1)*z2;
        ];

%         b_punto = [
%             0, 0
%         ]';

        % Final
        A = [ 
            A;
            A_punto
            ];
% 
%         b = [
%             b;
%             b_punto
%         ];  
        
    end
%     size(A)
%     size(b)
    % Solucion
%     X = linsolve(A,b)
    [U1,S1,V1] = svd(A);
    
    % Descomposicion
%     M_Final = [
%             X(1:4)';
%             X(5:8)';
%             X(9:12)';
%             [0,0,0,1]
%     ];

%     v = V(:,size(V,2));
    v = V1(:,9);
%     
%     M_Final = [
%         [v(1:3); 0]';
%         [v(4:6); 0]';
%         [v(7:9); 0]';
%         [0,0,0,1]
%     ];


    M_Final = [
        v(1:3)';
        v(4:6)';
        v(7:9)'
    ];

    %%
    
    
    F = M_Final;
    
    Or = zeros(size(img_cam_2,1),3);
    Xr = zeros(size(img_cam_2,1),3);
    for k=1:size(img_cam_2,1)
        Or(k,:) = [img_cam_1(k,:) f1];
        Xr(k,:) = F * [img_cam_2(k,:) f2]';
        Xr(k,:) = f1 * Xr(k,:) / Xr(k,3);
    end
    
    figure(2)
    hold on 
    grid on
    axis equal on
    
%     scatter(img_cam_1(:,1),img_cam_1(:,2))
%     scatter(Xr(:,1),Xr(:,2))
    
    [U2,S2,V2] = svd(M_Final);
    
    S2(:,3) = [0 0 0]';
    
    W = [
        0 1 0;
        -1 0 0;
        0 0 1
    ];

    Z = [
        0 1 0;
        -1 0 0;
        0 0 0
    ];

    R_p = U2 * W * V2';
    
    tx_p = U2 * Z * S2 * U2';
    
    tp = zeros(3,1);
    tp(1) = -tx_p(2,3);
    tp(2) = tx_p(1,3);
    tp(3) = -tx_p(1,2);
    
    
    Mp = [
        R_p tp;
        [0 0 0 1]
    ];
    


%% Figure 6: Ploteo Sistema para la Camara 1 + proyc. Camara 2.
%       -> Sistema de Coordenadas de la Camara 1 (como SC Original, perspectiva del O)
%       -> Puntos Originales, desde la perspectiva de la Camara 1, por eso
%       es necearia la inversion de E.

%       -> E : Matriz de parametros Extrinsecos de la camara
%       -> I : Matriz de parametros Intrinsecos de la camara

%     figure(6)
%     hold on
%     grid on
%     axis equal on
%     
    
    scatter3(img_cam_1(:,1), img_cam_1(:,2)', f1* ones(size(img_cam_1,1),1), 'o', 'black');
    
    scatter3(o(1), o(2), o(3), '*', 'red');

    plot3([o(1), M_sc(1,1)], [o(2), M_sc(2,1)], [o(3), M_sc(3,1)], 'color', 'red');
    plot3([o(1), M_sc(1,2)], [o(2), M_sc(2,2)], [o(3), M_sc(3,2)], 'color', 'blue');
    plot3([o(1), M_sc(1,3)], [o(2), M_sc(2,3)], [o(3), M_sc(3,3)], 'color', 'green');

    scatter3(M_sc(:,1), M_sc(:,2), M_sc(:,3), 'o', 'red');
        

%     % Ploteo plano de proyeccion
%     [x y] = meshgrid(-1:0.1:1); % Generate x and y data
%     
%     z = f1*ones(size(x, 1)); % Generate z data
% 
%     surf(x, y, z) % Plot the surface
%     
%     % Ploteo lineas, Punto Original - Origen SC Camara 1
%     plot3([p_proy_1(1,1), o(1)], [p_proy_1(1,2), o(2)], [p_proy_1(1,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(4,1), o(1)], [p_proy_1(4,2), o(2)], [p_proy_1(4,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(13,1), o(1)], [p_proy_1(13,2), o(2)], [p_proy_1(13,3), o(3)], 'color', 'black');
%     plot3([p_proy_1(16,1), o(1)], [p_proy_1(16,2), o(2)], [p_proy_1(16,3), o(3)], 'color', 'black');


    %% Camara 2
%     M_Final(2,2) = 1.0;
    inMF = inv(Mp);     
    
    c2_o = inMF * [o 1]';
    
    ip2 = zeros(size(img_cam_2,1),4);
    
    for k=1:size(img_cam_2,1)
        p_fig = inMF * [img_cam_2(k,:) f2 1]';
        ip2(k,:) = p_fig;
        %%p_fig = p_fig(:)/p_fig(4);
        
        
        scatter3(p_fig(1), p_fig(2), p_fig(3), '+', 'red');
    end
    
    scatter3(c2_o(1), c2_o(2), c2_o(3), '*', 'red');

    plot3([c2_o(1), inMF(1,1) + c2_o(1)], [c2_o(2), inMF(2,1) + c2_o(2)], [c2_o(3), inMF(3,1) + c2_o(3)], 'color', 'red');
    plot3([c2_o(1), inMF(1,2) + c2_o(1)], [c2_o(2), inMF(2,2) + c2_o(2)], [c2_o(3), inMF(3,2) + c2_o(3)], 'color', 'blue');
    plot3([c2_o(1), inMF(1,3) + c2_o(1)], [c2_o(2), inMF(2,3) + c2_o(2)], [c2_o(3), inMF(3,3) + c2_o(3)], 'color', 'green');

%     scatter3(M_sc(:,1), M_sc(:,2), M_sc(:,3), 'o', 'red');
        
    % Ploteo plano de proyeccion
%     [x y] = meshgrid(-1:0.1:1); % Generate x and y data
%     
%     z = f2*ones(size(x, 1)); % Generate z data
% 
%     surf(x, y, z) % Plot the surface
%     
%     % Ploteo lineas, Punto Original - Origen SC Camara 1
%     plot3([p_proy_2(1,1), o(1)], [p_proy_2(1,2), o(2)], [p_proy_2(1,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(4,1), o(1)], [p_proy_2(4,2), o(2)], [p_proy_2(4,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(13,1), o(1)], [p_proy_2(13,2), o(2)], [p_proy_2(13,3), o(3)], 'color', 'black');
%     plot3([p_proy_2(16,1), o(1)], [p_proy_2(16,2), o(2)], [p_proy_2(16,3), o(3)], 'color', 'black');

%% reconstruir origen

pend = [img_cam_1(1,:) f1] - o

pend2 = ip2(1,:) - c2_o'

%
line = [o' (o + pend*10)']

line2 = [c2_o (c2_o' + pend2*10)']

plot3(line(1,:),line(2,:), line(3,:), 'black')
plot3(line2(1,:),line2(2,:), line2(3,:), 'red')



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
        
        scatter3(o(1), o(2), o(3), '*', 'red');
        
        plot3([o(1), M_sc(1,1) + o(1)], [o(2), M_sc(2,1) + o(2)], [o(3), M_sc(3,1) + o(3)], 'color', 'red');
        plot3([o(1), M_sc(1,2) + o(1)], [o(2), M_sc(2,2) + o(2)], [o(3), M_sc(3,2) + o(3)], 'color', 'blue');
        plot3([o(1), M_sc(1,3) + o(1)], [o(2), M_sc(2,3) + o(2)], [o(3), M_sc(3,3) + o(3)], 'color', 'green');
        
        scatter3(M_sc(1,:) + o(1), M_sc(2,:) + o(2), M_sc(3,:) + o(3), 'o', 'red');
        
    % Visualizar objeto a projectar
        scatter3(p_reales(:,1),p_reales(:,2),p_reales(:,3),'x','black');
    
    %% Visualizar Sistema de Coordenadas Cam_1
        % para computar rotation y translacion en una sola matriz 
        % es necesario trabajar en coordenadas homogenes,
        % lo cual ayuda a computar la traslacion como una operacion
        % lineal en un dominio projectado.

        % nuevo origen cam_1
        c1_o = E1*[o 1]';
        
        % Sistema de coordenadas de la cam_1
        M_c1 = M_sc_h * E1;
        
        scatter3(c1_o(1), c1_o(2), c1_o(3), '*', 'blue');
        
        plot3([c1_o(1), M_c1(1,1) + c1_o(1)], [c1_o(2), M_c1(2,1) + c1_o(2)], [c1_o(3), M_c1(3,1) + c1_o(3)], 'color', 'red');
        plot3([c1_o(1), M_c1(1,2) + c1_o(1)], [c1_o(2), M_c1(2,2) + c1_o(2)], [c1_o(3), M_c1(3,2) + c1_o(3)], 'color', 'blue');
        plot3([c1_o(1), M_c1(1,3) + c1_o(1)], [c1_o(2), M_c1(2,3) + c1_o(2)], [c1_o(3), M_c1(3,3) + c1_o(3)], 'color', 'green');
        
        scatter3(M_c1(1,1:3)+ c1_o(1), M_c1(2,1:3) + c1_o(2), M_c1(3,1:3) + c1_o(3), 'o', 'blue')
    
    %Visualizar los puntos proyectados en el SC de la camara 1
        for k=1:size(p_proy_1(:,1),1)
            
            %Matriz 2D que representa la Imagen capturada con la camara 1
            img_cam_1(k,:) = (p_proy_1(k,1:2)/p_proy_1(k,4))';
            
            p_fig = M_c1 * (p_proy_1(k,:)/p_proy_1(k,4))';
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
        c2_o = E2*[o 1]';

        % Sistema de coordenadas de la cam_1
        M_c2 = M_sc_h * E2;

        scatter3(c2_o(1), c2_o(2), c2_o(3), '*', 'blue');

        plot3([c2_o(1), M_c2(1,1) + c2_o(1)], [c2_o(2), M_c2(2,1) + c2_o(2)], [c2_o(3), M_c2(3,1) + c2_o(3)], 'color', 'red');
        plot3([c2_o(1), M_c2(1,2) + c2_o(1)], [c2_o(2), M_c2(2,2) + c2_o(2)], [c2_o(3), M_c2(3,2) + c2_o(3)], 'color', 'blue');
        plot3([c2_o(1), M_c2(1,3) + c2_o(1)], [c2_o(2), M_c2(2,3) + c2_o(2)], [c2_o(3), M_c2(3,3) + c2_o(3)], 'color', 'green');

        scatter3(M_c2(1,1:3)+ c2_o(1), M_c2(2,1:3) + c2_o(2), M_c2(3,1:3) + c2_o(3), 'o', 'blue')
        
    % Visualizar los puntos proyectados en el SC de la camara 2
        for k=1:size(p_proy_2(:,1),1)
            
            % Matriz 2D que representa la Imagen capturada con la camara 2
            img_cam_2(k,:) = (p_proy_2(k,1:2)/p_proy_2(k,4))'; 
            
            p_fig = M_c2 * (p_proy_2(k,:)/p_proy_2(k,4))';            
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
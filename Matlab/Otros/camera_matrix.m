function [I, W, E] = camera_matrix(angle_x, angle_y, angle_z, t, dist_f)

%% Rotation Matrix

    angle_x = angle_x*pi/180;
    angle_y = angle_y*pi/180;
    angle_z = angle_z*pi/180;
    
    R_x = [
        1, 0, 0;
        0, cos(angle_x), -sin(angle_x);
        0 , sin(angle_x), cos(angle_x)
    ];

    R_y = [
         cos(angle_y), 0, sin(angle_y);
         0, 1, 0;
         -sin(angle_y), 0, cos(angle_y)
    ];

     R_z = [
         cos(angle_z), -sin(angle_z),  0;
         sin(angle_z), cos(angle_z), 0;
         0, 0, 1
    ];

     R = R_x * R_y * R_z;
%% Traslation    
     % t = [x0, y0, z0]
     
%% Camera Matrix - Extrinsic Parameters
    % En Coordenadas Homogeneas
    E = [R t;
        0 0 0 1];
    
    % Esta inversion es importante, la transformacion se efectuaba para
    % pasar lo Original, a la camara 1, con la inversion yo puedo ver los
    % puntos originales desde la perspectiva de la camara 1.
%     M_c1_b = inv(M_c1);
    
%% Camera Matrix - Intrinsic Parameters

    % Matriz proyectiva
    % REVISAR PINHOLE_CAMERA_MODEL PARA ENTENDER PORQUE ASI ESTA MATRIZ
%     I = [
%         dist_f,      0,      0, 0;
%              0, dist_f,      0, 0;
%              0,      0, dist_f, 0;
%              0,      0,      1, 0
%     ];

    I = [
       dist_f, 0, 0;
       0, dist_f, 0;
       0, 0, 1
    ];
    
    W = [
        1, 0, 0, 0;
        0, 1, 0, 0;
        0, 0, 1, 0
    ];

%     P = I * W * E;
end
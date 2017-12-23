% Zhang Complete Test
clear;

ejemplo = 0;

switch ejemplo
   
    case 0
        %% Cargar
        load('Caja_Cubo/c1_1.mat')
        load('Caja_Cubo/c1_2.mat')
        load('Caja_Cubo/c1_3.mat')
        load('Caja_Cubo/c1_obj.mat')
        load('Caja_Cubo/c2_1.mat')
        load('Caja_Cubo/c2_2.mat')
        load('Caja_Cubo/c2_3.mat')
        load('Caja_Cubo/c2_obj.mat')
        
        %% Caja_Cubo
        % Camara 1
        p0_1 = [c1_1' ones(size(c1_1',1),1)];
        p1_1 = [c1_2' ones(size(c1_2',1),1)];   
        p2_1 = [c1_3' ones(size(c1_3',1),1)];

        % Camara 2
        p0_2 = [c2_1' ones(size(c2_1',1),1)];
        p1_2 = [c2_2' ones(size(c2_2',1),1)];   
        p2_2 = [c2_3' ones(size(c2_3',1),1)];

    case 1
        %% Cargar

        load('Cajas/c1_0.mat')
        load('Cajas/c1_1.mat')
        load('Cajas/c1_2.mat')
        load('Cajas/c1_3.mat')

        load('Cajas/c2_0.mat')
        load('Cajas/c2_1.mat')
        load('Cajas/c2_2.mat')
        load('Cajas/c2_3.mat')

        load('Cajas/c3_0.mat')
        load('Cajas/c3_1.mat')
        load('Cajas/c3_2.mat')
        load('Cajas/c3_3.mat')

        load('Cajas/c4_0.mat')
        load('Cajas/c4_1.mat')
        load('Cajas/c4_2.mat')
        load('Cajas/c4_3.mat')

        load('Cajas/c2_3_obj.mat')
        load('Cajas/c3_2_obj.mat')
        load('Cajas/c3_1_obj.mat')
        load('Cajas/c1_3_obj.mat')
        load('Cajas/c1_4_obj.mat')
        load('Cajas/c4_1_obj.mat')
        
        %% Cajas

        % Camara 1
        p0_1 = [c1_0' ones(size(c1_0',1),1)];
        p1_1 = [c1_1' ones(size(c1_1',1),1)];
        p2_1 = [c1_2' ones(size(c1_2',1),1)];   
        p3_1 = [c1_3' ones(size(c1_3',1),1)];

        % Camara 2
        p0_2 = [c2_0' ones(size(c2_0',1),1)];
        p1_2 = [c2_1' ones(size(c2_1',1),1)];
        p2_2 = [c2_2' ones(size(c2_2',1),1)];   
        p3_2 = [c2_3' ones(size(c2_3',1),1)];

        % Camara 3
        p0_3 = [c3_0' ones(size(c3_1',1),1)];
        p1_3 = [c3_1' ones(size(c3_1',1),1)];
        p2_3 = [c3_2' ones(size(c3_2',1),1)];   
        p3_3 = [c3_3' ones(size(c3_3',1),1)];

        % Camara 4
        p0_4 = [c4_0' ones(size(c4_1',1),1)];
        p1_4 = [c4_1' ones(size(c4_1',1),1)];
        p2_4 = [c4_2' ones(size(c4_2',1),1)];   
        p3_4 = [c4_3' ones(size(c4_3',1),1)];
       
    case 2
        %% Cargar

        load('Inventadas\c1_1.mat')
        load('Inventadas\c1_2.mat')
        load('Inventadas\c1_3.mat')
        load('Inventadas\c1_obj.mat')

        load('Inventadas\c2_1.mat')
        load('Inventadas\c2_2.mat')
        load('Inventadas\c2_3.mat')
        load('Inventadas\c2_obj.mat')

        load('Inventadas\c3_1.mat')
        load('Inventadas\c3_2.mat')
        load('Inventadas\c3_3.mat')
        load('Inventadas\c3_obj.mat')

        load('Inventadas\c4_1.mat')
        load('Inventadas\c4_2.mat')
        load('Inventadas\c4_3.mat')
        load('Inventadas\c4_obj.mat')

        load('Inventadas\Im_1.mat')
        load('Inventadas\Im_2.mat')
        load('Inventadas\Im_3.mat')
        load('Inventadas\Im_4.mat')
        
        %% Inventadas

        % Camara 1
        p0_1 = [c1_1' ones(size(c1_1',1),1)];
        p1_1 = [c1_2' ones(size(c1_2',1),1)];
        p2_1 = [c1_3' ones(size(c1_3',1),1)];   

        % Camara 2
        p0_2 = [c2_1' ones(size(c2_1',1),1)];
        p1_2 = [c2_2' ones(size(c2_2',1),1)];
        p2_2 = [c2_3' ones(size(c2_3',1),1)];   

        % Camara 3
        p0_3 = [c3_1' ones(size(c3_1',1),1)];
        p1_3 = [c3_2' ones(size(c3_2',1),1)];
        p2_3 = [c3_3' ones(size(c3_3',1),1)];   

        % Camara 4
        p0_4 = [c4_1' ones(size(c4_1',1),1)];
        p1_4 = [c4_2' ones(size(c4_2',1),1)];
        p2_4 = [c4_3' ones(size(c4_3',1),1)];   
        
end
 
 %%
% DEBERIAN SER (X,Y,Z,W)... pero como Z=0... uso solo (X,Y,W)
if ejemplo~=2
    p_reales = [
         0 0 1;
         0 1 1;
         1 0 1;
         1 1 1;
     ];
else
    % Inventados
    p_reales = [
       0 0 1;
       1 0 1;
       0 1 1;
       1 1 1;
    ];
end

%% Calibracion

switch ejemplo

    case 0
        %% Caja_cubo
        %  Camara 1
         [Im_1,Em1_1,Em2_1,Em3_1] = zhang_calibration(p_reales,p0_1,p1_1,p2_1);

         % Camara 2
         [Im_2,Em1_2,Em2_2,Em3_2] = zhang_calibration(p_reales,p0_2,p1_2,p2_2);

        %% Calibracion

        % Camara 1, todas las poses
%        triangulation_2(Im_1,Im_1,Em1_1,Em2_1,p0_1,p1_1,'o','red',1)
%        triangulation_2(Im_1,Im_1,Em2_1,Em3_1,p1_1,p2_1,'x','green',1)
%        triangulation_2(Im_1,Im_1,Em1_1,Em3_1,p0_1,p2_1,'*','blue',1)
%
%        % Camara 2, todas las poses
%        triangulation_2(Im_2,Im_2,Em1_2,Em2_2,p0_2,p1_2,'o','red',2)
%        triangulation_2(Im_2,Im_2,Em2_2,Em3_2,p1_2,p2_2,'x','green',2)
%        triangulation_2(Im_2,Im_2,Em1_2,Em3_2,p0_2,p2_2,'*','blue',2)

        %% Caja-Cubo reconstruido
 
        p_obj_1 = [c1_obj' ones(size(c1_obj',1),1)];
        p_obj_2 = [c2_obj' ones(size(c2_obj',1),1)];

        inters = triangulation_2(Im_1,Im_2,Em1_1,Em1_2,p_obj_1,p_obj_2,'o','red',4);
%        inters = triangulation_2(Im_1,Im_2,Em1_1,Em1_2,p0_1,p0_2,'o','red',4);

    case 1
        %% Cajas

        % Camara 1
        [Im_1,Em1_1,Em2_1,Em3_1] = zhang_calibration(p_reales,p0_1,p1_1,p2_1);

        % Camara 2
        [Im_2,Em1_2,Em2_2,Em3_2] = zhang_calibration(p_reales,p0_2,p1_2,p2_2);

        % Camara 3
        [Im_3,Em1_3,Em2_3,Em3_3] = zhang_calibration(p_reales,p0_3,p1_3,p2_3);

        % Camara 4
        [Im_4,Em1_4,Em2_4,Em3_4] = zhang_calibration(p_reales,p0_4,p1_4,p2_4);

        %% Calibracion

        % Camara 1, todas las poses
        triangulation_2(Im_1,Im_1,Em1_1,Em2_1,p0_1,p1_1,'o','red',1)
        triangulation_2(Im_1,Im_1,Em2_1,Em3_1,p1_1,p2_1,'x','green',1)
        triangulation_2(Im_1,Im_1,Em1_1,Em3_1,p0_1,p2_1,'*','blue',1)

        % Camara 2, todas las poses
        triangulation_2(Im_2,Im_2,Em1_2,Em2_2,p0_2,p1_2,'o','red',2)
        triangulation_2(Im_2,Im_2,Em2_2,Em3_2,p1_2,p2_2,'x','green',2)
        triangulation_2(Im_2,Im_2,Em1_2,Em3_2,p0_2,p2_2,'*','blue',2)

        % Camara 3, todas las poses
        triangulation_2(Im_3,Im_3,Em1_3,Em2_3,p0_3,p1_3,'o','red',3)
        triangulation_2(Im_3,Im_3,Em2_3,Em3_3,p1_3,p2_3,'x','green',3)
        triangulation_2(Im_3,Im_3,Em1_3,Em3_3,p0_3,p2_3,'*','blue',3)

        % Camara 4, todas las poses
        triangulation_2(Im_4,Im_4,Em1_4,Em2_4,p0_4,p1_4,'o','red',4)
        triangulation_2(Im_4,Im_4,Em2_4,Em3_4,p1_4,p2_4,'x','green',4)
        triangulation_2(Im_4,Im_4,Em1_4,Em3_4,p0_4,p2_4,'*','blue',4)

        %% Cajas reconstruido

        p_obj_1 = [c2_3_obj' ones(size(c2_3_obj',1),1)];
        p_obj_2 = [c3_2_obj' ones(size(c3_2_obj',1),1)];

        p_obj_3 = [c3_1_obj' ones(size(c3_1_obj',1),1)];
        p_obj_4 = [c1_3_obj' ones(size(c1_3_obj',1),1)];

        p_obj_5 = [c1_4_obj' ones(size(c1_4_obj',1),1)];
        p_obj_6 = [c4_1_obj' ones(size(c4_1_obj',1),1)];

        int23 = triangulation_2(Im_2,Im_3,Em1_2,Em1_3,p_obj_1,p_obj_2,'o','red',6);
        int31 = triangulation_2(Im_3,Im_1,Em1_3,Em1_1,p_obj_3,p_obj_4,'x','magenta',6);
        % int14 = triangulation_2(Im_1,Im_4,Em1_1,Em1_4,p_obj_5,p_obj_6,'o','green',6);

        
    case 2
        %% Inventadas

        % Camara 1
        [Im_1,Em1_1,Em2_1,Em3_1] = zhang_calibration(p_reales,p0_1,p1_1,p2_1);

        % Camara 2
        [Im_2,Em1_2,Em2_2,Em3_2] = zhang_calibration(p_reales,p0_2,p1_2,p2_2);

        % Camara 3
        [Im_3,Em1_3,Em2_3,Em3_3] = zhang_calibration(p_reales,p0_3,p1_3,p2_3);

        % Camara 4
        [Im_4,Em1_4,Em2_4,Em3_4] = zhang_calibration(p_reales,p0_4,p1_4,p2_4);

        %% Calibracion

        % Camara 1, todas las poses
        triangulation_2(Im_1,Im_1,Em1_1,Em2_1,p0_1,p1_1,'o','red',1)
        triangulation_2(Im_1,Im_1,Em2_1,Em3_1,p1_1,p2_1,'x','green',1)
        triangulation_2(Im_1,Im_1,Em1_1,Em3_1,p0_1,p2_1,'*','blue',1)

        % Camara 2, todas las poses
        triangulation_2(Im_2,Im_2,Em1_2,Em2_2,p0_2,p1_2,'o','red',2)
        triangulation_2(Im_2,Im_2,Em2_2,Em3_2,p1_2,p2_2,'x','green',2)
        triangulation_2(Im_2,Im_2,Em1_2,Em3_2,p0_2,p2_2,'*','blue',2)

        % Camara 3, todas las poses
        triangulation_2(Im_3,Im_3,Em1_3,Em2_3,p0_3,p1_3,'o','red',3)
        triangulation_2(Im_3,Im_3,Em2_3,Em3_3,p1_3,p2_3,'x','green',3)
        triangulation_2(Im_3,Im_3,Em1_3,Em3_3,p0_3,p2_3,'*','blue',3)

        % Camara 4, todas las poses
        triangulation_2(Im_4,Im_4,Em1_4,Em2_4,p0_4,p1_4,'o','red',4)
        triangulation_2(Im_4,Im_4,Em2_4,Em3_4,p1_4,p2_4,'x','green',4)
        triangulation_2(Im_4,Im_4,Em1_4,Em3_4,p0_4,p2_4,'*','blue',4)

        %% Inventadas
        p_obj_1 = [c1_obj' ones(size(c1_obj',1),1)];
        p_obj_2 = [c2_obj' ones(size(c2_obj',1),1)];
        p_obj_3 = [c3_obj' ones(size(c3_obj',1),1)];
        p_obj_4 = [c4_obj' ones(size(c4_obj',1),1)];

        triangulation_2(Im_1,Im_2,Em1_1,Em1_2,p_obj_1,p_obj_2,'o','red',6)
        triangulation_2(Im_2,Im_3,Em1_2,Em1_3,p_obj_2,p_obj_3,'x','blue',6)
        % triangulation_2(Im_1,Im_3,Em1_1,Em1_3,p_obj_1,p_obj_3,'*','black',6)
        % triangulation_2(Im_1,Im_4,Em1_1,Em1_4,p_obj_1,p_obj_4,'+','green',6)
        % triangulation_2(Im_2,Im_4,Em1_2,Em1_4,p_obj_2,p_obj_4,'o','magenta',6)
        % triangulation_2(Im_3,Im_4,Em1_3,Em1_4,p_obj_3,p_obj_4,'x','red',6)
end



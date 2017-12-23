% Calibration
function [Im,Em1,Em2,Em3] = zhang_calibration(p_reales,p0,p1,p2)

    %% Homography Computation
    %Closed Form Solution
    % z = 0

    % Homography Camera 0
    H1 = estimateHomography(p_reales,p0);

    % Homography Camera 1
    H2 = estimateHomography(p_reales,p1);

    % Homography Camera 2
    H3 = estimateHomography(p_reales,p2);

    %%Restaurar P_reales
    p_reales = [p_reales(:,1:2) zeros(size(p_reales,1),1) p_reales(:,3)];

    %% Aprovechando la ortogonalidad de la matriz de rotacion R, se calcula, en
    %% su relacion con lo homografia calculada:
    %
    %       h1          r1                  h1       r1
    %     h(:,1) = Im*R(:,1)  ->  inv(Im)*h(:,1) = R(:,1)
    %     -> r1*r1 = r2*r2
    %     -> r1*r2 = 0
    %
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
    V(6,:) = v11_c3 - v22_c3;

    %     V(5,:) = [0 1 0 0 0 0];   %Restriccion a implementar si se ignora el parametro de skewning (gamma)
    
    %% Descompongo y calculo para obtener los paremetros intrinsecos de la
    %% camara, pura formula de los apuntes, la explicacion del desglose viene
    %% por lo desarrollado arriba.

    b = gauss(V);
%     [U,S,Vt] = svd(V);
% 
%     b = Vt(:,size(Vt,2));

   if b(1) < 0 || b(3) < 0 || b(6) < 0
       b = -b;
   end

    w = b(1)*b(3)*b(6) - b(2)*b(2)*b(6) - b(1)*b(5)*b(5) + 2*b(2)*b(4)*b(5) - b(3)*b(4)*b(4);
    d = b(1)*b(3) - b(2)*b(2);


    alpha = sqrt(abs(w/(d*b(1))));
    beta = sqrt(abs((w/(d*d))*b(1)));

    gamma = sqrt(abs(w/(d*d*b(1))))*b(2);

    u0 = (b(2)*b(5) - b(3)*b(4))/d;
    v0 = (b(2)*b(4) - b(1)*b(5))/d;

%     alpha = sqrt(abs(1/b(1)));
%     beta = sqrt(abs(1/b(3)));
%     gamma = 0;
%     u0 = 320;
%     v0 = 240;


    % Intrinsic Matrix

    Im = [
      alpha, gamma, u0;
          0,  beta, v0;
          0,     0,  1
    ];


    %% Calcular parametros Extrinsicos

    % Camara 1
    [R1 t1] = getExtrinsic(H1,Im);
    Em1 = [R1 t1];

    % Camara 2
    [R2 t2] = getExtrinsic(H2,Im);
    Em2 = [R2 t2];

    % Camara 3
    [R3 t3] = getExtrinsic(H3,Im);
    Em3 = [R3 t3];
end
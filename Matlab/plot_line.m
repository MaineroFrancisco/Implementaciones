%Plot Lines
% Dibuja la linea entre el centro de camara y el punto de la imagen, y
% devuelvo los puntos inicial y final de la recta, asi como tambien su
% pendiente, y offset, REVISAR SI REQUIERO MAS PROPIEDADES...
% 
% Im -> Intrinsic Param Matrix
% Em -> Extrinsic Param Matrix
% cc -> camera center (deducible)
% cp -> Camera Points (de la imagen)
% pp -> Projected Point, la projeccion sin parametros internos, puesta en
%       0, sin transformacion en el SC de la camara
% i -> point index
function [r,m,offset] = plot_line(Im, Em, cp, i, t_f)

    Em = [Em; 0 0 0 1];

    cc = inv(Em)*[0 0 0 1]';

    pp = inv(Im)*cp';
    pp = [pp; ones(1,size(pp,2))];
    
  
    pp = inv(Em)*pp;
    pp = pp';
    
    %         [X, Y, Z, w=1]
    m = pp(i, :)' - cc;
    
    offset = cc;
    
    t = [0 1];
    r = [
        m'*t(1) + cc';
        m'*t(2) + cc'
%         pp(i, :)
    ];
%   r2 = [
%         m'*t(1) + cc';
%         m'*t(2) + cc';
% %         pp(i, :)
%     ]
%     if nargin>4
%          plot3(r(:,1), r(:,2), r(:,3))
%     end
end

%% Dibujar Sistema de coordenadas, dado 1 punto origen y una matriz.
function draw_coordinate_system(O, M, point_type,color)
    
%    scatter3(O(1), O(2), O(3), point_type, color);
%            
%    plot3([O(1), M(1,1) + O(1)], [O(2), M(2,1) + O(2)], [O(3), M(3,1) + O(3)], 'color', 'red');     % X
%    plot3([O(1), M(1,2) + O(1)], [O(2), M(2,2) + O(2)], [O(3), M(3,2) + O(3)], 'color', 'blue');    % Y
%    plot3([O(1), M(1,3) + O(1)], [O(2), M(2,3) + O(2)], [O(3), M(3,3) + O(3)], 'color', 'green');   % Z
%
%    scatter3(M(1,1:3)+ O(1), M(2,1:3) + O(2), M(3,1:3) + O(3), point_type, color);
%   

    scatter3(O(1), O(2), O(3));
            
    plot3([O(1), M(1,1) + O(1)], [O(2), M(2,1) + O(2)], [O(3), M(3,1) + O(3)], 'color', 'red');     % X
    plot3([O(1), M(1,2) + O(1)], [O(2), M(2,2) + O(2)], [O(3), M(3,2) + O(3)], 'color', 'blue');    % Y
    plot3([O(1), M(1,3) + O(1)], [O(2), M(2,3) + O(2)], [O(3), M(3,3) + O(3)], 'color', 'green');   % Z

    scatter3(M(1,1:3)+ O(1), M(2,1:3) + O(2), M(3,1:3) + O(3));
     
end
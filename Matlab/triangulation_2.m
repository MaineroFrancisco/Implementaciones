% De a 2 vistas unicamente
function [int_p] = triangulation_2(Im1, Im2, Em1, Em2, c0, c1,p_char,p_color,fig_id)
    
   plot_system(Em1,Em2,Em1,fig_id)
% 
%     figure(1)
%     hold on
%     grid on
%     axis equal on

    int_p = zeros(size(c1,1),4);
    for k=1:size(c0,1)
        
        [r1,m1,of1]= plot_line(Im1,Em1,c0,k); 
        [r2,m2,of2] = plot_line(Im2,Em2,c1,k);
        
        int_p(k,:) = inters_point(m1,of1,m2,of2,p_char,p_color);
%         int_p(k,:) = inters_point(r1,r2,p_char,p_color);
    end
end
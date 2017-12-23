% Plot Intersection Point
% Calcula y dibuja la interseccion entre 2 rectas

% function [int] = inters_point(r1,r2, p_char, p_color)
function [int] = inters_point(m1,of1,m2,of2, p_char, p_color)
    
%     df = of2 - of1;
% %     
% %     b = (df(2) - df(1)*r1(2,2)/r1(2,1))/((r2(2,1)/r1(2,1))*r1(2,2) - r2(2,2));
% %     
%     b = (df(2) - m1(2)*df(1)/m1(1))/((m1(2)*m2(1)/m1(1)) - m2(2));
%     a = b*m2(1)/m1(1) + df(1)/m1(1);
%     
%     int = (of2+b*m2 + of1 + a*m1)/2;

r1 = [
    of1';
    (m1 + of1)';
];

r2 = [
    of2';
    (m2 + of2)';
];

    d1 = r1(2,:) - r1(1,:);
    d2 = r2(2,:) - r2(1,:);
  
    df = r2(1,:) - r1(1,:);
    
    n = cross(d1(1:3),d2(1:3));
    n2 = n*n';
    
    if n2~=0
        dist = dot(df(1:3),n/norm(n));
        
        if abs(dist)<0.001
            b = cross(n,df(1:3));
            alpha = dot(b,d2(1:3));
            beta = dot(b,d1(1:3));

%             if alpha < n2 && beta < n2   %% Es solo si quiero interpolar, no extrapolar
            int = r1(1,:) + (alpha/n2)*d1;
%                     int = r2(1,:) + (beta/n2)*d2;
%             end
        else
                        
            n = n/norm(n);
            
            r1(1,1:3) = r1(1,1:3) + ((dist/2)*n);
            r1(2,1:3) = r1(2,1:3) + ((dist/2)*n);
            r2(1,1:3) = r2(1,1:3) - ((dist/2)*n);
            r2(2,1:3) = r2(2,1:3) - ((dist/2)*n);

            d1 = r1(2,:) - r1(1,:);
            d2 = r2(2,:) - r2(1,:);
            
            df = r2(1,:) - r1(1,:);
            
            n = cross(d1(1:3),d2(1:3));
            n2 = n*n';
            
            
%            df = r2(1,:) - r1(1,:);
%
%            b = (df(2) - m1(2)*df(1)/m1(1))/((m1(2)*m2(1)/m1(1)) - m2(2));
%            a = b*m2(1)/m1(1) + df(1)/m1(1);
%
%            int = ((r1(1,:) + a*m1')+(r2(1,:) + b*m2'))/2;

             b = cross(n,df(1:3));
             alpha = dot(b,d2(1:3)');
             beta = dot(b,d1(1:3)');
 
 %             if alpha < n2 && beta < n2
                     int = r1(1,:) + (alpha/n2)*d1;
 %                     int = r2(1,:) + (beta/n2)*d2;
 %             end
        end    
    end
    
%   scatter3(int(1),int(2),int(3),p_char,p_color)
     scatter3(int(1),int(2),int(3))
    
end
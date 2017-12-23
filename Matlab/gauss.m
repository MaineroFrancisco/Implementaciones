% Gauss Jordan
% La matriz M se espera que sea de rango 8, para el problema particular
function [h] = gauss(M)
    n = size(M,1);
    m = size(M,2);

    % pivoteo parcial
    
    for k=1:n
        
        if M(k,k) == 0
            for i=k:n
              if M(i,k)~=0
                    aux = M(i,:);
                    M(i,:) = M(k,:);
                    M(k,:) = aux;
                    break;
              end
            end
        end
      
    end
    
%     for k=1:n-1
%         
%         if abs(M(k,k)) < abs(M(k+1,k))
%             aux = M(k,:);
%             M(k,:) = M(k+1,:);
%             M(k+1,:) = aux;
%             k=0;
%         end
%       
%     end
    
    % foward elimination
    for k=1:n
        for i=k:n-1
            c = M(i+1,k)/M(k,k);
            
            M(i+1,:) = M(i+1,:)- c*M(k,:);
            
        end
    end

    h = zeros(m,1);
    h(m) = 1;
    
    for k=m-1:-1:1
        
        for i=k+1:m
            h(k) = h(k) - M(k,i)*h(i);
        end
        h(k) = h(k)/(M(k,k));
        
    end
    
end
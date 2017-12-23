% ESTIMATE HOMOGRAPHY
% B = H*A
function [H] = estimateHomography(A,B)
    N = size(A,1);
    
    Na = getNormMatrix(A);
    Nb = getNormMatrix(B);
    
%    Na = [ 1 0 0; 0 1 0; 0 0 1];
%    Nb = [ 1 0 0; 0 1 0; 0 0 1];
    
    %% ERROR EN LA HOMOGRAFIE REVISAR!!!
    
    M = zeros(2*N,9);
    
    for j=1:N
    
        k = 2*j;
        
        %Normalizar
        a = Na * A(j,:)';
        
%        if a(3)~=0
            a = a/a(3);
%        end
        
        b = Nb * B(j,:)';

%        if b(3)~=0
            b = b/b(3);
%        end
        
        M(k-1,:) = [-a(1) -a(2) -1 0 0 0 a(1)*b(1) a(2)*b(1) b(1)]; 
        M(k,:) = [0 0 0 -a(1) -a(2) -1 a(1)*b(2) a(2)*b(2) b(2)]; 
        
    end
    
    v = gauss(M);
    
%     [U,S,V] = svd(M);
% %    S = diag(S);
% 
%     v = V(:,size(V,2));

    %%
    
    Hp = [
        v(1) v(2) v(3);
        v(4) v(5) v(6);
        v(7) v(8) v(9);
    ];
    
    H = inv(Nb)*Hp*Na;
    H = H/H(3,3);
end
% V
function [v] = vij(H,i,j)
    v = [
        H(1,i)*H(1,j);
        H(1,i)*H(2,j) + H(2,i)*H(1,j);
        H(2,i)*H(2,j);
        H(3,i)*H(1,j) + H(1,i)*H(3,j);
        H(3,i)*H(2,j) + H(2,i)*H(3,j);
        H(3,i)*H(3,j)
    ]';
end
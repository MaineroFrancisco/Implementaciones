% GET NORMALIZATION MATRIX
function [Na] = getNormMatrix(A)

    N = size(A,1);
    
    x = A(:,1);
    y = A(:,2);
    
    x_mean = (1/N)*sum(x);
    y_mean = (1/N)*sum(y);

    desv_x = sum(((x-x_mean).*(x-x_mean)))/N;
    desv_y = sum(((y-y_mean).*(y-y_mean)))/N;
    
    scale_x = sqrt(2/desv_x);
    scale_y = sqrt(2/desv_y);
    
    Na = [
        scale_x         0 -scale_x*x_mean;
              0   scale_y -scale_y*y_mean;
              0         0               1
    ];

end
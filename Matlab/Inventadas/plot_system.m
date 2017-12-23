% Plot System, 3 Camera Matrix
function plot_system(Em1,Em2,Em3, i)
    figure(i)
    hold on
    grid on
    axis equal on
    draw_coordinate_system([0 0 0 1]', [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1], 'o', 'blue')
    draw_coordinate_system(inv([Em1; 0 0 0 1])*[0 0 0 1]', inv([Em1; 0 0 0 1])*[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1], 'o', 'blue')
    draw_coordinate_system(inv([Em2; 0 0 0 1])*[0 0 0 1]', inv([Em2; 0 0 0 1])*[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1], 'o', 'blue')
    draw_coordinate_system(inv([Em3; 0 0 0 1])*[0 0 0 1]', inv([Em3; 0 0 0 1])*[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1], 'o', 'blue')
end
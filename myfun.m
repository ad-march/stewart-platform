function F = myfun(x, l_crank)
%rp = x(1);
%theta2 = x(2);
h = 0.200;
l_rocker = sqrt(l_crank^2 + h^2);
theta1 = deg2rad(45);

F = [l_rocker*sin(x(2)) - x(1)*sin(theta1) - h + l_crank;
     l_rocker*cos(x(2)) + x(1)*cos(theta1) - x(1)];
end
 

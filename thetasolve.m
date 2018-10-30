
x0 = [100;100];
options = optimoptions('fsolve','Display','iter');

table=ones(16,10);
table(1,2:16) = 10:10:150;
table(2:10,1) = 100:50:500;

l_crank=10;
h=200;
%rp=100;

%for j=2:10 %rp
   
for i=2:16 %crank
    l_rocker = sqrt(h^2+ l_crank^2);
table(2,i) = x(1);
F = [x(2)*sin(theta2) - x(1)*sin(theta1) - h + l_crank;
     x(2)*cos(theta2) + x(1)*cos(theta1) - x(1)];
l_crank=l_crank + 10;

end
%rp = rp + 50;

%end
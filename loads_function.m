function M12 = loads(l_crank,l_rocker)
r2 = l_crank/1000; %crank m
r3 = l_rocker/1000; %rocker m
b3 = r3/2; %dist to cg
theta2 = 0;%servo angle for max load
omega2 = -50*2*pi/60; %50rpm = no load speed
m2 = 0;
m3 = 0;
m4 = 0.3;
I3 = 1/12 * m3*r3^2;
F = m4*9.81;

theta3 = acos(-r2*cos(theta2)/r3);
omega3 = -(omega2*r2*sin(theta2))/(r3*sin(theta3));
alpha3 = ( -(omega2^2*r2*cos(theta2))-(omega3*r3*cos(theta3)) ) / (r3*sin(theta3));
ag4y=(omega2^2 *r2*sin(theta2)) + (omega3^2 *r3*sin(theta3)) - (alpha3*r3*cos(theta3));
ag3x = -(omega2^2*r2*cos(theta2))-(omega3^2*b3*cos(theta3))-(alpha3*b3*sin(theta3));
ag3y = -(omega2^2*r2*sin(theta2))-(omega3^2*b3*sin(theta3))+(alpha3*b3*cos(theta3));

F34Y = F - m4*ag4y;
F23Y = m3*ag3y-F34Y;
F23X = (I3*alpha3 + F23Y*b3*sin(theta3-pi/2) - F34Y*(r3-b3)*sin(theta3-pi/2) + m3*ag3x*(r3-b3)*cos(theta3-pi/2)) / (b3*cos(theta3-pi/2)+(r3-b3)*cos(theta3-pi/2));
F34X = m3*ag3x - F23X;

M12 = -F23X*(r2*sin(theta2)) - F23Y*(r2*cos(theta2));
end

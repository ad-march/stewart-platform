rb = 150; %radius of base mm
angle_offset = 20; %smallest angle between 2 mounts
h = 200;
l_crank = 150;
l_rocker = sqrt(h^2 + l_crank^2);
n_segments = 45;
linewidth = 2;
x_lim = rb+50;
y_lim = rb+50;

Tx=0;
Ty=0;
Tz=0;
alpha=1; %1 degree increments
beta=0/n_segments;
gamma=0;

T = ones(7,3);
top = ones(7,3);
base = ones(7,3);
R = eye(3);
lengths = ones(6,n_segments);
servo_angle = zeros(6,n_segments);
B = ones(n_segments, 6); %crank angle?


%base platform
for i=0:6
    if mod(i,2)==0 %if i is even
    angle = i*60 + angle_offset;  
    B(i+1) = deg2rad(angle-90);

    else
    angle = i*60 - angle_offset;
    B(i+1) = deg2rad(angle+90);
    end
    base(i+1,:) = [rb*cos(deg2rad(angle)), rb*sin(deg2rad(angle)), -h];
end
%plot base
plot3(base(:,1),base(:,2),base(:,3),'r', 'linewidth', linewidth); %connects the dots
hold on;

%top platform
for i=0:6
    if mod(i,2)==0 %if i is even
    angle = i*60 + angle_offset;  
      
    else
    angle = i*60 - angle_offset;  
    end
  top(i+1,:) = [rb*cos(deg2rad(angle)), rb*sin(deg2rad(angle)), 0];
end
%plot top
plot3(top(:,1),top(:,2),top(:,3),'g', 'linewidth', linewidth);
hold on;


%plot crank and rocker
for i=1:6
lengths(i) = norm(top(i,:) - base(i,:));
M = 2*l_crank*(top(i,3)-base(i,3));
N = 2*l_crank*(cos(B(i))*(top(i,1)-base(i,1)) + sin(B(i))*(top(i,2)-base(i,2)));
L=lengths(i)^2-(l_rocker^2-l_crank^2);
servo_angle(i,1) = asin(L/sqrt(M^2+N^2)) - atan(N/M);
crank = [base(i,1) + l_crank*cos(B(i))*cos(servo_angle(i,1)), base(i,2) + l_crank*cos(servo_angle(i,1))*sin(B(i)),...
        base(i,3) + l_crank*sin(servo_angle(i,1))];

link1 = [top(i,:); crank];
link2 = [crank;base(i,:)];
plot3(link1(:,1),link1(:,2),link1(:,3),'m', 'linewidth', linewidth);
hold on;
plot3(link2(:,1),link2(:,2),link2(:,3),'c', 'linewidth', linewidth);
hold on;

% compute misalignemnt angles
N = cross([base(i,1) base(i,2) 0] - base(1,:), [base(i,1) base(i,2) 0] - crank);
%// angle between plane and line, equals pi/2 - angle between D-E and N
plane_angle(i,1) = rad2deg(abs( pi/2 - acos( dot(crank-top(i,:), N)/norm(N)/norm(crank-top(i,:)) ) ));
end

axis([-x_lim x_lim -y_lim y_lim -h-l_crank h]);
grid on;
hold off;
  

%%{
%move platform
for j=1:n_segments

pause(0.0001);

%plot base
plot3(base(:,1),base(:,2),base(:,3),'r', 'linewidth', linewidth); %connects the dots
hold on;

%rotation matrix
R_x = [1,0,0 ; 0, cos(deg2rad(alpha)), sin(deg2rad(alpha)); 0, -sin(deg2rad(alpha)), cos(deg2rad(alpha))];
R_y = [ cos(deg2rad(beta)),0, -sin(deg2rad(beta)); 0,1,0 ; sin(deg2rad(beta)),0, cos(deg2rad(beta))];
R_z = [cos(deg2rad(gamma)), sin(deg2rad(gamma)), 0; -sin(deg2rad(gamma)), cos(deg2rad(gamma)),0; 0,0,1];
R = R_x * R_y * R_z ;

%translation matrix
T(:,1)=Tx;
T(:,2)=Ty;
T(:,3)=Tz;

%update top mount pts
top = R*transpose(top);
top = transpose(top)+T;

%plot top
plot3(top(:,1),top(:,2),top(:,3),'g', 'linewidth', linewidth);
hold on;

%plots links
for i=1:6
lengths(i) = norm(top(i,:) - base(i,:));
M = 2*l_crank*(top(i,3)-base(i,3));
N = 2*l_crank*(cos(B(i))*(top(i,1)-base(i,1)) + sin(B(i))*(top(i,2)-base(i,2)));
L=lengths(i)^2-(l_rocker^2-l_crank^2);
servo_angle(i,j+1) = asin(L/sqrt(M^2+N^2)) - atan(N/M);
crank = [base(i,1) + l_crank*cos(B(i))*cos(servo_angle(i,j+1)), base(i,2) + l_crank*cos(servo_angle(i,j+1))*sin(B(i)),...
        base(i,3) + l_crank*sin(servo_angle(i,j+1))];

link1 = [top(i,:); crank];
link2 = [crank;base(i,:)];
plot3(link1(:,1),link1(:,2),link1(:,3),'m', 'linewidth', linewidth);
hold on;
plot3(link2(:,1),link2(:,2),link2(:,3),'c', 'linewidth', linewidth);
hold on;

% compute misalignemnt angles
N = cross([base(i,1) base(i,2) 0] - base(1,:), [base(i,1) base(i,2) 0] - crank);
%// angle between plane and line, equals pi/2 - angle between D-E and N
plane_angle(i,j+1) = rad2deg(abs( pi/2 - acos( dot(crank-top(i,:), N)/norm(N)/norm(crank-top(i,:)) ) ));

end

hold off;
axis([-x_lim x_lim -y_lim y_lim -h-l_crank h]);
grid on;
xlabel('x');
ylabel('y');
end
%%}
array = rad2deg(servo_angle);
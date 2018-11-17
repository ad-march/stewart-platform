x_size = 10;
y_size = 11;
max_angle = zeros(x_size,y_size);
plane_angle = zeros(x_size,y_size);
max_load = zeros(x_size,y_size);

angle_offset = 30-15.63/2; %smallest angle between 2 mounts
h = 200;
n_segments = 45;

Tx=0;
Ty=35.8;
Tz=0;

platform_center = [Tx Ty Tz];

%alpha=45/n_segments;
beta=0/n_segments;
gamma=0;

T = ones(7,3);
top = ones(7,3);
base = ones(7,3);
R = eye(3);
lengths = ones(6,n_segments);
servo_angle = zeros(6,n_segments);
B = ones(n_segments, 6); %crank angle?

alpha = 1; %increment by 1 degree)
%rotation matrix
R_x = [1,0,0 ; 0, cos(deg2rad(alpha)), sin(deg2rad(alpha)); 0, -sin(deg2rad(alpha)), cos(deg2rad(alpha))];
R_y = [ cos(deg2rad(beta)),0, -sin(deg2rad(beta)); 0,1,0 ; sin(deg2rad(beta)),0, cos(deg2rad(beta))];
R_z = [cos(deg2rad(gamma)), sin(deg2rad(gamma)), 0; -sin(deg2rad(gamma)), cos(deg2rad(gamma)),0; 0,0,1];
R = R_x * R_y * R_z ;



rb = 25; %radius of base mm
for loop_rb = 1:x_size-1

rb = rb+25;
max_angle(loop_rb+1,1) = rb; %rows show rb starting at 2
plane_angle(loop_rb+1,1) = rb;
max_load(loop_rb+1,1) = rb;
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

l_crank = 0;
for loop_crank = 1:y_size-1
    
%reset variabes
l_crank = l_crank + 10;
l_rocker = sqrt(h^2 + l_crank^2);
lengths = ones(6,n_segments);
servo_angle = zeros(6,n_segments);

max_angle(1,loop_crank+1) = l_crank; %columns show l_crank starting at 2
plane_angle(1,loop_crank+1) = l_crank;
max_load(1,loop_crank+1) = l_crank;

%{
if l_crank > rb
    continue
end
%}

%reset top platform 
for i=0:6
    if mod(i,2)==0 %if i is even
    angle = i*60 + angle_offset;  
      
    else
    angle = i*60 - angle_offset;  
    end
  top(i+1,:) = [rb*cos(deg2rad(angle)), rb*sin(deg2rad(angle)), 0];
end

top = top + ones(7,3).*platform_center;
%%{
%move platform
for j = 1:45 %increment degrees
  
%update top mount pts
%to rotate around its own axis, it translates itself back to the origin,rotates and then translates back
top = transpose(R*transpose(top - ones(7,3).*platform_center)) + ones(7,3).*(platform_center);


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

% compute misalignemnt angles
N = cross([base(i,1) base(i,2) 0] - base(1,:), [base(i,1) base(i,2) 0] - crank);
%// angle between plane and line, equals pi/2 - angle between D-E and N
temp_angle = rad2deg(abs( pi/2 - acos( dot(crank-top(i,:), N)/norm(N)/norm(crank-top(i,:)) ) ));

%fill array with largest misalignemnt angle
    if temp_angle > plane_angle(loop_rb +1,loop_crank +1)    
        plane_angle(loop_rb +1,loop_crank +1) = temp_angle;
    end
end

    if isreal(servo_angle)==0
        break
    end

end
%%}
max_load(loop_rb +1,loop_crank +1) = loads_function(l_crank,l_rocker);
max_angle(loop_rb +1,loop_crank +1) = j;

end

end

surf(max_angle(1,2:y_size),max_angle(2:x_size,1),max_angle(2:x_size,2:y_size)) %3D plot
xlabel('Crank Length (mm)');
ylabel('Base Radius (mm)');
zlabel('Max Angle (deg)');